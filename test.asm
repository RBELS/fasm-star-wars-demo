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

        ;stdcall strToFloat, floatStr
        ;invoke  Sleep, 1000
        ;invoke  ReadConsoleInput, [inHnd], charInBuf, 10, numEventsRead

        ;stdcall Random.Init

        ;stdcall Random.GetFloat
        ;stdcall Random.Get

        ;stdcall mulVecD, frontVec, double 10.0
        ;stdcall mulVecD, frontVec, double 10.0

        ;stdcall normalizeVecD, frontVec

        ;stdcall Stars.Init
        ;stdcall  Stars.GetTriangle, starsdata

        ;push    10.0
        ;fld     dword [esp]
        ;pop     edx

        ;push    9.0
        ;fcom    dword [esp]
        ;fstsw   ax

        ;test    ah, 0000'0001
        ;jne     .Greater
;.Less:
        ;mov     edx, 0
        ;jmp     .EndIf
;.Greater:
        ;mov     edx, 1
;.EndIf:

        ;stdcall getStage


        ;stdcall Ticks.Init

        ;stdcall Ticks.Update

        stdcall cmpFloats, 11.4, 25.3; ah = 01
        stdcall cmpFloats, 54.34, -32.1; ah = 00
        stdcall cmpFloats, 39.39, 39.39; ah = 40

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

include 'ticks\ticks.d'


starsdata       dd      57.8, 57.8, 57.8
db $FF
bufVec          dd      3 dup (?)
vertice         dd      3*3*4 dup (?)

include 'random\random.d'

section '.idata' data import readable writable

library kernel32, 'kernel32.dll',\
    gdi32,    'gdi32.dll',\
    user32,   'user32.dll'

include 'api\kernel32.inc'
include 'api\gdi32.inc'
include 'api\user32.inc'
