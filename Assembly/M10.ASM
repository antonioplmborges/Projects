; CIS-261
;
; @topic W130105 Lab M10 demo program
; @brief Lab M10, <a href="http://www.c-jump.com/bcc/c261c/MLabs/M10arithmetic/lecture.html" target="_blank">Multiplication by Powers of 2</a>
;
; M10.ASM
;
; Assignment M10 
; High-speed Multiplication of 32-bit Integer by Powers of 2 
;

INCLUDE IO.H        ; header file for input/output

.386                ; Tells MASM to use Intel 80386 instruction set.
.MODEL FLAT         ; Flat memory model
option casemap:none ; Treat labels as case-sensitive

.CONST              ; Constant data segment
    PROMPT_MULTIPLIER	BYTE	"Enter multiplier: ", 0
	PROMPT_K_MULTPLC	BYTE	"Enter a single digit k-multiplicand: ", 0
	PROMPT_M_MULTPLC	BYTE	"Enter a signle digit m-multiplicand: ", 0
	PROMPT_N_MULTPLC	BYTE	"Enter a single digit n-multiplicand: ", 0
	PROMPT_BAD_INPUT    BYTE	"Sorry, your input was invalid, please repeat.", 0
	SZ_PAUSE            BYTE	"Please type x and hit Enter to exit: ", 0
	NUMERIC				BYTE	"Numeric: ", 0
	BINARY				BYTE	"Binary: ", 0
	ENDL				BYTE    13, 10, 0
    OVERFLOW			BYTE    "*** Bad format, please retry!", 0
    TXT_LINE			BYTE    "__________________________________________________________________", 0
    
.STACK 100h         ; (default is 1-kilobyte stack)

.DATA               ; Begin initialised data segment
    ; multiplier * ( 2^k + 2^m + 2^n ) = multiplier * 2^k + multiplier * 2^m + multiplier * 2^n
    multiplier      DWORD  7
    k_multiplicand  BYTE   0
    m_multiplicand  BYTE   0
    n_multiplicand  BYTE   0
    product         DWORD  ?

    ; memory for converting integers to text
    dtoa_buffer     BYTE    11 DUP (?), 0
    
    ; bit output buffer reserving space for 32 bits and 32 spaces
    bit_buffer      BYTE    64 dup(' '), 0

        
.CODE               ; Begin code segment
_main PROC          ; Main entry point into program

start_code:
@@:
	output PROMPT_MULTIPLIER
	input       bit_buffer, 12     ; 10 characters + CR, LF
    atod        bit_buffer         ; convert text to int -- result in EAX
    jno         @F                  ; if everything okay, continue
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
    jmp         @B 

