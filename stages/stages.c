STAGE1_BEGIN    equ     0.0
STAGE1_END      equ     400.0

STAGE2_BEGIN    equ     300.0
STAGE2_END      equ     500.0

proc    getStage uses edx

.CASE_STAGE1:
        stdcall cmpFloats, dword [ticksFloat], STAGE1_END

        cmp    al, 1
        je     .CASE_STAGE2

        mov     eax, 1
        jmp     .CASE_END

.CASE_STAGE2:
        stdcall cmpFloats, dword [ticksFloat], STAGE2_END
        cmp     al, 1
        je      .CASE_STAGE0

        mov     eax, 2
        jmp     .CASE_END

.CASE_STAGE0:
        xor     eax, eax
.CASE_END:

        push    0
        fstp    dword [esp]
        pop     edx

        ret
endp