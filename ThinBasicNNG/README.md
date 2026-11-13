# ThinBasicNng  

NNG (nanomsg-next-gen) wrappers for ThinBasic Programming Language.

![ThinBasic](https://img.shields.io/badge/language-ThinBasic-blue.svg)
![Dependency](https://img.shields.io/badge/Protocol-nng-3A3A3A?style=flat-square)

This package is the NNG counterpart of [ThinBasicNanoMsg](../ThinBasicNanoMsg).  
nanomsg is no longer maintained; new projects should prefer NNG. The two wrappers are **API-incompatible** and live side by side.

## Environment  

- Windows 10/11 or later (recommended)
- ThinBasic 1.14+ recommended — **32-bit (x86) runtime only**
- Bundled **x86** `nng.dll` (from PureBasicNng/FreeBasicNng)

## Example  

Nng Publisher Server

```thinbasic
USES "CONSOLE"

#INCLUDE Once "..\Core\Nng.inc"

Global sock As Long
Global Rc As Long

If NngInitDefault() <> $NNG_OK Then
  Printl("nng_init failed: " & NngStrerrorString(NngLastErr))
Else
  Rc = NngPub0Open(sock)
  If Rc <> $NNG_OK Then
    Printl("pub open failed: " & NngStrerrorString(Rc))
  Else
    Rc = NngListenDefault(sock, "tcp://0.0.0.0:1700", 0)

    If Rc <> $NNG_OK Then
      Printl("listen failed: " & NngStrerrorString(Rc))
    Else
      Printl("PUB listening on tcp://0.0.0.0:1700")
      
      While %TRUE
        Rc = NngSendString(sock, "quotes#tick", 0)
        If Rc = $NNG_OK Then Printl("Published: quotes#tick")
        Sleep 500
      Wend
    End If
  End If

  NngSocketClose(sock)
  NngFini()
End If
```

Nng Subscribe Client

```thinbasic
USES "CONSOLE"

#INCLUDE Once "..\Core\Nng.inc"

Global sock As Long
Global buf As Asciiz * 256
Global n As Long
Global Rc As Long
Global topic As String

If NngInitDefault() <> $NNG_OK Then
  Printl("nng_init failed: " & NngStrerrorString(NngLastErr))
Else
  Rc = NngSub0Open(sock)

  If Rc <> $NNG_OK Then
    Printl("sub open failed: " & NngStrerrorString(Rc))
  Else
    Rc = NngDialDefault(sock, "tcp://127.0.0.1:1700", 0)

    If Rc <> $NNG_OK Then
      Printl("dial failed: " & NngStrerrorString(Rc))
    Else
      topic = "quotes"
      Rc = NngSub0Subscribe(sock, topic)

      If Rc <> $NNG_OK Then
        Printl("subscribe failed: " & NngStrerrorString(Rc))
      Else
        Printl("Subscribed to ""quotes"" on tcp://127.0.0.1:1700 (start PubServer first)")

        While %TRUE
          n = NngRecvBuffer(sock, VarPtr(buf), SizeOf(buf), 0)
          
          If n >= 0 Then
            Printl(Left$(buf, n))
          Else
            If Not NngErrIsTimedOut(NngLastErr) Then
              Printl("recv: " & NngStrerrorString(NngLastErr))
            End If
          End If
        Wend
      End If
    End If
  End If

  NngSocketClose(sock)
  NngFini()
End If
```

## License

Copyright (c) 2019-2026 Ji-Feng Tsai.  
ThinBasic Copyright (c) Eros Olmi [ThinBASIC Interpreter](https://github.com/ThinBASIC).  
Code released under the MIT license.  

## Donation

If this application help you reduce time to coding, you can give me a cup of coffee :)

[![paypal](https://www.paypalobjects.com/en_US/TW/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=3RNMD6Q3B495N&source=url)

[Paypal Me](https://paypal.me/jiowcl?locale.x=zh_TW)
