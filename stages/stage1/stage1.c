proc    drawStage1
        local   speedEnd: DWORD
        ;get velocity

        stdcall getPosD, Tie1PosTable, Tie1PosTableEnd, Stage1.tie1Pos
        stdcall getPosF, Tie1RotateTable, Tie1RotateTableEnd, Stage1.tie1Rot

        stdcall getPosF, Dest1Table, Dest1TableEnd, Stage1.dest1Pos
        stdcall getPosF, Dest2Table, Dest2TableEnd, Stage1.dest2Pos
        stdcall getPosF, Dest3Table, Dest3TableEnd, Stage1.dest3Pos

        ;Move camera
        ;stdcall setCameraToTie


        invoke  glMatrixMode, GL_PROJECTION
        invoke  glLoadIdentity
        invoke  gluPerspective, double FOV, double [aspect], double Z_NEAR, double Z_FAR


        ;stdcall getPosF, TestCamPosTable, TestCamPosTableEnd, Stage1.cameraPosF
        ;stdcall copyVecFtoD, Stage1.cameraPos, Stage1.cameraPosF

        ;create and push view matrix
        invoke  glMatrixMode, GL_MODELVIEW
        invoke  glLoadIdentity


        stdcall setCameraToTie
        invoke  gluLookAt, double [Stage1.cameraPos.x], double [Stage1.cameraPos.y], double [Stage1.cameraPos.z],\
                           double [Stage1.pointPos.x], double [Stage1.pointPos.y], double [Stage1.pointPos.z],\
                           double 0.0, double 1.0, double 0.0
        invoke  glPushMatrix
        invoke  glPushMatrix
        invoke  glPushMatrix
        invoke  glPushMatrix

        stdcall Stars.Draw, starsData


        ;DESTROYER 1
        invoke  glPopMatrix
        invoke  glTranslatef, dword [Stage1.dest1Pos.x], dword [Stage1.dest1Pos.y], dword [Stage1.dest1Pos.z]
        stdcall drawDestroyer
        ;DESTROYER 1 END

        ;DESTROYER 2
        invoke  glPopMatrix
        invoke  glTranslatef, dword [Stage1.dest2Pos.x], dword [Stage1.dest2Pos.y], dword [Stage1.dest2Pos.z]
        stdcall drawDestroyer
        ;DESTROYER 2 END

        ;DESTROYER 3
        invoke  glPopMatrix
        invoke  glTranslatef, dword [Stage1.dest3Pos.x], dword [Stage1.dest3Pos.y], dword [Stage1.dest3Pos.z]
        stdcall drawDestroyer
        ;DESTROYER 3 END

        invoke  glPopMatrix
        invoke  glTranslated, double [Stage1.tie1Pos.x], double [Stage1.tie1Pos.y], double [Stage1.tie1Pos.z]
        invoke  glScalef, 0.2, 0.2, 0.2

        ;TIE 1 ROTATE
        invoke  glRotatef, dword [Stage1.tie1Rot.x], 1.0, 0.0, 0.0
        invoke  glRotatef, dword [Stage1.tie1Rot.y], 0.0, 1.0, 0.0
        invoke  glRotatef, dword [Stage1.tie1Rot.z], 0.0, 0.0, 1.0
        ;invoke  glPopMatrix
        ;invoke  glPushMatrix

        stdcall drawTie


        ret
endp

