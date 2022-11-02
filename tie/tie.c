proc    drawTie

        invoke  glEnable, GL_NORMALIZE
        invoke  glEnable, GL_LIGHTING
        invoke  glEnable, GL_LIGHT0
        invoke  glLightfv, GL_LIGHT0, GL_DIFFUSE, light0Diffuse

        invoke  glLightfv, GL_LIGHT0, GL_POSITION, light0Position

        invoke  glEnableClientState, GL_VERTEX_ARRAY
        invoke  glEnableClientState, GL_NORMAL_ARRAY

        invoke  glColor3f, 0.5, 0.5, 1.0
        invoke  glVertexPointer, 3, GL_FLOAT, 3*4, tieVertices+16
        invoke  glNormalPointer, GL_FLOAT, 3*4, tieNormals+16

        invoke  glDrawArrays, GL_TRIANGLES, 0, (tieVerticesEnd-tieVertices-16)/4/3

        invoke  glDisableClientState, GL_VERTEX_ARRAY
        invoke  glDisableClientState, GL_NORMAL_ARRAY
        invoke  glDisable, GL_LIGHTING

        ret
endp