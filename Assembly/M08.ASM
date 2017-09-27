; CIS-261
; M08.ASM
; Demo program of IO.H and IO.ASM usage

.386                ; Tells MASM to use Intel 80386 instruction set.
.MODEL FLAT         ; Flat memory model
option casemap:none ; Treat labels as case-sensitive

INCLUDE IO.H        ; header file for input/output

.CONST              ; Constant data segment
SZ_PROMPT1_8BIT_UNSIGNED     BYTE "Input first 8-bit unsigned integer: ", 0
SZ_PROMPT2_8BIT_UNSIGNED	 BYTE "Input second 8-bit unsigned integer: ", 0
SZ_PROMPT1_32BIT_SIGNED      BYTE "Input first 32-bit signed integer: ", 0
SZ_PROMPT2_32BIT_SIGNED	     BYTE "Input second 32-bit signed integer: ", 0
SZ_FIRST_8BIT_UNSIGNED		 BYTE "The first 8-bit unsigned integer is " , 0
SZ_SECND_8BIT_UNSIGNED		 BYTE "The second 8-bit unsigned integer is", 0
SZ_FIRST_32BIT_SIGNED		 BYTE "The first 32-bit unsigned integer is " , 0
SZ_SECND_32BIT_SIGNED		 BYTE "The second 32-bit unsigned integer is", 0
SZ_PROMPT_BAD_INPUT			 BYTE "***BAD INPUT*** try again!", 0
SZ_PROMPT_BAD_SMALL_NUMBER   BYTE "** Error: the number is too small...", 0
SZ_PROMPT_BAD_BIG_NUMBER     BYTE "** Error: the number is too big...", 0
SZ_PROMPT_BAD_SUM            BYTE "** Error: sum overflow...", 0
SZ_PROMPT_OVERFLOW           BYTE "** Error: overflow...", 0
SZ_RESULT					 BYTE "The result is: ", 0
SZ_NEW_LINE					 BYTE 13, 10, 0
SZ_PAUSE					 BYTE "Please type x and hit Enter to exit: ", 0

.DATA               ; Begin initialized data segment
buffer              BYTE    12 DUP (?)
dtoa_buffer_one     BYTE    11 DUP (?)
dtoa_buffer_two     BYTE    11 DUP (?)
dtoa_buffer_1       BYTE    11 DUP (?)
dtoa_buffer_2       BYTE    11 DUP (?)
dtoa_buffer_3       BYTE    11 DUP (?),0
fst_8bit            BYTE    11 DUP (?)			; a memory for a byte-size variable
scnd_8bit           BYTE    11 DUP (?)          ; another byte-size variable
fst_32bit           DWORD		?				; a memory for a byte-size variable
scnd_32bit          DWORD		?				; another byte-size variable 

.CODE               ; Begin code segment  
_main PROC          ; Beginning of code

input_first_8_bit:
    ;--------------------------------------------------------
    ; Input first 8-bit unsigned integers from the user
    ;--------------------------------------------------------
    output SZ_PROMPT1_8BIT_UNSIGNED
    input buffer, SIZEOF buffer ; Get user input
    ;--------------------------------------------------------
    ; Validate input length and make sure it's 0 < input < 4
    ;--------------------------------------------------------
    szlen buffer                ; Get input size in EAX
    or EAX, EAX                 ; Is EAX zero?
    jnz @F                      ; if not, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
    jmp input_first_8_bit       ; repeat the input
@@:
    cmp EAX, 3                  ; Make sure no more than 3 characters
    jle @F                      ; if everything okay move on
    output SZ_PROMPT_BAD_BIG_NUMBER 
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_first_8_bit       ; repeat the input
@@:
    ;--------------------------------------------------------
    ; Validate range from 0 to 255
    ;--------------------------------------------------------
    atod buffer                 ; convert text to number in EAX
    jno @F                      ; if it worked, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
    jmp input_first_8_bit       ; repeat the input
@@:
    ;--------------------------------------------------------
    ; Now EAX contains our first number
    ;--------------------------------------------------------
    cmp EAX, 0                  ; See if EAX >= 0
    jge @F                      ; EAX is >= 0, which is good 
    output SZ_PROMPT_BAD_SMALL_NUMBER
    output SZ_NEW_LINE
    jmp input_first_8_bit       ; repeat the input
