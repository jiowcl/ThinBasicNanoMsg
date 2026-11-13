# ThinBasic SDK module  

Builds `thinBasic_NNG.dll` for `USES "NNG"`.

- **Pelles C (x86):** `build_pelles.bat`
- **MinGW i686 (CI):** `build_mingw_ci.bat`

Output: `bin\thinBasic_NNG.dll` — copy to `C:\thinBasic\Lib\`.  
`NngLibraryInit` loads `nng.dll` from the path you pass (package `Library\x86`) and calls `nng_init`.

Smoke test: `examples\NngSdkSmoke.tbasic`.

See repository root [README.md](../../../README.md).  

## License

Copyright (c) 2019-2026 Ji-Feng Tsai.  
ThinBasic Copyright (c) Eros Olmi [ThinBASIC Interpreter](https://github.com/ThinBASIC).  
Code released under the MIT license.  

## Donation

If this application help you reduce time to coding, you can give me a cup of coffee :)

[![paypal](https://www.paypalobjects.com/en_US/TW/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=3RNMD6Q3B495N&source=url)

[Paypal Me](https://paypal.me/jiowcl?locale.x=zh_TW)
