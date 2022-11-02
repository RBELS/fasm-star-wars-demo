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

        stdcall getPos, Dest1Table, Dest1TableEnd, Stage1.dest1Pos
        invoke  glPopMatrix
        invoke  glPushMatrix
        invoke  glTranslatef, dword [Stage1.dest1Pos.x], dword [Stage1.dest1Pos.y], dword [Stage1.dest1Pos.z]
        stdcall drawDestroyer


        stdcall getPos, Dest2Table, Dest2TableEnd, Stage1.dest2Pos
        invoke  glPopMatrix
        invoke  glPushMatrix
        invoke  glTranslatef, dword [Stage1.dest2Pos.x], dword [Stage1.dest2Pos.y], dword [Stage1.dest2Pos.z]
        stdcall drawDestroyer


        stdcall getPos, Dest3Table, Dest3TableEnd, Stage1.dest3Pos
        invoke  glPopMatrix
        invoke  glPushMatrix
        invoke  glTranslatef, dword [Stage1.dest3Pos.x], dword [Stage1.dest3Pos.y], dword [Stage1.dest3Pos.z]
        stdcall drawDestroyer

        ;Draw tie fighter

        stdcall getPos, Tie1PosTable, Tie1PosTableEnd, Stage1.tie1Pos
        stdcall getPos, Tie1RotateTable, Tie1RotateTableEnd, Stage1.tie1Rot
        invoke  glPopMatrix
        invoke  glPushMatrix

        invoke  glTranslatef, dword [Stage1.tie1Pos.x], dword [Stage1.tie1Pos.y], dword [Stage1.tie1Pos.z]
        invoke  glScalef, 0.2, 0.2, 0.2

        ;ROTATE
        invoke  glRotatef, [Stage1.tie1Rot.x], 1.0, 0.0, 0.0
        invoke  glRotatef, [Stage1.tie1Rot.y], 0.0, 1.0, 0.0
        invoke  glRotatef, [Stage1.tie1Rot.z], 0.0, 0.0, 1.0

        stdcall drawTie

        ret
endp

