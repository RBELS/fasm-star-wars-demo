format PE CONSOLE 4.0
entry WinMain

STARS_COUNT     =       2

include 'win32ax.inc'
include 'macro\proc32.inc'

section '.tcode' code readable executable

proc WinMain
        invoke  GetStdHandle, STD_OUTPUT_HANDLE
        mov [outHnd], eax

        invoke  GetStdHandle, STD_INPUT_HANDLE
        mov [inHnd], eax

        invoke  WriteConsole, [outHnd], szText, 9, numEventsRead, NULL

        ;stdcall getIndex
        stdcall  getPos, Dest1Table, Dest1TableEnd, dest1Pos

        fld     dword [dest1Pos]

        invoke  ExitProcess, 0
endp




proc    Stars.Init

        mov     edx, starsdata
        mov     ecx, STARS_COUNT
.GenLoop:
        stdcall genVecF, edx
        stdcall normalizeVecF, edx
        stdcall mulVecF, 100.0

        add     edx, 3*4
        loop    .GenLoop

        ret
endp

include 'ticks\ticks.c'


include 'stages\stages.c'
include 'stages\stage1\stage1.d'
include 'stages\drawQueue\drawQueue.c'
include 'random\random.c'

include 'func.c'


section '.data' data readable writable

szText  db  'Test msg!', 0
szTitle db  'Test title', 0

floatStr        db      '12.34', 0

outHnd  dd  ?
inHnd   dd  ?

charInBuf   db  0 dup 10
.size       dd  $-charInBuf
numEventsRead   dd  0

  posVec:
  .x    dq      0.0
  .y    dq      0.0
  .z    dq      800.0

  frontVec:
  .x    dq      0.21
  .y    dq      0.5
  .z    dq      -1.0

  watchPointVec:
  .x    dq      0.0
  .y    dq      0.0
  .z    dq      0.0

;include 'ticks\ticks.d'
include 'stages\drawQueue\drawQueue.d'
ticksFloat      dd      20.0

starsdata       dd      57.8, 57.8, 57.8
db $FF
bufVec          dd      3 dup (?)
vertice         dd      3*3*4 dup (?)
dest1Pos        dd      3 dup (0)

include 'random\random.d'

section '.idata' data import readable writable

library kernel32, 'kernel32.dll',\
    gdi32,    'gdi32.dll',\
    user32,   'user32.dll'

include 'api\kernel32.inc'
include 'api\gdi32.inc'
include 'api\user32.inc'
