@echo off
setlocal EnableExtensions
set "ROOT=%~dp0"
set "PELLESC=C:\Program Files\PellesC"
if not exist "%PELLESC%\Bin\pocc.exe" (echo ERROR: Pelles C not found & exit /b 1)
call "%PELLESC%\Bin\povars32.bat" >nul
set "SRC=%ROOT%src" & set "INC=%ROOT%include" & set "OBJ=%ROOT%build" & set "OUT=%ROOT%bin"
if not exist "%OBJ%" mkdir "%OBJ%"
if not exist "%OUT%" mkdir "%OUT%"
set CCFLAGS=/Tx86-coff /std:C11 /Ze /W2 /utf-8 /I"%INC%"
pocc %CCFLAGS% /Fo"%OBJ%\nng_dynload.obj" "%SRC%\nng_dynload.c" || exit /b 1
pocc %CCFLAGS% /Fo"%OBJ%\tb_thincore.obj" "%SRC%\tb_thincore.c" || exit /b 1
pocc %CCFLAGS% /Fo"%OBJ%\tb_nng_exec.obj" "%SRC%\tb_nng_exec.c" || exit /b 1
pocc %CCFLAGS% /Fo"%OBJ%\thinBasic_NNG.obj" "%SRC%\thinBasic_NNG.c" || exit /b 1
porc /Fo"%OBJ%\thinBasic_NNG.res" /I"%INC%" "%ROOT%lib\thinBasic_NNG.rc" || exit /b 1
polink /DLL /DEF:"%ROOT%lib\thinBasic_NNG.def" /OUT:"%OUT%\thinBasic_NNG.dll" "%OBJ%\nng_dynload.obj" "%OBJ%\tb_thincore.obj" "%OBJ%\tb_nng_exec.obj" "%OBJ%\thinBasic_NNG.obj" "%OBJ%\thinBasic_NNG.res" kernel32.lib
echo Built: %OUT%\thinBasic_NNG.dll
endlocal
