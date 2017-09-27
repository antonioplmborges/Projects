; The M13_SM_RUN.ASM file

.586P
.MODEL FLAT, stdcall     ; Flat memory model

EXTERN NEWARRAY@4:NEAR   ; This procedure is defined in M13_externs.cpp
EXTERN OUTPUTSZ@4:NEAR   ; This procedure is defined in M13_externs.cpp
EXTERN OUTPUTINT@4:NEAR   ; This procedure is defined in M13_externs.cpp
EXTERN strlen:NEAR       ; This procedure is part of the C standard library

EXTERN global_variable:DWORD    ; Sample global variable defined in M13_externs.cpp

PUBLIC SM_RUN            ; SM_RUN is externally visible to the linker

.const
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ; Constants corresponding to the command opcodes
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        COMMAND_NOP				EQU 0 
        COMMAND_PUSH_NUMBER		EQU 1
        COMMAND_PUSH_REGISTER	EQU 2
        COMMAND_ADD				EQU 3
		COMMAND_SUB				EQU 4
		COMMAND_MULT			EQU 5
		COMMAND_DIV				EQU 6
        COMMAND_HLT				EQU 7
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.data                   ; The data segment
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ; Table of procedure addresses invoked by the stack machine
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        call_table DWORD OFFSET nop_cmd
				   DWORD OFFSET push_cmd
				   DWORD OFFSET pushreg_cmd
                   DWORD OFFSET add_cmd
				   DWORD OFFSET sub_cmd
				   DWORD OFFSET mult_cmd
				   DWORD OFFSET	div_cmd
                   DWORD OFFSET hlt_cmd
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	sm_pointer DWORD 0
	sm_memory  DWORD 512 DUP (0)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.code                    ; Code segment begins
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Procedure for running the stack machine program
; Output: EAX is the status code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SM_RUN  PROC stack_machine_code:DWORD

		mov   eax, stack_machine_code

        ; Invoke procedures corresponding to particular opcodes
forever:
		mov     ebx, [ eax ]            ; get the opcode
		push    DWORD PTR [ eax + 4 ]   ; for each command push operand on stack
        call    call_table[ ebx * 4 ]   ; invoke command handler
        ;cmp     call_table[ ebx * 4 ], OFFSET hlt_cmd ; HALT?
        cmp     ebx, COMMAND_HLT
        je      getout                  ; Yes, we are done.
        add     eax, 8                  ; Advance to the next opcode
		jmp     forever

getout:
        mov DWORD PTR [global_variable], 456  ; Testing global variable
    ;    mov eax, 678                      ; Procedure return value
		mov edi, DWORD PTR[sm_pointer] ;load temp memory
		dec edi                        ; set index to the top element
		mov eax,sm_memory[edi*4]       ;store operand in temp memory
		ret
SM_RUN  ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the PUSH command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_PUSH_CMD BYTE "...push_cmd...", 13, 10, 0
.code
push_cmd PROC push_operand:DWORD
		pushad
		mov   edx, push_operand  ; get the operand from the stack
		; sm_memory[sm_pointer]= edx ;store value in temp memory
		;++sm_pointer
		mov edi, DWORD PTR[sm_pointer] ;load temp memory
		mov sm_memory[edi*4],edx ;store operand in temp memory
		inc DWORD PTR[sm_pointer]
        
        pushd OFFSET SZ_PUSH_CMD
        call  OUTPUTSZ@4    ; display text
        push  DWORD PTR [push_operand]
        call  OUTPUTINT@4    ; display text
        popad
        ret
push_cmd ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the ADD command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_ADD_CMD BYTE "...add_cmd...", 13, 10, 0
.code
add_cmd PROC push_operand:DWORD
        pushad
        ; push (pop()+pop())
		;        eax
		mov edi, DWORD PTR[sm_pointer] ;load temp memory
		dec edi						   ; index of existing element
		mov eax,sm_memory[edi*4] ;get top operand
		dec edi							; index of second element
		add sm_memory[edi*4],eax
		dec DWORD PTR[sm_pointer]

        
        pushd OFFSET SZ_ADD_CMD
        call  OUTPUTSZ@4    ; display text
        popad
        ret
add_cmd ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the SUB command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_SUB_CMD BYTE "...sub_cmd...", 13, 10, 0
.code
sub_cmd PROC push_operand:DWORD
        pushad
		 ; push (pop()-pop())
		;        eax
		mov edi, DWORD PTR[sm_pointer] ;load temp memory
		dec edi							; index of existing element
		mov eax,sm_memory[edi*4]		;get top operand
		dec edi							; index of second element
		sub sm_memory[edi*4], eax          ;subtract from first integer
		dec DWORD PTR[sm_pointer]
        pushd OFFSET SZ_SUB_CMD
        call  OUTPUTSZ@4    ; display text
        popad
        ret
sub_cmd ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the mult command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_MULT_CMD BYTE "...mult_cmd...", 13, 10, 0
.code
mult_cmd PROC push_operand:DWORD
        pushad
		 ; push (pop()*pop())
		;        eax
		mov edi, DWORD PTR[sm_pointer] ;load temp memory
		dec edi							; index of existing element
		mov eax,sm_memory[edi*4]		;get top operand
		dec edi							; index of second element
		mov ebx,sm_memory[edi*4]
		xor edx,edx
		imul ebx                       ;multiply times first integer
		mov sm_memory[edi*4],eax       ;store result of multiplication
		dec DWORD PTR[sm_pointer]
        pushd OFFSET SZ_MULT_CMD
        call  OUTPUTSZ@4    ; display text
        popad
        ret
mult_cmd ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the div command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_DIV_CMD BYTE "...div_cmd...", 13, 10, 0
.code
div_cmd PROC push_operand:DWORD
        pushad
		 ; push (pop()/pop())
		;        eax
		mov edi, DWORD PTR[sm_pointer] ;load temp memory
		dec edi							; index of existing element
		mov eax,sm_memory[edi*4]		;get top operand
		dec edi							; index of second element
		mov ebx,sm_memory[edi*4]
		xor edx,edx
		idiv ebx                       ;multiply times first integer
		mov sm_memory[edi*4],eax       ;store result of division
		dec DWORD PTR[sm_pointer]
        pushd OFFSET SZ_DIV_CMD
        call  OUTPUTSZ@4				; display text
        popad
        ret
div_cmd ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the NOP command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_NOP_CMD BYTE "...nop_cmd...", 13, 10, 0
.code
nop_cmd PROC push_operand:DWORD
        pushad
        pushd OFFSET SZ_NOP_CMD
        call  OUTPUTSZ@4    ; display text
        popad
        ret
nop_cmd ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the HLT command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_HLT_CMD BYTE "...hlt_cmd...", 13, 10, 0
.code
hlt_cmd PROC push_operand:DWORD
        pushad
        pushd OFFSET SZ_HLT_CMD
        call  OUTPUTSZ@4    ; display text
        popad
        ret
hlt_cmd ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Sample procedure handling the PUSH REG command
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.const
        SZ_PUSHREG_CMD BYTE "...pushreg_cmd...", 13, 10, 0
.code
pushreg_cmd PROC push_operand:DWORD
        pushad
        pushd OFFSET SZ_PUSHREG_CMD
        call  OUTPUTSZ@4    ; display text
        popad
        ret
pushreg_cmd ENDP

END

