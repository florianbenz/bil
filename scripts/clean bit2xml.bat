@echo off
setlocal

set /p ans=Clean all bit2xml generated files in testbase? [y/n] 
if not "%ans%"=="y" goto end
echo;

for /r "%~dp0\..\test" %%i in (*.css *.xsl *.xml) do (
  echo Deleting "%%i"
  del "%%i"
)
echo;

:end