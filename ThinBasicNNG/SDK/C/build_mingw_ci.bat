@echo off
setlocal EnableExtensions
set "ROOT=%~dp0"
set "SRC=%ROOT%src"
set "INC=%ROOT%include"
set "DEFDIR=%ROOT%lib"
set "OUT=%ROOT%bin"
set "OBJ=%ROOT%build"
set "CC="
if exist "C:\msys64\mingw32\bin\gcc.exe" set "CC=C:\msys64\mingw32\bin\gcc.exe"
if "%CC%"=="" where i686-w64-mingw32-gcc.exe >nul 2>&1 && for /f "delims=" %%p in ('where i686-w64-mingw32-gcc.exe') do set "CC=%%p"
if "%CC%"=="" (echo ERROR: 32-bit MinGW gcc not found. & exit /b 1)
if not exist "%OBJ%" mkdir "%OBJ%"
if not exist "%OUT%" mkdir "%OUT%"
set "CFLAGS=-std=c11 -Wall -Wextra -O2"
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\nng_dynload.c" -o "%OBJ%\nng_dynload.o" || exit /b 1
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\tb_thincore.c" -o "%OBJ%\tb_thincore.o" || exit /b 1
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\tb_nng_exec.c" -o "%OBJ%\tb_nng_exec.o" || exit /b 1
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\thinBasic_NNG.c" -o "%OBJ%\thinBasic_NNG.o" || exit /b 1
for %%d in ("%CC%") do set "CCDIR=%%~dpd"
set "WINDRES=%CCDIR%windres.exe"
if not exist "%WINDRES%" set "WINDRES=%CCDIR%i686-w64-mingw32-windres.exe"
"%WINDRES%" -I "%INC%" -i "%DEFDIR%\thinBasic_NNG.rc" -o "%OBJ%\thinBasic_NNG_res.o" || exit /b 1
"%CC%" -shared -Wl,--enable-stdcall-fixup "%OBJ%\nng_dynload.o" "%OBJ%\tb_thincore.o" "%OBJ%\tb_nng_exec.o" "%OBJ%\thinBasic_NNG.o" "%OBJ%\thinBasic_NNG_res.o" "%DEFDIR%\thinBasic_NNG.def" -lkernel32 -o "%OUT%\thinBasic_NNG.dll" || exit /b 1
echo Built: %OUT%\thinBasic_NNG.dll
endlocal
exit /b 0
