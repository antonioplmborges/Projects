.386                ; Tells MASM to use Intel 80386 instruction set.
.MODEL FLAT         ; Flat memory model
option casemap:none ; Treat labels as case-sensitive

.CONST              ; Constant data segment
ENDL              BYTE 13, 10, 0
BAD_INPUT         BYTE "Bad Input", 0
OOUTPUT_PAUSE     BYTE "Please type x and hit Enter to exit: ", 0


.DATA               ; Begin initialized data segment
    op1   QWORD 0A2B2A40675981234h ; first 64-bit operand for addition
	            ;|_EBX___|_EAX__|

    op2   QWORD 08010870001234502h ; second 64-bit operand for addition
		        ;|_EDX___|_ECX__|

    sum   DWORD 3 dup(?)           ; 96-bit sum = ????????????????????????h
	                               ;              36 57 bb 76 06 2b c3 22 00 00 00 00
	                               ;              00000000 22c32b06 76bb5736

    op3   DWORD 3 dup(2)           ; 96-bit oper to sub  20000000200000002h
                                   ; Result sum = ????????????????????????h
								   ;              34 57 bb 76 04 2b c3 22 01 00 00 00
								   ;              00000001 22c32b04 76bb5734

.CODE               ; Begin code segment
_main PROC          ; Beginning of code

    mov ebx, DWORD PTR [op1+4]
	mov eax, DWORD PTR [op1+0]

    mov edx, DWORD PTR [op2+4]
	mov ecx, DWORD PTR [op2+0]           

	; We want whats below to happen
	; EBX:EAX = EBX:EAX + EDX:ECX

	add eax, ecx ; Now EAX = EAX + ECX -------- which is the lower portion of the sum & CF is set
	adc ebx, edx ; Now EBX = EBX + EDX + CF --- which is the higher portion of the sum & CF is set
	
	    ;              Low=EAX  Mid=EBX  High=CF
	    ; 96-bit sum = ???????? ???????? ????????h
	    ;              |        |        |
    ;	[sum+8]--------|--------|--------'
    ;	[sum+4]--------|--------'
    ;   [sum+0]--------'

    mov DWORD PTR [sum+0], eax ; low
	mov DWORD PTR [sum+4], ebx ; middle
	mov DWORD PTR [sum+8], 0   ; high
	adc DWORD PTR [sum+8], 0

	; Compute sum = (sum - op3)

	mov eax, DWORD PTR [sum + 0] ; low
	mov ebx, DWORD PTR [op3 + 0] ; low
	sub eax, ebx                 ; EAX = EAX - EBX
	mov DWORD PTR [sum + 0], eax ; Store the low part

    mov eax, DWORD PTR [sum + 4] ; middle
	mov ebx, DWORD PTR [op3 + 4] ; middle
	sbb eax, ebx                 ; EAX = EAX - EBX - CF
	mov DWORD PTR [sum + 4], eax ; Store the low part

	mov eax, DWORD PTR [sum + 8] ; High
	mov ebx, DWORD PTR [op3 + 8] ; High
	sbb eax, ebx                 ; EAX = EAX - EBX - CF
	mov DWORD PTR [sum + 8], eax ; Store the high part

	ret

_main ENDP
END _main        ; Marks the end of the module and sets the program entry point label

antonioplmborges@gmail.com