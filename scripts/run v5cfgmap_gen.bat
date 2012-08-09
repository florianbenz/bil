@echo off
setlocal

set /p ans=Run v5cfgmap_gen for all device files? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\bin\win32\MSVC 2008\v5cfgmap_gen\Release"
for /r "%~dp0\..\data" %%i in (*.dev) do (
  echo ----------------------------------------------------------------------
  echo v5cfgmap_gen
  echo   "%%i"
  echo   "..\..\..\..\..\data"
  echo ----------------------------------------------------------------------
  echo;
  v5cfgmap_gen "%%i" "..\..\..\..\..\data"
  echo;
  echo;
)
echo;

:end