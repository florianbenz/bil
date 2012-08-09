@echo off
setlocal

set /p ans=Clean all bitcorrelate generated files in testbase? [y/n] 
if not "%ans%"=="y" goto end
echo;

for /r "%~dp0\..\test" %%i in (*.cdb.txt *.cdb) do (
  echo Deleting "%%i"
  del "%%i"
)
echo;

:end