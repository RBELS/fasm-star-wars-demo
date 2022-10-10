proc addVecQ uses edx ecx, vec1, vec2

        mov     ecx, [vec1]
        mov     edx, [vec2]
        fld     qword [edx]
        fadd    qword [ecx]
        fstp    qword [ecx]

        fld     qword [edx+8]
        fadd    qword [ecx+8]
        fstp    qword [ecx+8]

        fld     qword [edx+16]
        fadd    qword [ecx+16]
        fstp    qword [ecx+16]

        ret
endp

proc addVecF uses edx ecx, vec1, vec2

        mov     ecx, [vec1]
        mov     edx, [vec2]
        fld     dword [edx]
        fadd    dword [ecx]
        fstp    dword [ecx]

        fld     dword [edx+4]
        fadd    dword [ecx+4]
        fstp    dword [ecx+4]

        fld     dword [edx+8]
        fadd    dword [ecx+8]
        fstp    dword [ecx+8]

        ret
endp


proc    mulVecD uses ebx ecx, vec, coeff

        mov     ebx, [vec]
        mov     ecx, 3
.mulLoop:
        fld     qword [ebx]
        fmul    qword [coeff]
        fstp    qword [ebx]

        add     ebx, 8
        loop    .mulLoop

        ret
endp


proc    mulVecF uses ebx ecx, vec, coeff

        mov     ebx, [vec]
        mov     ecx, 3
.mulLoop:
        fld     dword [ebx]
        fmul    dword [coeff]
        fstp    dword [ebx]

        add     ebx, 4
        loop    .mulLoop

        ret
endp


proc    genVecF uses ebx ecx, addr

        mov     ebx, [addr]
        mov     ecx, 3
.GenLoop:

        stdcall Random.GetFloat
        mov     [ebx], eax

        add     ebx, 4
        loop    .GenLoop

        ret
endp




proc    normalizeVecD uses ebx ecx edx, vec
        local sum: QWORD

        mov     ebx, [vec]
        mov     ecx, 3
        mov     edx, 0
.CountLoop:

        fld1
        fmul    qword [ebx+edx]
        fmul    qword [ebx+edx]

        add     edx, 8
        loop    .CountLoop

        faddp
        faddp
        fsqrt
        fstp    qword [sum]

        mov     ecx, 3
        mov     edx, 0
.DivLoop:
        fld     qword [ebx+edx]
        fdiv    qword[sum]
        fstp    qword [ebx+edx]

        add     ebx, 8
        loop    .DivLoop

        ret
endp


proc    normalizeVecF uses ebx ecx edx, vec
        local sum: DWORD

        mov     ebx, [vec]
        mov     ecx, 3
        mov     edx, 0
.CountLoop:

        fld1
        fmul    dword [ebx+edx]
        fmul    dword [ebx+edx]

        add     edx, 4
        loop    .CountLoop

        faddp
        faddp
        fsqrt

        fstp    dword [sum]

        mov     ecx, 3
        mov     edx, 0
.DivLoop:
        fld     dword [ebx+edx]
        fdiv    dword [sum]
        fstp    dword [ebx+edx]

        add     edx, 4
        loop    .DivLoop

        ret
endp


proc    getDeltaTicksFloat

        fld     dword [ticksFloat]
        fsub    dword [startTicksFloat]
        push    0
        fstp    dword [esp]
        pop     eax

        ret
endp


;       f1 < f2 -> -1
;       f1 > f2 ->  1
;       f1 = f2 ->  0
proc    cmpFloats, f1, f2

        fld     dword [f1]
        fcomp   dword [f2]
        fstsw   ax

.EQUAL:
        test    ah, $40
        jz      .LESS
        mov     eax, 0
        jmp     .ENDIF
.LESS:
        test    ah, $01
        jz      .GREATER
        mov     eax, -1
        jmp     .ENDIF
.GREATER:
        mov     eax, 1
.ENDIF:

        ret
endp