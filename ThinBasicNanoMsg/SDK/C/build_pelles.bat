@echo off
setlocal EnableExtensions
set "ROOT=%~dp0"
set "PELLESC=C:\Program Files\PellesC"
if not exist "%PELLESC%\Bin\pocc.exe" (echo ERROR: Pelles C not found & exit /b 1)
call "%PELLESC%\Bin\povars32.bat" >nul
set "SRC=%ROOT%src"
set "INC=%ROOT%include"
set "OBJ=%ROOT%build"
set "OUT=%ROOT%bin"
if not exist "%OBJ%" mkdir "%OBJ%"
if not exist "%OUT%" mkdir "%OUT%"
set CCFLAGS=/Tx86-coff /std:C11 /Ze /W2 /utf-8 /I"%INC%"
pocc %CCFLAGS% /Fo"%OBJ%\nn_dynload.obj" "%SRC%\nn_dynload.c" || exit /b 1
pocc %CCFLAGS% /Fo"%OBJ%\tb_thincore.obj" "%SRC%\tb_thincore.c" || exit /b 1
pocc %CCFLAGS% /Fo"%OBJ%\tb_nanomsg_exec.obj" "%SRC%\tb_nanomsg_exec.c" || exit /b 1
pocc %CCFLAGS% /Fo"%OBJ%\thinBasic_NanoMsg.obj" "%SRC%\thinBasic_NanoMsg.c" || exit /b 1
porc /Fo"%OBJ%\thinBasic_NanoMsg.res" /I"%INC%" "%ROOT%lib\thinBasic_NanoMsg.rc" || exit /b 1
polink /DLL /DEF:"%ROOT%lib\thinBasic_NanoMsg.def" /OUT:"%OUT%\thinBasic_NanoMsg.dll" "%OBJ%\nn_dynload.obj" "%OBJ%\tb_thincore.obj" "%OBJ%\tb_nanomsg_exec.obj" "%OBJ%\thinBasic_NanoMsg.obj" "%OBJ%\thinBasic_NanoMsg.res" kernel32.lib
echo Built: %OUT%\thinBasic_NanoMsg.dll
endlocal
