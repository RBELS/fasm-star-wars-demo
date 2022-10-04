include 'macro\proc32.inc'

proc    Random.Init

        invoke  GetSystemTimeAsFileTime, LPRandom
        mov     eax, dword [LPRandom]
        mov     [PrevRandom], eax

        ret
endp

proc    Random.Get uses ecx edx, wMin, wMax

        mov     eax, [PrevRandom]
        rol     eax, 7
        adc     eax, 23
        mov     [PrevRandom], eax

        mov     ecx, [wMax]
        sub     ecx, [wMin]
        inc     ecx

        xor     edx, edx
        div     ecx
        add     edx, [wMin]
        mov     eax, edx

        ret
endp

proc    Random.GetFloat

        mov     eax, [PrevRandom]
        rol     eax, 7
        adc     eax, 23
        mov     [PrevRandom], eax

        push    eax
        fild    dword [esp]
        pop     eax

        fabs

        push    4294967295.0
        fdiv    dword [esp]
        pop     eax

        push    2.0
        fmul    dword [esp]
        pop     eax

        push    1.0
        fsub    dword [esp]
        fstp    dword [esp]

        pop     eax
        ret
endp

