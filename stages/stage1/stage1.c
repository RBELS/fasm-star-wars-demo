proc    drawStage1
        local   speedEnd: DWORD
        ;get velocity






        invoke  glMatrixMode, GL_PROJECTION
        invoke  glLoadIdentity
        invoke  gluPerspective, double FOV, double [aspect], double Z_NEAR, double Z_FAR



        ;create and push view matrix
        invoke  glMatrixMode, GL_MODELVIEW
        invoke  glLoadIdentity




        invoke  gluLookAt, double [Stage1.cameraPos.x], double [Stage1.cameraPos.y], double [Stage1.cameraPos.z],\
                           double [Stage1.pointPos.x], double [Stage1.pointPos.y], double [Stage1.pointPos.z],\
                           double 0.0, double 1.0, double 0.0

        invoke  glPushMatrix
        ;create and push view matrix

        ;invoke  glTranslatef, 0.0, 0.0, dword [Stage1.cameraPos.z]
        stdcall Stars.Draw, starsData


        invoke  glTranslatef, -20.0, -10.0, dword [Stage1.dest1Z]

        stdcall drawDestroyer

        ret
endp

