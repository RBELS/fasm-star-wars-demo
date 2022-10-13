

proc    getIndex uses ecx edx ebx, tableStart, tableEnd

        mov     ebx, [tableStart]
        xor     edx, edx
.findLoop:

        stdcall cmpFloats, dword [ticksFloat], dword [ebx]
        cmp     al, -1
        je      .endFindLoop

        inc     edx
        add     ebx, 4*4


        mov  ecx, [tableEnd] ;can be error
        sub  ecx, 4

        cmp     ebx, ecx
        ja      .noResult

        jmp     .findLoop
.noResult:
        mov     edx, -1
        jmp     .noDec
.endFindLoop:
        dec     edx
.noDec:
        mov     eax, edx

        ret
endp


proc    getPos uses eax ecx edx ebx es esi edi, table, tableEnd, vector
        local   speedVec[3]: DWORD
        local   indent:      DWORD

        stdcall getIndex, dword [table], dword [tableEnd]

        cmp     eax, -1
        je      .PROC_END

        imul    eax, 16
        add     eax, [table]; param2
        push    eax
        ;first vector

        mov     ebx, eax
        add     ebx, 16
        ;second vector

        mov     dword [indent], 0
        mov     ecx, 3

        fld     dword [ebx]
        fsub    dword [eax]
        add     eax, 4
        add     ebx, 4
.getSpeedLoop:
        fld     dword [ebx]
        fsub    dword [eax]
        fdiv    st0, st1

        push    ecx
        lea     ecx, [speedVec]
        add     ecx, [indent]
        fstp    dword [ss:ecx]
        pop     ecx

        add     eax, 4
        add     ebx, 4
        add     [indent], 4
        loop    .getSpeedLoop

        ffree   st0


        fld     dword [ticksFloat]
        pop     eax
        push    dword [eax]
        fsub    dword [esp]
        pop     ecx
        add     eax, 4
        ;first vector

        mov     ecx, 3
        lea     ebx, [speedVec]
.mulLoop:
        fld     dword [ebx]
        fmul    st0, st1
        fadd    dword [eax]
        fstp    dword [ebx]

        add     ebx, 4
        add     eax, 4
        loop    .mulLoop
        ffree   st0

        ;copy to addr
        push    ds ds ss
        pop     ds
        lea     esi, [speedVec]
        pop     es

        mov     edi, [vector]
        mov     ecx, 3
        rep     movsd
        pop     ds

.PROC_END:

        ret
endp