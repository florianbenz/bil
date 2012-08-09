@echo off
setlocal

echo This will generate the *.xdl files out of *.ncd files by using the Xilinx
echo tool xdl, so be sure its path is set in the system's PATH variable. For
echo every *.ncd a xdl file will be created.
echo;

set /p ans=Continue? [y/n] 
if not "%ans%"=="y" goto end
echo;

for /r "%~dp0..\test" %%i in (*.ncd) do (
  cd /d "%%~dpi"
  echo ----------------------------------------------------------------------
  echo Generating xdl file for "%%~nxi":
  echo Current directory: "%%~dpi"
  echo ----------------------------------------------------------------------
  xdl -ncd2xdl "%%~nxi" "%%~ni.xdl"
  rd /s /q "_xmsgs" 2> nul
  echo;
  echo;
)

echo ----------------------------------------------------------------------
echo Finished.

:end