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

.BEFORE_MOVE:
        stdcall cmpFloats, dword [ticksFloat], 50.0
        cmp     al, 1
        je      .MOVE1

        jmp     .SWITCH_CAM_END
.MOVE1:
        stdcall cmpFloats, dword [ticksFloat], 90.0
        cmp     al, 1
        je      .MOVE2

        stdcall translateVecD, Stage1.cameraPos, double 0.5, double 0.5, double 0.2


        jmp     .SWITCH_CAM_END
.MOVE2:
        stdcall cmpFloats, dword [ticksFloat], 150.0
        cmp     al, 1
        je      .MOVE3

        stdcall translateVecD, Stage1.cameraPos, double -0.8, double -0.1, double 0.2
        stdcall translateVecD, Stage1.pointPos,  double 0.0, double 0.0, double 0.6

        jmp     .SWITCH_CAM_END
.MOVE3:
        ;stdcall cmpFloats, dword [ticksFloat], 200.0
        ;cmp     al, 1
        ;je      .NEXT

        stdcall translateVecD, Stage1.cameraPos, double -0.02, double -0.05, double 0.4
        stdcall translateVecD, Stage1.pointPos,  double 0.0, double 0.0, double 0.2
.SWITCH_CAM_END:

        ;stdcall movQWord, double 30.0, Stage1.cameraPos.x

        invoke  gluLookAt, double [Stage1.cameraPos.x], double [Stage1.cameraPos.y], double [Stage1.cameraPos.z],\
                           double [Stage1.pointPos.x], double [Stage1.pointPos.y], double [Stage1.pointPos.z],\
                           double 0.0, double 1.0, double 0.0

        invoke  glPushMatrix
        ;create and push view matrix

        ;invoke  glTranslatef, 0.0, 0.0, dword [Stage1.cameraPos.z]
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
