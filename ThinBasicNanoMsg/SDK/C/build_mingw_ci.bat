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
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\nn_dynload.c" -o "%OBJ%\nn_dynload.o" || exit /b 1
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\tb_thincore.c" -o "%OBJ%\tb_thincore.o" || exit /b 1
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\tb_nanomsg_exec.c" -o "%OBJ%\tb_nanomsg_exec.o" || exit /b 1
"%CC%" %CFLAGS% -I"%INC%" -c "%SRC%\thinBasic_NanoMsg.c" -o "%OBJ%\thinBasic_NanoMsg.o" || exit /b 1
for %%d in ("%CC%") do set "CCDIR=%%~dpd"
set "WINDRES=%CCDIR%windres.exe"
if not exist "%WINDRES%" set "WINDRES=%CCDIR%i686-w64-mingw32-windres.exe"
"%WINDRES%" -I "%INC%" -i "%DEFDIR%\thinBasic_NanoMsg.rc" -o "%OBJ%\thinBasic_NanoMsg_res.o" || exit /b 1
"%CC%" -shared -Wl,--enable-stdcall-fixup "%OBJ%\nn_dynload.o" "%OBJ%\tb_thincore.o" "%OBJ%\tb_nanomsg_exec.o" "%OBJ%\thinBasic_NanoMsg.o" "%OBJ%\thinBasic_NanoMsg_res.o" "%DEFDIR%\thinBasic_NanoMsg.def" -lkernel32 -o "%OUT%\thinBasic_NanoMsg.dll" || exit /b 1
echo Built: %OUT%\thinBasic_NanoMsg.dll
endlocal
exit /b 0