@@:
    cmp EAX, 255                ; See if EAX > 255
    jle @F                      ; EAX <= 255, which is good
    output SZ_PROMPT_BAD_BIG_NUMBER
    output SZ_NEW_LINE
    jmp input_first_8_bit       ; repeat the input
@@:
	
	;-----------------------------------------------
    ; First 8-bit number is okay
    ;-----------------------------------------------
    mov [fst_8bit], AL                ; store value in memory

	;--------------------------------------------------------
    ; Print result in EAX on the screen
    ;--------------------------------------------------------
    dtoa dtoa_buffer_one, EAX			;convert integer stored in EAX to ASCII and store in dtoa_buffer_two
    output SZ_FIRST_8BIT_UNSIGNED		;"The first 8-bit unsigned integer is "
    output dtoa_buffer_one				;print user input
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    
input_second_8_bit:

    ;--------------------------------------------------------
    ; Input second 8-bit unsigned integers from the user
    ;--------------------------------------------------------
    output SZ_PROMPT2_8BIT_UNSIGNED
    input buffer, SIZEOF buffer ; Get user input
    ;--------------------------------------------------------
    ; Validate input length and make sure it's 0 < input < 4
    ;--------------------------------------------------------
    szlen buffer                ; Get input size in EBX
    or EAX, EAX                 ; Is EAX zero?
    jnz @F                      ; if not, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_second_8_bit       ; repeat the input
@@:
    cmp EAX, 3                  ; Make sure no more than 3 characters
    jle @F                      ; if everything okay move on
    output SZ_PROMPT_BAD_BIG_NUMBER
    output SZ_NEW_LINE
    jmp input_second_8_bit       ; repeat the input
@@:
    ;--------------------------------------------------------
    ; Validate range from 0 to 255
    ;--------------------------------------------------------
    atod buffer                 ; convert text to number in EAX
    jno @F                      ; if it worked, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_first_8_bit       ; repeat the input
@@:
    ;--------------------------------------------------------
    ; Now EAX contains our second number
    ;--------------------------------------------------------
    cmp EAX, 0                  ; See if EBX >= 0
    jge @F                      ; EAX is >= 0, which is good 
    output SZ_PROMPT_BAD_SMALL_NUMBER
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_second_8_bit       ; repeat the input
@@:
    cmp EAX, 255                ; See if EAX > 255
    jle @F                      ; EAX <= 255, which is good
    output SZ_PROMPT_BAD_BIG_NUMBER
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_second_8_bit       ; repeat the input
@@:
	
    ;--------------------------------------------------------
    ; Print result in EAX on the screen                      
    ;--------------------------------------------------------
    dtoa dtoa_buffer_two, EAX			; convert integer stored in EAX to ASCII and store in dtoa_buffer_two
    output SZ_SECND_8BIT_UNSIGNED		; "The second 8-bit unsigned integer is"
	output dtoa_buffer_two				; print user input
    output SZ_NEW_LINE
	output SZ_NEW_LINE

	;-----------------------------------------------
    ; First 8-bit number is okay
    ;-----------------------------------------------
    mov [scnd_8bit], AL                ; store value in memory
	
	;-----------------------------------------------
    ; Add
    ;-----------------------------------------------
    
	add AL, [fst_8bit]					; compute the sum
	jae @F
	;Error handling
	clc									; clear carry flag
	xor al, al							;XOR instruction always clears OF and CF flags
	output SZ_PROMPT_BAD_SUM
	output SZ_NEW_LINE
	output SZ_NEW_LINE
	jmp input_second_8_bit
	
	@@:
	output SZ_RESULT					; "The result is "
	dtoa dtoa_buffer_two, EAX			; convert number to text
	output dtoa_buffer_two				; print result of the sum
    output SZ_NEW_LINE
	output SZ_NEW_LINE
	
input_first_32_bit:
    ;--------------------------------------------------------
    ; Input first 32-bit signed integers from the user
    ;--------------------------------------------------------
    output SZ_PROMPT1_32BIT_SIGNED
    input buffer, SIZEOF buffer ; Get user input
    ;--------------------------------------------------------
    ; Validate input length and make sure it's 0 < input < 11
    ;--------------------------------------------------------
    szlen buffer                ; Get input size in EAX
    or EAX, EAX                 ; Is EAX zero?
    jnz @F                      ; if not, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_first_32_bit      ; repeat the input
