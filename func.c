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

proc addVecFtoD uses ecx esi edi, dest, src

        mov     esi, [src]
        mov     edi, [dest]
        mov     ecx, 3
.addLoop:
        fld     qword [edi]
        fadd    dword [esi]
        fstp    qword [edi]

        add     esi, 4
        add     edi, 8
        loop    .addLoop

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


proc    translateVecD uses ebx, camVec, addX: QWORD, addY: QWORD, addZ:QWORD

        mov     ebx, [camVec]

        fld     qword [addX]
        fmul    dword [deltaTicksFloat]
        fadd    qword [ebx]
        fstp    qword [ebx]

        fld     qword [addY]
        fmul    dword [deltaTicksFloat]
        fadd    qword [ebx+8]
        fstp    qword [ebx+8]

        fld     qword [addZ]
        fmul    dword [deltaTicksFloat]
        fadd    qword [ebx+16]
        fstp    qword [ebx+16]

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


proc    movQWord, q1, q2, dest

        mov     ebx, [dest]

        mov     eax, [q1]
        mov     dword [ebx], eax

        mov     eax, [q2]
        mov     dword [ebx+4], eax


        ret
endp

proc rotateXYZF, vec, newVec, angleX, angleY, angleZ

        stdcall degToRad, [angleX]
        stdcall rotateX, [vec], [newVec], eax
        stdcall copyVecFtoF, rotateXYZF.bufVec, [newVec]

        stdcall degToRad, [angleY]
        stdcall rotateY, rotateXYZF.bufVec, [newVec], eax
        stdcall copyVecFtoF, rotateXYZF.bufVec, [newVec]

        stdcall degToRad, [angleZ]
        stdcall rotateZ, rotateXYZF.bufVec, [newVec], eax

        ret
endp

proc rotateZ uses ecx ebx esi edi, vec, newVec, angle

        lea     ebx, [vec]
        lea     ecx, [newVec]
        mov     esi, [ebx]
        mov     edi, [ecx]

        fld     dword [angle]
        fsincos

        fld     dword [esi]
        fmul    st0, st1
        fld     dword [esi+4]
        fmul    st0, st3
        fchs

        fadd    st0, st1

        fstp    dword [edi]
        push    0
        fstp    dword [esp]

        fld     dword [esi]
        fmul    st0, st2
        fld     dword [esi+4]
        fmul    st0, st2

        fadd    st0, st1
        fstp    dword [edi+4]
        fstp    dword [esp]

        mov     eax, [esi+8]
        mov     [edi+8], eax

        fstp    dword [esp]
        fstp    dword [esp]

        pop     eax

        ret
endp

proc rotateX uses ecx ebx esi edi, vec, newVec, angle

        lea     ebx, [vec]
        lea     ecx, [newVec]
        mov     esi, [ebx]
        mov     edi, [ecx]

        fld     dword [angle]
        fsincos

        mov     eax, [esi]
        mov     [edi], eax

        fld     dword [esi+4]
        fmul    st0, st1
        fld     dword [esi+8]
        fmul    st0, st3
        fchs

        fadd    st0, st1
        fstp    dword [edi+4]
        push    0
        fstp    dword [esp]

        fld     dword [esi+4]
        fmul    st0, st2
        fld     dword [esi+8]
        fmul    st0, st2

        fadd    st0, st1
        fstp    dword [edi+8]

        fstp    dword [esp]
        fstp    dword [esp]
        fstp    dword [esp]

        pop     eax

        ret
endp


proc rotateY uses ecx ebx esi edi, vec, newVec, angle


        lea     ebx, [vec]
        lea     ecx, [newVec]
        mov     esi, [ebx]
        mov     edi, [ecx]

        fld     dword [angle]
        fsincos

        fld     dword [esi]
        fmul    st0, st1
        fld     dword [esi+8]
        fmul    st0, st3

        fadd    st0, st1

        fstp    dword [edi]
        push    0
        fstp    dword [esp]

        mov     eax, dword [esi+4]
        mov     dword [edi+4], eax

        fld     dword [esi]
        fmul    st0, st2
        fchs
        fld     dword [esi+8]
        fmul    st0, st2
        fadd    st0, st1

        fstp    dword [edi+8]

        fstp    dword [esp]
        fstp    dword [esp]
        fstp    dword [esp]

        pop     eax

        ret
endp

proc copyVecFtoF uses ecx esi edi, dest, src

        mov     esi, [src]
        mov     edi, [dest]

        mov     ecx, 3
        rep     movsd

        ret
endp

proc copyVecFtoD uses ecx esi edi, dest, src

        mov     esi, [src]
        mov     edi, [dest]
        mov     ecx, 3
.copyLoop:
        fld     dword [esi]
        fstp    qword [edi]

        add     esi, 4
        add     edi, 8
        loop    .copyLoop

        ret
endp

proc degToRad, deg

        fldpi
        fmul    dword [deg]
        push    180.0
        fdiv    dword [esp]
        fstp    dword [esp]
        pop     eax

        ret
endp

proc setCameraToTie

        stdcall rotateXYZF, ozVec, watchVec, [Stage1.tie1Rot.x], [Stage1.tie1Rot.y], [Stage1.tie1Rot.z]
        ;stdcall copyVecFtoF, watchVec, ozVec

        ;stdcall degToRad, dword [Stage1.tie1Rot.y]
        ;stdcall rotateY, ozVec, watchVec, eax
        stdcall mulVecF, watchVec, 5.0

        stdcall copyVecFtoD, Stage1.cameraPos, Stage1.tie1Pos

        stdcall addVecFtoD, Stage1.cameraPos, watchVec
        stdcall addVecFtoD, Stage1.cameraPos, Stage1.upVecF

        stdcall copyVecFtoD, Stage1.pointPos, Stage1.tie1Pos

        ret
endp

