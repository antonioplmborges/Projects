; CIS-261
; M09demo.ASM
;
; @topic W110101 Lab M09 demo program
; @brief Lab M09, <a href="http://www.c-jump.com/bcc/c261c/MLabs/M09arrays/lecture.html" target="_blank">Data Arrays and Windows API Calls</a>

.386                  ; Tells MASM to use Intel 80386 instruction set.
.MODEL FLAT           ; Flat memory model
option casemap:none   ; Treat labels as case-sensitive

EXTERN _Beep@8:NEAR				; takes 2 DWORD parameters
EXTERN _Sleep@4:NEAR			; takes 1 DWORD parameter
 EXTERN _GetLastError@0:NEAR	; Function has no arguments

INCLUDE IO.H          ; header file for input/output

.CONST                ; Constant data segment
DEBUG_MESSAGE			 BYTE	"debug ", 0
PROMPT_FREQUENCY		 BYTE	"enter frequency: ", 0
PROMPT_DURATION			 BYTE	"enter duration: ", 0
PROMPT_NUMBER_OF_BEEPS   BYTE	"enter number of beeps (max 16): ", 0
PROMPT_BAD_INPUT         BYTE	"Sorry, your input was invalid, please repeat.", 0
SZ_PAUSE                 BYTE	"Please type x and hit Enter to exit: ", 0
SZ_ERROR				 BYTE	"Error: ", 0
SZ_FREQ					 BYTE	"Playing frequency: ", 0
SZ_DUR					 BYTE	"Duration: ", 0
ENDL                     BYTE	13, 10, 0


.STACK 100h     ; (default is 1-kilobyte stack)

.DATA           ; Begin initialized data segment
    char_buffer BYTE     12 DUP (0) ; memory to convert numbers to text
    frequency   DWORD    1000       ; Hertz
    duration    DWORD    200        ; milliseconds
    beep_count  DWORD    5          ; how many beeps to make

    ;; TODO: populate this array with frequency/duration pairs
    ;;       and use it as input for the make_beep procedure
    beep_mem    DWORD    32 DUP (?) ; an array of up to 32 integers
                                    ; provides space for 8 pairs of frequency/duration

	ARRAY_LENGTH EQU	LENGTHOF beep_mem        ; should be up to 32
    ARRAY_TYPE   EQU	TYPE     beep_mem        ; should be 4

.CODE           ; Begin code segment
_main PROC      ; Beginning of code

code_start:

    ;;--------------------------------------------------
    ;; ask the user how many beeps they want
    ;;--------------------------------------------------

@@:
    output      PROMPT_NUMBER_OF_BEEPS
    input       char_buffer, 12     ; 10 characters + CR, LF
    atod        char_buffer         ; convert text to int -- result in EAX
    jno         @F                  ; if everything okay, continue
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
    jmp         @B

	

	@@:

	mov         [beep_count], eax   ; store beep count in  memory
	output      ENDL

    ;;-----------------------------------------------------------
    ;; validate that input in EAX is less than max allowed value
    ;; Use this formula: user_input <= ARRAY_LENGTH / 2
    ;;-----------------------------------------------------------
    cmp         eax, ARRAY_LENGTH / 2
    
	jle         @F
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
    jmp         code_start

@@:	
	mov ecx, [beep_count]; the loop counter - how many pairs of F:D we have
	mov edi, OFFSET beep_mem     ; load address of our array into EDI
get_freq_count:
@@:

	
    ;; ------------------------------------------------------
    ;; ask the user for the freq value
    ;; ------------------------------------------------------
    
	
	output      PROMPT_FREQUENCY
    input       char_buffer, 12     ; 10 characters + CR, LF
    atod        char_buffer         ; convert text to int -- result in EAX
    jno @F
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
	output      ENDL
    jmp         @B

@@:
    mov         [frequency], eax ; store frequency in memory

	output      PROMPT_DURATION
    input       char_buffer, 12     ; 10 characters + CR, LF
    atod        char_buffer         ; convert text to int -- result in EAX
    jno @F
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
	output      ENDL
    jmp         @B
	


@@:
    mov         [duration], eax ; store duration in memory
	output      ENDL

	

   

	;;-------------------------------------------------------
    ;; populate an array with [duration] and [frequency] values
    ;; use beep_count as the number of beeps
    ;;-------------------------------------------------------
    
    mov eax, [ frequency ]       ; load freq value
    mov edx, [ duration ]        ; load duration value



    mov [edi], eax               ; store freq in the first element of each pair
    mov [edi + ARRAY_TYPE], edx  ; store duration in the second element

  

    add edi, ARRAY_TYPE * 2      ; advance the data pointer
    dec ecx                       ; decremnt loop counter
    cmp ecx, 0
    jnz get_freq_count


    ;; ------------------------------------------------------
    ;; Generate beeps at the specified freq/duration:
    ;; ------------------------------------------------------
    mov         ecx, [beep_count]  ; use ECX as loop counter

	mov edi, OFFSET[beep_mem]
@@:
;loop_count:

    output      ENDL	
	output		SZ_FREQ
	dtoa		char_buffer, [edi]		; convert frequency value
	output		char_buffer				; print frequency
	output		ENDL
	output		SZ_DUR
	dtoa		char_buffer, [edi + ARRAY_TYPE]	; convert duration value
	output		char_buffer						; print duration
	output		ENDL
	mov         ebx, [edi + ARRAY_TYPE]    ; duration, milliseconds
    mov         eax, [edi]   ; frequency, Hertz
    call        make_beep
   

    add			edi, [ARRAY_TYPE * 2]	; continue to the next pair
    dec         ecx                ; decrement loop counter
    cmp         ecx, 0             ; check the loop condition
    jnz         @B                 ; continue or exit loop
	;loop loop_count
	


	


	;--------------------------------------------------------
    ; Pause before exiting
    ;--------------------------------------------------------
    output      ENDL
	output	SZ_PAUSE
    input	char_buffer, SIZEOF char_buffer
    cmp     byte ptr [char_buffer], "x"	; if user input 'x' exit program
	je		@F
	output  ENDL
	jmp		code_start				; otherwise restart
	
@@:
    ret
    
_main ENDP

; to call this procedure, pass
; frequency in EAX
; duration in EBX
make_beep PROC
    ;push   eax       ; preserve orig EAX reg value
    ;push   ebx       ; preserve orig EBX reg value
    pushad            ; preserve all registers on the stack

    push	ebx				; duration
    push	eax				; frequency
    call	_Beep@8			; Beep( frequency, duration );eax contains the result
	cmp		eax, eax		; compare eax for error. if eax=0 - no error. if eax =1 - error
	jz		@F
	call	_GetLastError@0	; call GetLastError function and store return in eax
	dtoa	char_buffer, eax; convert error to ASCII
	output	SZ_ERROR
	output	char_buffer		;print error
	output  ENDL
	
	@@:

    mov    eax, 200   ; 200 milliseconds pause
    push   eax        ; specify time to sleep
    call   _Sleep@4   ; Sleep for 200 ms

    ;pop    ebx       ; restore EBX from the stack
    ;pop    eax       ; restore EAX from the stack
    popad             ; restore all registers from the stack
    ret
make_beep ENDP

    ret

END _main        ; Marks the end of the module and sets the program entry point label

cd D:\CIS261\Projects\M09
"C:\Program Files\Microsoft Visual Studio 10.0\Common7\Tools\vsvars32.bat"
ML /coff /c /Fl M09demo.ASM IO.ASM
LINK /subsystem:console /entry:main /out:M09.exe M09demo.obj IO.obj "kernel32.lib"