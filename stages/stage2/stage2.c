proc    drawStage2

        invoke  glMatrixMode, GL_MODELVIEW

        invoke  glLoadIdentity
        invoke  gluLookAt, double 0.0, double 5.0, double 20.0,\
                           double 0.0, double 0.0, double 0.0,\
                           double 0.0, double 1.0, double 0.0

        stdcall Stars.Draw, starsData

        ret
endp