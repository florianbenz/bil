@echo off
setlocal

set /p ans=Run bitcorrelate for all *.xdl/*.bit pairs in testbase? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\bin\win32\MSVC 2008\bitcorrelate\Release"
for /r "%~dp0\..\test" %%i in (*.bit) do (
  echo ----------------------------------------------------------------------
  echo bitcorrelate
  echo   -dp "..\..\..\..\..\data"
  echo   -s "%%~dpni.cdb.txt"
  echo   "%%~dpni.xdl"
  echo   "%%i"
  echo   "%%~dpni.cdb"
  echo ----------------------------------------------------------------------
  echo;
  bitcorrelate -dp "..\..\..\..\..\data" -s "%%~dpni.cdb.txt" "%%~dpni.xdl" "%%i" "%%~dpni.cdb"
  echo;
  echo;
)
echo;

:end