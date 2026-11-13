# ThinBasicNanoMsg  

[Nanomsg](https://nanomsg.org) and [NNG](https://nng.nanomsg.org) wrappers for ThinBasic Programming Language.

![GitHub](https://img.shields.io/github/license/jiowcl/ThinBasicNanoMsg.svg)
![ThinBasic](https://img.shields.io/badge/language-ThinBasic-blue.svg)
![Dependency](https://img.shields.io/badge/Protocol-nanomsg-3A3A3A?style=flat-square)

## Environment  

- Windows 10/11 or later (recommended)
- ThinBasic 1.14+ recommended — **32-bit (x86) runtime only**
- Bundled **x86** `nanomsg.dll` / `nng.dll` (from PureBasicNanoMsg/FreeBasicNanoMsg)

### Architecture note  

ThinBasic runs as a **32-bit** process, so only **x86** DLLs in each package `Library\x86` can be loaded. Do not use `Library\x64` builds from sibling FreeBasicNanoMsg/PureBasicNanoMsg repos. TCP and other network transports still interoperate with x64 peers.

## Package layout

```thinbasic
ThinBasicNanoMsg/
├── ThinBasicNanoMsg/          # nanomsg (legacy SP stack)
│   ├── Core/                  # NanoMsg.inc, NanomsgWrapper.inc, …
│   ├── Library/x86/           # nanomsg.dll (+ .lib for reference)
│   ├── Example/               # procedural .tbasic
│   ├── Example/Module/        # Type-wrapper examples
│   └── SDK/C/                 # thinBasic_NanoMsg.dll (USES "NanoMsg")
├── ThinBasicNNG/              # NNG (nanomsg-next)
│   ├── Core/                  # Nng.inc, NngWrapper.inc, …
│   ├── Library/x86/           # nng.dll (+ .lib)
│   ├── Example/ + Module/
│   └── SDK/C/                 # thinBasic_NNG.dll (USES "NNG")
├── README.md
└── .github/workflows/ci.yml
```

Samples:

| Pattern | NanoMsg | NNG |
|--------|---------|-----|
| REQ/REP | `Example\RepServer.tbasic`, `ReqClient.tbasic` | same names under `ThinBasicNNG\Example` |
| PUB/SUB | `PubServer.tbasic`, `SubClient.tbasic` | same |
| PUSH/PULL | `PushServer.tbasic`, `PullClient.tbasic` | same |
| Survey | `SurveyorServer.tbasic`, `RespondentClient.tbasic` | same |
| PAIR inproc | `PairInproc.tbasic` | same |
| Type wrapper | `Example\Module\*.tbasic` | `ThinBasicNNG\Example\Module\*.tbasic` |

Default TCP ports follow the FreeBasic/PureBasic ports: **1700** (pub/sub, req/rep), **1701** (push/pull), **1702** (surveyor), **1703** (bus).

| BUS | NanoMsg | NNG |
|-----|---------|-----|
| Procedural | `ThinBasicNanoMsg\Example\BusServer.tbasic`, `BusClient.tbasic` | `ThinBasicNNG\Example\BusServer.tbasic`, `BusClient.tbasic` |
| Type wrapper | `Example\Module\BusServer.tbasic`, `BusClient.tbasic` | same under `ThinBasicNNG\Example\Module\` |

NanoMsg bus samples use `NnPoll` + `$NN_POLLIN` (idle send every 500 ms). NNG bus samples use `recv-timeout` (`nng_socket_set_ms`) and treat `$NNG_ETIMEDOUT` as idle.

## Native vs ThinBasic SDK  

| | Native (`Core\*.inc`) | SDK (`USES "NanoMsg"` / `USES "NNG"`) |
|--|----------------------|----------------------------------------|
| Coverage | Full procedural + Type wrappers | Core subset (socket, bind/connect, send/recv, errno, library init) |
| DLL load | `LibPath.inc` sets process CWD → `Library\x86` | `NnLibraryInit(path)` / `NngLibraryInit(path)` in C module |
| Build | None (includes only) | `SDK\C\build_pelles.bat` or `build_mingw_ci.bat` |
| Constants | `$NN_*` / `$NNG_*` in `Enums.inc` | `%NN_*` / `%NNG_*` registered by the module |

Do not mix `#INCLUDE` Core files with `USES "NanoMsg"` or `USES "NNG"` in the same script.

Typical includes:

```vb
#INCLUDE Once ".\Core\NanoMsg.inc"
#INCLUDE Once ".\Core\NanomsgWrapper.inc"
```

## How to build SDK modules  

From each package:

```text
ThinBasicNanoMsg\SDK\C\build_pelles.bat
ThinBasicNNG\SDK\C\build_pelles.bat
```

CI uses i686 MinGW: `build_mingw_ci.bat` (no `thinCore.lib`). Install artifacts to `C:\thinBasic\Lib\`.

## Example  

NanoMsg Publisher Server

```thinbasic
USES "CONSOLE"

#INCLUDE Once "..\..\Core\NanomsgWrapper.inc"

Function RndRange(ByVal first As Double, ByVal last As Double) As Double
  Function = Rnd * (last - first) + first
End Function

Dim NnRuntime As LibNanomsgRuntime
Dim NnSocketRec As LibNanomsgSocket
Global Socket As Long
Global lpszServerAddr As String
Global lpszSendMessage As String
Global Rc As Long

lpszServerAddr = "tcp://*:1700"
Socket = NnSocketRec.NewSocket($AF_SP, $NN_PUB)
Rc = NnSocketRec.SockBind(Socket, lpszServerAddr)

If Rc < 0 Then
  Printl("Bind failed: " & NnRuntime.GetStrerror(NnRuntime.GetErrno()))
Else
  Printl("Bind an IP address: " & lpszServerAddr)
  Randomize
  
  While %TRUE
    lpszSendMessage = "quotes#Bid:" & Str$(Int(RndRange(1000, 9000))) & ",Ask:" & Str$(Int(RndRange(1000, 9000)))

    If NnSocketRec.SockSendStr(Socket, lpszSendMessage, 0) >= 0 Then
      Printl("Published: " & lpszSendMessage)
    End If

    Sleep 500
  Wend
End If
```

NanoMsg Subscribe Client

```thinbasic
USES "CONSOLE"

#INCLUDE Once "..\..\Core\NanomsgWrapper.inc"

Dim NnSocketRec As LibNanomsgSocket
Global Socket As Long
Global lpszServerAddr As String
Global lpszSubscribe As String
Global lpszRecvBuffer As Asciiz * 256
Global Rc As Long

lpszServerAddr = "tcp://localhost:1700"
lpszSubscribe = "quotes"
Socket = NnSocketRec.NewSocket($AF_SP, $NN_SUB)
Rc = NnSocketRec.SockConnect(Socket, lpszServerAddr)

If Rc < 0 Then
  Printl("Connect failed")
Else
  NnSocketRec.SockSetsockoptStr(Socket, $NN_SUB, $NN_SUB_SUBSCRIBE, lpszSubscribe)
  
  While %TRUE
    NnSocketRec.SockRecv(Socket, VarPtr(lpszRecvBuffer), SizeOf(lpszRecvBuffer), 0)
    Printl(lpszRecvBuffer)
  Wend
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
