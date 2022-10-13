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




proc    Stars.Draw uses ebx ecx edx, starsData

        invoke  glPointSize, 1.0
        invoke  glEnable, GL_POINT_SMOOTH
        invoke  glEnableClientState, GL_VERTEX_ARRAY

        invoke  glVertexPointer, 3, GL_FLOAT, 0, [starsData]


        invoke  glColor3f, 1.0, 1.0, 1.0
        invoke  glDrawArrays, GL_POINTS, 0, STARS_COUNT/2


        invoke  glColor3f, 0.4, 0.4, 0.6
        invoke  glDrawArrays, GL_POINTS, STARS_COUNT/4, STARS_COUNT/2

        invoke  glColor3f, 0.4, 0.4, 0.6
        invoke  glDrawArrays, GL_POINTS, STARS_COUNT/2, STARS_COUNT/4

        invoke  glColor3f, 0.6, 0.4, 0.4
        invoke  glDrawArrays, GL_POINTS, STARS_COUNT*3/4, STARS_COUNT/4

        invoke  glDisableClientState, GL_VERTEX_ARRAY

        ret
endp