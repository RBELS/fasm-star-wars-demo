proc    drawStage1
        local   speedEnd: DWORD
        ;get velocity

.BEFORE_EXIT1:
        stdcall cmpFloats, dword [ticksFloat], 10.0
        cmp     al, 1
        je      .EXITTING1

        mov     dword [Stage1.dest1V], 0.0

        jmp     .SWITCH_END1
.EXITTING1:
        stdcall cmpFloats, dword [ticksFloat], 13.2
        cmp     al, 1
        je      .AFTER_EXIT1

        mov     dword [Stage1.dest1V], 300.0

        jmp     .SWITCH_END1
.AFTER_EXIT1:
        mov     dword [Stage1.dest1V], 0.2
.SWITCH_END1:



.BEFORE_EXIT2:
        stdcall cmpFloats, dword [ticksFloat], 20.0
        cmp     al, 1
        je      .EXITTING2

        mov     dword [Stage1.dest2V], 0.0

        jmp     .SWITCH_END2
.EXITTING2:
        stdcall cmpFloats, dword [ticksFloat], 23.2
        cmp     al, 1
        je      .AFTER_EXIT2

        mov     dword [Stage1.dest2V], 300.0

        jmp     .SWITCH_END2
.AFTER_EXIT2:
        mov     dword [Stage1.dest2V], 0.2
.SWITCH_END2:


.BEFORE_EXIT3:
        stdcall cmpFloats, dword [ticksFloat], 30.0
        cmp     al, 1
        je      .EXITTING3

        mov     dword [Stage1.dest3V], 0.0

        jmp     .SWITCH_END3
.EXITTING3:
        stdcall cmpFloats, dword [ticksFloat], 33.2
        cmp     al, 1
        je      .AFTER_EXIT3

        mov     dword [Stage1.dest3V], 300.0

        jmp     .SWITCH_END3
.AFTER_EXIT3:
        mov     dword [Stage1.dest3V], 0.2
.SWITCH_END3:





        stdcall moveDest, Stage1.dest1Z, dword [Stage1.dest1V]
        stdcall moveDest, Stage1.dest2Z, dword [Stage1.dest2V]
        stdcall moveDest, Stage1.dest3Z, dword [Stage1.dest3V]

        invoke  glMatrixMode, GL_PROJECTION
        invoke  glLoadIdentity
        invoke  gluPerspective, double FOV, double [aspect], double Z_NEAR, double Z_FAR



        ;create and push view matrix

        invoke  glMatrixMode, GL_MODELVIEW
        invoke  glLoadIdentity
        invoke  gluLookAt, double 30.0, double 5.0, double 50.0,\
                           double 0.0, double 0.0, double 0.0,\
                           double 0.0, double 1.0, double 0.0

        invoke  glPushMatrix
        ;create and push view matrix


        stdcall Stars.Draw, vertice, STARS_COUNT


        invoke  glTranslatef, -20.0, -10.0, dword [Stage1.dest1Z]

        stdcall drawDestroyer



        ;DESTROYERS 2 AND 3

        invoke  glPopMatrix
        invoke  glPushMatrix
        invoke  glTranslatef, -60.0, 0.0, dword [Stage1.dest2Z]
        stdcall drawDestroyer


        invoke  glPopMatrix
        invoke  glTranslatef, 15.0, 0.0, dword [Stage1.dest3Z]
        stdcall drawDestroyer

        ret
endp

proc    moveDest uses ebx, destPosZ, destV

        mov     ebx, dword [destPosZ]

        fld     dword [deltaTicksFloat]
        fmul    dword [destV]
        fadd    dword [ebx]
        fstp    dword [ebx]

        ret
endp