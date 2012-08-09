@echo off
setlocal

echo This will generate the bitstreams out of *.ncd files by using the Xilinx
echo tool bitgen, so be sure its path is set in the system's PATH variable.
echo For every *.ncd a bitstream (with compression enabled) will be created.
echo;

set /p ans=Continue? [y/n] 
if not "%ans%"=="y" goto end
echo;

for /r "%~dp0..\test" %%i in (*.ncd) do (
  cd /d "%%~dpi"
  echo ----------------------------------------------------------------------
  echo Generating compressed bitfile for "%%~nxi":
  echo Current directory: "%%~dpi"
  echo ----------------------------------------------------------------------
  bitgen -w -g Compress "%%~nxi"
  rd /s /q "_xmsgs" 2> nul
  del "%%~ni.bgn"
  del "%%~ni.drc"
  del "%%~ni_bitgen.xwbt"
  del "webtalk.log"
  del "xilinx_device_details.xml"
  echo;
  echo;
)

echo ----------------------------------------------------------------------
echo Finished.

:end