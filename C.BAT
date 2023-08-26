if "%1" == ""     goto ERROR
if not "%2" == "" goto ERROR

C:\KEIL\C51\BIN\C51 %1.C CODE
if errorlevel 2 goto END
C:\KEIL\C51\BIN\BL51 %1.OBJ TO %1.OUT IXREF
if errorlevel 2 goto END
C:\KEIL\C51\BIN\OH51 %1.OUT
goto END

:ERROR
echo off
echo     **********************************
echo     *   Syntax :  C sourcefile[.c]   *
echo     **********************************
:END
