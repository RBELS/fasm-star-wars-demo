proc    Stars.Init uses edx ecx, starsData, starsCount

        mov     edx, [starsData]
        mov     ecx, STARS_COUNT
.GenLoop:
        push    cx
        stdcall genVecF, edx
        stdcall normalizeVecF, edx
        stdcall mulVecF, edx, 100.0
        pop     cx

        add     edx, 12
        loop    .GenLoop

        ret
endp




proc    Stars.Draw uses ebx ecx, starsData, starsCount

        invoke  glPointSize, 1.0
        invoke  glEnable, GL_POINT_SMOOTH
        invoke  glEnableClientState, GL_VERTEX_ARRAY

        invoke  glVertexPointer, 3, GL_FLOAT, 0, [starsData]
        invoke  glColor3f, 1.0, 1.0, 1.0

        invoke  glDrawArrays, GL_POINTS, 0, [starsCount]

        invoke  glDisableClientState, GL_VERTEX_ARRAY

        ret
endp