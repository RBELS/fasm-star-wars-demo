format PE CONSOLE 4.0
entry WinMain

include 'win32ax.inc'
include 'macro\proc32.inc'

section '.tcode' code readable executable

proc WinMain
        invoke  GetStdHandle, STD_OUTPUT_HANDLE
        mov [outHnd], eax

        invoke  GetStdHandle, STD_INPUT_HANDLE
        mov [inHnd], eax

        invoke  WriteConsole, [outHnd], szText, 12, numEventsRead, NULL

        ;stdcall strToFloat, floatStr
        ;invoke  Sleep, 1000
        ;invoke  ReadConsoleInput, [inHnd], charInBuf, 10, numEventsRead

        stdcall Random.Init

        stdcall Random.GetFloat
        stdcall Random.Get

        ;stdcall mulVecD, frontVec, double 10.0
        ;stdcall mulVecD, frontVec, double 10.0
        stdcall normalizeVecD, frontVec

        invoke  ExitProcess, 0
endp


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

include 'random\random.d'

section '.idata' data import readable writable

library kernel32, 'kernel32.dll',\
    gdi32,    'gdi32.dll',\
    user32,   'user32.dll'

include 'api\kernel32.inc'
include 'api\gdi32.inc'
include 'api\user32.inc'
