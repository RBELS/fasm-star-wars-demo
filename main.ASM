
; OpenGL programming example

format PE GUI 4.0
entry start

FOV             =       50.0
Z_NEAR          =       0.1
Z_FAR           =       250.0
STARS_COUNT     =       1024*20

include 'win32ax.inc'
include 'opengl.inc'

section '.text' code readable executable

  start:

        invoke  GetModuleHandle,0
        mov     [wc.hInstance],eax
        invoke  LoadIcon,0,IDI_APPLICATION
        mov     [wc.hIcon],eax
        mov     [wc.hCursor], NULL

        stdcall initScreenFields
        invoke  RegisterClass,wc
        invoke  CreateWindowEx,0,_class,_title,WS_VISIBLE+WS_POPUP,0,0,[Screen.width],[Screen.height],NULL,NULL,[wc.hInstance],NULL
        mov     [hwnd],eax

        stdcall Ticks.Init
        stdcall Random.Init

        stdcall Stars.Init, starsData, STARS_COUNT



  msg_loop:
        invoke  GetMessage,msg,NULL,0,0
        or      eax,eax
        jz      end_loop
        invoke  TranslateMessage,msg
        invoke  DispatchMessage,msg
        jmp     msg_loop

  end_loop:
        invoke  ExitProcess,[msg.wParam]

proc WindowProc uses ebx esi edi, hwnd,wmsg,wparam,lparam
        cmp     [wmsg],WM_CREATE
        je      .wmcreate
        cmp     [wmsg],WM_SIZE
        je      .wmsize
        cmp     [wmsg],WM_PAINT
        je      .wmpaint
        cmp     [wmsg],WM_KEYDOWN
        je      .wmkeydown
        cmp     [wmsg],WM_DESTROY
        je      .wmdestroy
  .defwndproc:
        invoke  DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
        jmp     .finish
  .wmcreate:
        invoke  GetDC,[hwnd]
        mov     [hdc],eax
        mov     edi,pfd
        mov     ecx,sizeof.PIXELFORMATDESCRIPTOR shr 2
        xor     eax,eax
        rep     stosd
        mov     [pfd.nSize],sizeof.PIXELFORMATDESCRIPTOR
        mov     [pfd.nVersion],1
        mov     [pfd.dwFlags],PFD_SUPPORT_OPENGL+PFD_DOUBLEBUFFER+PFD_DRAW_TO_WINDOW
        mov     [pfd.iLayerType],PFD_MAIN_PLANE
        mov     [pfd.iPixelType],PFD_TYPE_RGBA
        mov     [pfd.cColorBits],16
        mov     [pfd.cDepthBits],16
        mov     [pfd.cAccumBits],0
        mov     [pfd.cStencilBits],0

        invoke  ChoosePixelFormat,[hdc],pfd
        invoke  SetPixelFormat,[hdc],eax,pfd
        invoke  wglCreateContext,[hdc]
        mov     [hrc],eax
        invoke  wglMakeCurrent,[hdc],[hrc]
        invoke  GetClientRect,[hwnd],rc
        invoke  glViewport,0,0,[rc.right],[rc.bottom]
        invoke  GetTickCount
        mov     [clock],eax




        invoke  glEnable, GL_DEPTH_TEST
        invoke  glShadeModel, GL_SMOOTH
        invoke  glHint, GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST

        xor     eax, eax

        jmp     .finish
  .wmsize:
        invoke  GetClientRect,[hwnd],rc
        invoke  glViewport,0,0,[rc.right],[rc.bottom]

        xor     eax,eax
        jmp     .finish
  .wmpaint:
        invoke  GetTickCount
        sub     eax,[clock]
        cmp     eax,10
        jb      .animation_ok
        add     [clock],eax



      .animation_ok:

        invoke  SetCursor, NULL
        stdcall Ticks.Update

        invoke  glClearColor, 0.0, 0.0, 0.02745, 1.0f
        invoke  glClear,GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT

        stdcall drawStage1


  .wKey:

  .wEnd:



        invoke  SwapBuffers,[hdc]
        xor     eax,eax
        jmp     .finish
  .wmkeydown:
        cmp     [wparam],VK_ESCAPE
        jne     .defwndproc
  .wmdestroy:
        invoke  wglMakeCurrent,0,0
        invoke  wglDeleteContext,[hrc]
        invoke  ReleaseDC,[hwnd],[hdc]
        invoke  PostQuitMessage,0
        xor     eax,eax
  .finish:
        ret
endp




proc    drawDestroyer

        invoke  glEnable, GL_NORMALIZE
        invoke  glEnable, GL_LIGHTING
        invoke  glEnable, GL_LIGHT0
        invoke  glEnable, GL_LIGHT1
        invoke  glLightfv, GL_LIGHT0, GL_DIFFUSE, light0Diffuse
        invoke  glLightfv, GL_LIGHT1, GL_DIFFUSE, light0Diffuse

        invoke  glLightfv, GL_LIGHT0, GL_POSITION, light0Position
        invoke  glLightfv, GL_LIGHT1, GL_POSITION, light1Position


        invoke  glEnableClientState, GL_VERTEX_ARRAY
        invoke  glEnableClientState, GL_NORMAL_ARRAY

        invoke  glVertexPointer, 3, GL_FLOAT, 3*4, vertices+16
        invoke  glNormalPointer, GL_FLOAT, 3*4, normals+16

        invoke  glDrawArrays, GL_TRIANGLES, 0, (verticesEnd-vertices-16)/4/3

        invoke  glDisableClientState, GL_VERTEX_ARRAY
        invoke  glDisableClientState, GL_NORMAL_ARRAY

        invoke  glDisable, GL_LIGHTING

        ret

endp

include 'func.c'
include 'stages\stages.c'
include 'ticks\ticks.c'
include 'random\random.c'
include 'stages\stage1\stage1.c'
include 'stages\stage2\stage2.c'
include 'stars\stars.c'
include 'stages\drawQueue\drawQueue.c'
include 'tie\tie.c'


section '.data' data readable writeable

_title  db 'Star wars demo',0
_class  db 'Star wars demo',0


wc      WNDCLASS 0,WindowProc,0,0,NULL,NULL,NULL,NULL,NULL,_class

hwnd    dd ?
hdc     dd ?
hrc     dd ?

msg     MSG
rc      RECT
pfd     PIXELFORMATDESCRIPTOR

Screen:
.aspect  dq     0
.width   dd     0
.height  dd     0

clock   dd ?

light0Position  dd              600.0, 50.0, 0.0, 1.0
light0V         dd              0.0, 0.0, 0.0

light0Diffuse   dd              1.0, 1.0, 1.0, 1.0
light1Position  dd              -600.0, 50.0, 0.0, 1.0



include 'func.d'
include 'random\random.d'
include 'stages\stages.d'
include 'stars\stars.d'

include 'stages\stage1\stage1.d'
include 'stages\stage2\stage2.d'
include 'ticks\ticks.d'

include 'tie\tie.d'

include 'stages\drawQueue\drawQueue.d'

resdata vertices
  file  'newModels\destroyer.v'
endres
verticesEnd:

resdata normals
  file  'newModels\destroyer.n'
endres
normalsEnd:


section '.idata' data import readable writeable
include 'idata.i'