@@:
    cmp EAX, 10                 ; Make sure no more than 10 characters
    jne @F                      ; if everything okay move on
    output SZ_PROMPT_BAD_BIG_NUMBER 
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_first_32_bit       ; repeat the input
@@:
    ;--------------------------------------------------------
    ; Validate range from -2,147,483,648 to 2,147,483,647
    ;--------------------------------------------------------
    atod buffer                 ; convert text to number in EAX
    jno @F                      ; if it worked, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_first_32_bit       ; repeat the input

@@:
	;-----------------------------------------------
    ; First 32-bit number is okay
    ;-----------------------------------------------
    mov [fst_32bit],EAX                ; store value in memory

	;--------------------------------------------------------
    ; Print result in EAX on the screen
    ;--------------------------------------------------------
    dtoa dtoa_buffer_1, EAX			;convert integer stored in EAX to ASCII and store in dtoa_buffer_1
    output SZ_FIRST_32BIT_SIGNED		;"The first 32-bit unsigned integer is "
    output dtoa_buffer_1				;print user input
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    
input_second_32_bit:
    ;--------------------------------------------------------
    ; Input second 32-bit unsigned integers from the user
    ;--------------------------------------------------------
    output SZ_PROMPT2_32BIT_SIGNED
    input buffer, SIZEOF buffer ; Get user input
    ;--------------------------------------------------------
    ; Validate input length and make sure it's 0 < input < 11
    ;--------------------------------------------------------
    szlen buffer                ; Get input size in EBX
    or EAX, EAX                 ; Is EAX zero?
    jnz @F                      ; if not, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_second_32_bit     ; repeat the input
@@:
    cmp EAX, 10                 ; Make sure no more than 10 characters
    jne @F                      ; if everything okay move on
    output SZ_PROMPT_BAD_BIG_NUMBER
    output SZ_NEW_LINE
	output SZ_NEW_LINE
    jmp input_second_32_bit     ; repeat the input
@@:
    ;--------------------------------------------------------
    ; Validate range from -2,147,483,648 to 2,147,483,647
    ;--------------------------------------------------------
    atod buffer                 ; convert text to number in EAX
    jno @F                      ; if it worked, then move on
    output SZ_PROMPT_BAD_INPUT
    output SZ_NEW_LINE
	output SZ_NEW_LINE
	xor EAX, EAX					; clear overlfow flag
    jmp input_second_32_bit       ; repeat the input

@@:	
	
    ;--------------------------------------------------------
    ; Print result in EAX on the screen                      
    ;--------------------------------------------------------
    dtoa dtoa_buffer_2, EAX				; convert integer stored in EAX to ASCII and store in dtoa_buffer_two
    output SZ_SECND_32BIT_SIGNED		; "The second 32-bit unsigned integer is"
	output dtoa_buffer_2				; print user input
    output SZ_NEW_LINE
	output SZ_NEW_LINE

	;-----------------------------------------------
    ; Second 32-bit number is okay
    ;-----------------------------------------------
    mov [scnd_32bit], EAX                ; store value in memory
	
	;-----------------------------------------------
    ; SUBTRACT
    ;-----------------------------------------------
   								
	sub [fst_32bit], EAX						; compute the difference
	jno @F
	;Error handling
	output SZ_PROMPT_OVERFLOW
	output SZ_NEW_LINE
	output SZ_NEW_LINE
	jmp input_second_32_bit
	
@@:
	output SZ_RESULT					; "The result is "
	dtoa dtoa_buffer_3, [fst_32bit]	; convert number to text
	output dtoa_buffer_3				; print result of the subtraction
    output SZ_NEW_LINE
	output SZ_NEW_LINE

    ;--------------------------------------------------------
    ; Pause before exiting
    ;--------------------------------------------------------
    output SZ_PAUSE
    input buffer, SIZEOF buffer
    ret
    
_main ENDP
END _main        ; Marks the end of the module and sets the program entry point label