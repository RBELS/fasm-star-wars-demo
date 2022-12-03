proc    Ticks.Init uses edx

        invoke  GetTickCount
        mov     [startTicks], eax
        mov     edx, eax

        fild    dword [startTicks]
        push    100.0
        fdiv    dword [esp]
        pop     eax

        fstp    dword [startTicksFloat]

        mov     [prevTicks], 0
        mov     [prevTicksFloat], 0.0

        mov     [ticks], 0
        mov     [ticksFloat], 0.0

        mov     [deltaTicks], 0
        mov     [deltaTicksFloat], 0.0

        ret
endp

proc    Ticks.Update

        invoke  GetTickCount
        sub     eax, [startTicks]

        cmp     eax, 440 * 100
        jb      .NO_LOOP
        stdcall Ticks.Init
.NO_LOOP:

        ;to rewind scene
        ;add     eax, 0 * 100
        ;to rewind scene

        mov     [ticks], eax
        fild    dword [ticks]

        push    100.0
        fdiv    dword [esp]
        pop     eax

        fstp    dword [ticksFloat]

        mov     eax, [ticks]
        sub     eax, [prevTicks]

        mov     [deltaTicks], eax
        mov     eax, [ticks]
        mov     [prevTicks], eax

        fld     dword [ticksFloat]
        fsub    dword [prevTicksFloat]
        fstp    dword [deltaTicksFloat]

        mov     eax, [ticksFloat]
        mov     [prevTicksFloat], eax

        ret
endp