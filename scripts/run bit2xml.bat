@echo off
setlocal

set /p ans=Run bit2xml for all bitfiles in testbase? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\bin\win32\MSVC 2008\bit2xml\Release"
for /r "%~dp0\..\test" %%i in (*.bit) do (
  echo ----------------------------------------------------------------------
  echo bit2xml -s "%%i"
  echo ----------------------------------------------------------------------
  echo;
  bit2xml -s "%%i"
  echo;
  echo;
)
echo;

:end