@@:

	mov [multiplier], eax		; store multiplier in memory 
	output      ENDL
    
    
	
	mov [product], 0            ; clear up the result
	
	@@:
	output		PROMPT_K_MULTPLC
	input       bit_buffer, 12     ; 10 characters + CR, LF
	cmp			byte ptr [bit_buffer], "x"	; if user input 'x'
	je			m_multplc			; if true, mantain value of product and ask the user for m-multilicand
    atod        bit_buffer			; convert text to int -- result in EAX
    jno         @F                  ; if everything okay, continue
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
    jmp         @B 


	@@:
	mov [k_multiplicand], al	;store k-multiplicand in memory
	output      ENDL
	
	mov cl, [k_multiplicand]
	mov eax, [multiplier]       ; load the multiplier
    shl eax, cl                 ; multiplier * 2^k
    mov [product], eax          ; accumulate intermediate value

	m_multplc:
    @@:
	output		PROMPT_M_MULTPLC
	input       bit_buffer, 12     ; 10 characters + CR, LF
	cmp			byte ptr [bit_buffer], "x"	; if user input 'x'
	je			n_multplc			; if true, mantain value of product and ask the user for n-multilicand	
	atod        bit_buffer			; convert text to int -- result in EAX
    jno         @F                  ; if everything okay, continue
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
    jmp         @B 

	@@:
	mov [m_multiplicand], al	;store m-multiplicand in memory
	output      ENDL

	mov eax, [multiplier]       ; load the multiplier
    mov cl, [m_multiplicand]
    shl eax, cl                 ; multiplier * 2^m
    add [product], eax          ; accumulate intermediate value

	n_multplc:
	@@:
	output		PROMPT_N_MULTPLC
	input       bit_buffer, 12     ; 10 characters + CR, LF
	cmp			byte ptr [bit_buffer], "x"	; if user input 'x'
	je			multplc				; if true, mantain value of product and print it
    atod        bit_buffer         ; convert text to int -- result in EAX
    jno         @F                  ; if everything okay, continue
    output      PROMPT_BAD_INPUT    ; otherwise, bark at the user and repeat
    output      ENDL
    jmp         @B 


	@@:
	mov [n_multiplicand], al	;store n-multiplicand in memory
	output      ENDL

    mov eax, [multiplier]       ; load the multiplier
    mov cl, [n_multiplicand]
    shl eax, cl                 ; multiplier * 2^n
    add [product], eax          ; accumulate intermediate value

	multplc:
	mov eax, [product]	; store result in eax in order to compare
	; test overflow
	cmp [multiplier], eax
	jl @F
	output OVERFLOW
	output  ENDL
	jmp	start_code

@@:
    dtoa dtoa_buffer, [product] ; convert
    output NUMERIC
	output  dtoa_buffer         ; print numeric result
    output  ENDL                ; print new line 
	

	; display in binary form
    mov eax, [product]
    call eax_2_bit_buffer       ; convert EAX to binary string
    output BINARY				
	output  bit_buffer          ; print binary digits
    output  ENDL                ; print new line
	output TXT_LINE
	output  ENDL                ; print new line
   

	;--------------------------------------------------------
    ; Pause before exiting
    ;--------------------------------------------------------
    output      ENDL
	output	SZ_PAUSE
    input	bit_buffer, SIZEOF bit_buffer
    cmp     byte ptr [bit_buffer], "x"	; if user input 'x' exit program
	je		@F
	output  ENDL
	jmp		start_code				; otherwise restart
	
@@:
    ret

_main ENDP


; Procedure to calculate positions of white space
; Input is ECX, the position counter
; We want to insert space after every 4th binary digit
; The procedure returns CF (Carry Flag)
; CF=1 indicates the need to insert space
; CF=0 cleared otherwise
is_space_needed PROC
    push eax
    push edx
    push ecx
    mov         eax, ecx
    xor         edx, edx    ; set EDX = 0
    mov         ecx, 4
    div         ecx         ; DX = EAX % ECX, AX = EAX / ECX
    test        edx, edx  
    clc                     ; clear carry flag
    jne         @F
    ; result of div is zero
    stc                     ; set carry flag
@@:
    pop ecx
    pop edx
    pop eax
    ret
is_space_needed ENDP


; Procedure to convert EAX to bits in bit_buffer
; EAX contains integer to convert
eax_2_bit_buffer PROC
    push eax                ;  preserve registers
    push ecx
    push edx
    push esi
    mov ecx,32              ; number of bits in EAX
    mov esi, OFFSET bit_buffer ; Hardcoded (!) buffer location
next_bit:
    call is_space_needed    ; returns CF if extra space is needed
    jnc @F
    inc esi
@@:
    shl eax, 1              ; shift high bit into Carry flag
    mov BYTE PTR [esi], '0' ; display zero by default
    jnc next_byte           ; if no Carry, advance to next byte
    mov BYTE PTR [esi], '1' ; otherwise display 1
next_byte:
    inc esi                 ; next buffer position
    loop next_bit           ; shift another bit to left
    pop esi                 ; restore registers
    pop edx
    pop ecx
    pop eax
    ret
eax_2_bit_buffer ENDP


END _main       ; Marks the end of the module and sets the program entry point label
