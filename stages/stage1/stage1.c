proc    drawStage1
        local   speedEnd: DWORD

        local   testF: DWORD
        mov     [testF], 0.1

        mov     [speedEnd], 5.0




        invoke  glMatrixMode, GL_PROJECTION
        invoke  glLoadIdentity
        invoke  gluPerspective, double FOV, double [aspect], double Z_NEAR, double Z_FAR



        invoke  glMatrixMode, GL_MODELVIEW
        invoke  glLoadIdentity
        invoke  gluLookAt, double 30.0, double 5.0, double 50.0,\
                           double 0.0, double 0.0, double 0.0,\
                           double 0.0, double 1.0, double 0.0

        invoke  glPushMatrix
        stdcall Stars.Draw, vertice, STARS_COUNT






        invoke  glTranslatef, -20.0, -10.0, dword [Stage1.dest1Z]

        stdcall drawDestroyer



        ;DESTROYERS 2 AND 3

        ;invoke  glPopMatrix
        ;invoke  glPushMatrix
        ;invoke  glTranslatef, -60.0, 0.0, -50.0
        ;stdcall drawDestroyer
        ;invoke  glPopMatrix
        ;invoke  glTranslatef, 15.0, 0.0, -15.0
        ;stdcall drawDestroyer

        ret
endp