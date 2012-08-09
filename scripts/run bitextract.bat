@echo off
setlocal

set /p ans=Run bitextract for all bitfiles in testbase? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\bin\win32\MSVC 2008\bitextract\Release"
for /r "%~dp0\..\test" %%i in (*.bit) do (
  echo ----------------------------------------------------------------------
  echo bitextract
  echo   -dp "..\..\..\..\..\data"
  echo   "%%i"
  echo ----------------------------------------------------------------------
  echo;
  bitextract -dp "..\..\..\..\..\data" "%%i"
  echo;
  echo;
)
echo;

:end