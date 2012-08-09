@echo off
setlocal

echo.
echo This will generate the device description files for all
echo Virtex-5 devices out of the corresponding xdlrc files.
echo Since the xdlrc files are huge, they will be generated
echo on the fly by calling the xdl binary from Xilinx. After
echo a xdlrc has been converted, it will be deleted again.
echo.

set /p ans=Run xdlrc_convert for all Virtex-5 devices? [y/n] 
if not "%ans%"=="y" goto end
echo;

set V5DEVICES=xc5vfx30tff665
set V5DEVICES=%V5DEVICES% xc5vfx70tff665
set V5DEVICES=%V5DEVICES% xc5vfx70tff1136
set V5DEVICES=%V5DEVICES% xc5vfx100tff1136
set V5DEVICES=%V5DEVICES% xc5vfx100tff1738
set V5DEVICES=%V5DEVICES% xc5vfx130tff1738
set V5DEVICES=%V5DEVICES% xc5vfx200tff1738
set V5DEVICES=%V5DEVICES% xc5vlx30ff324
set V5DEVICES=%V5DEVICES% xc5vlx30ff676
set V5DEVICES=%V5DEVICES% xc5vlx50ff324
set V5DEVICES=%V5DEVICES% xc5vlx50ff676
set V5DEVICES=%V5DEVICES% xc5vlx50ff1153
set V5DEVICES=%V5DEVICES% xc5vlx85ff676
set V5DEVICES=%V5DEVICES% xc5vlx85ff1153
set V5DEVICES=%V5DEVICES% xc5vlx110ff676
set V5DEVICES=%V5DEVICES% xc5vlx110ff1153
set V5DEVICES=%V5DEVICES% xc5vlx110ff1760
set V5DEVICES=%V5DEVICES% xc5vlx155ff1153
set V5DEVICES=%V5DEVICES% xc5vlx155ff1760
set V5DEVICES=%V5DEVICES% xc5vlx220ff1760
set V5DEVICES=%V5DEVICES% xc5vlx330ff1760
set V5DEVICES=%V5DEVICES% xc5vlx20tff323
set V5DEVICES=%V5DEVICES% xc5vlx30tff323
set V5DEVICES=%V5DEVICES% xc5vlx30tff665
set V5DEVICES=%V5DEVICES% xc5vlx50tff665
set V5DEVICES=%V5DEVICES% xc5vlx50tff1136
set V5DEVICES=%V5DEVICES% xc5vlx85tff1136
set V5DEVICES=%V5DEVICES% xc5vlx110tff1136
set V5DEVICES=%V5DEVICES% xc5vlx110tff1738
set V5DEVICES=%V5DEVICES% xc5vlx155tff1136
set V5DEVICES=%V5DEVICES% xc5vlx155tff1738
set V5DEVICES=%V5DEVICES% xc5vlx220tff1738
set V5DEVICES=%V5DEVICES% xc5vlx330tff1738
set V5DEVICES=%V5DEVICES% xc5vsx35tff665
set V5DEVICES=%V5DEVICES% xc5vsx50tff665
set V5DEVICES=%V5DEVICES% xc5vsx50tff1136
set V5DEVICES=%V5DEVICES% xc5vsx95tff1136
set V5DEVICES=%V5DEVICES% xc5vsx240tff1738
set V5DEVICES=%V5DEVICES% xc5vtx150tff1156
set V5DEVICES=%V5DEVICES% xc5vtx150tff1759
set V5DEVICES=%V5DEVICES% xc5vtx240tff1759

cd /D "%~dp0..\data"  
for %%i in (%V5DEVICES%) do (
  echo ----------------------------------------------------------------------
  echo Converting xdlrc file for device %%i
  echo ----------------------------------------------------------------------
  echo;
  echo xdl -report -pips -all_conns %%i
  xdl -report -pips -all_conns %%i
  echo;
  echo xdlrc_convert %%i.xdlrc
  "%~dp0..\bin\win32\MSVC 2008\xdlrc_convert\Release\xdlrc_convert" %%i.xdlrc
  del %%i.xdlrc
  echo;
  echo;
)

echo ----------------------------------------------------------------------
echo Deleting temporary data...
rd /s /q "_xmsgs" 2> nul
echo Finished.

:end