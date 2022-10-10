STAGE1_BEGIN    equ     0.0
STAGE1_END      equ     100.0

proc    getStage uses edx

        fld     dword [ticksFloat]
        ;push     11.0
        ;fld      dword [esp]
        ;pop      edx

.CASE_STAGE1:
        push    STAGE1_END
        fcom    dword [esp]
        pop     eax
        fstsw   ax

        test    ah, 1
        je     .CASE_STAGE0

        mov     eax, 1
        jmp     .CASE_END
.CASE_STAGE0:
        xor     eax, eax
.CASE_END:

        push    0
        fstp    dword [esp]
        pop     edx

        ret
endp