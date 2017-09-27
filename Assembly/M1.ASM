
; CIS-261
; your_program_name.asm
; Brief description of what the program does

.586                ; Tells MASM to use Intel 80386 instruction set.
.MODEL FLAT         ; Flat memory model
option casemap:none ; Treat labels as case-sensitive

.CONST          ; Constant data segment

.STACK 100h     ; (default is 1-kilobyte stack)

.DATA           ; Begin initialized data segment

	count   DWORD 77778888h
    
.CODE           ; Begin code segment
_main PROC      ; Beginning of code

	mov [count], 11112222h        ; store value 11112222h in memory pointed by label count
	mov EBX, [count]              ; get value at count and put it in EBX
	mov EBX, OFFSET count         ; load "address of" count into EBX
	mov DWORD PTR [EBX], 33334444h ; use EBX as memory address and store 789 there

    ret
    
_main ENDP
END _main       ; Marks the end of the module and sets the program entry point label
