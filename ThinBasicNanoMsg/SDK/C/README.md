# ThinBasic SDK module  

Builds `thinBasic_NanoMsg.dll` for `USES "NanoMsg"`.

- **Pelles C (x86):** `build_pelles.bat`
- **MinGW i686 (CI):** `build_mingw_ci.bat`

Output: `bin\thinBasic_NanoMsg.dll` — copy to `C:\thinBasic\Lib\`.  
Runtime loads `nanomsg.dll` from the directory passed to `NnLibraryInit` (package `Library\x86`, not `thinBasic\Lib`).

Smoke test: run `examples\NanoMsgSdkSmoke.tbasic` with `thinBasicc.exe` (resolves `..\..\..\Library\x86` from `examples\`).

See repository root [README.md](../../../README.md) for native vs SDK comparison.

## License

Copyright (c) 2019-2026 Ji-Feng Tsai.  
ThinBasic Copyright (c) Eros Olmi [ThinBASIC Interpreter](https://github.com/ThinBASIC).  
Code released under the MIT license.  

## Donation

If this application help you reduce time to coding, you can give me a cup of coffee :)

[![paypal](https://www.paypalobjects.com/en_US/TW/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=3RNMD6Q3B495N&source=url)

[Paypal Me](https://paypal.me/jiowcl?locale.x=zh_TW)
