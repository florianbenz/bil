@echo off
setlocal

set /p ans=Copy correlation results from testbase to data directory? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\test"
copy /y xc5vfx100t\ff1136\jpegenc.cdb ..\data\xc5vfx100tff1136.cdb
copy /y xc5vfx100t\ff1738\jpegenc.cdb ..\data\xc5vfx100tff1738.cdb
copy /y xc5vfx130t\ff1738\jpegenc.cdb ..\data\xc5vfx130tff1738.cdb
copy /y xc5vfx200t\ff1738\jpegenc.cdb ..\data\xc5vfx200tff1738.cdb
copy /y xc5vfx30t\ff665\jpegenc.cdb ..\data\xc5vfx30tff665.cdb
copy /y xc5vfx70t\ff1136\jpegenc.cdb ..\data\xc5vfx70tff1136.cdb
copy /y xc5vfx70t\ff665\jpegenc.cdb ..\data\xc5vfx70tff665.cdb
copy /y xc5vlx110\ff1153\jpegenc.cdb ..\data\xc5vlx110ff1153.cdb
copy /y xc5vlx110\ff1760\jpegenc.cdb ..\data\xc5vlx110ff1760.cdb
copy /y xc5vlx110\ff676\jpegenc.cdb ..\data\xc5vlx110ff676.cdb
copy /y xc5vlx110t\ff1136\jpegenc.cdb ..\data\xc5vlx110tff1136.cdb
copy /y xc5vlx110t\ff1738\jpegenc.cdb ..\data\xc5vlx110tff1738.cdb
copy /y xc5vlx155\ff1153\jpegenc.cdb ..\data\xc5vlx155ff1153.cdb
copy /y xc5vlx155\ff1760\jpegenc.cdb ..\data\xc5vlx155ff1760.cdb
copy /y xc5vlx155t\ff1136\jpegenc.cdb ..\data\xc5vlx155tff1136.cdb
copy /y xc5vlx155t\ff1738\jpegenc.cdb ..\data\xc5vlx155tff1738.cdb
copy /y xc5vlx20t\ff323\jpegenc.cdb ..\data\xc5vlx20tff323.cdb
copy /y xc5vlx220\ff1760\jpegenc.cdb ..\data\xc5vlx220ff1760.cdb
copy /y xc5vlx220t\ff1738\jpegenc.cdb ..\data\xc5vlx220tff1738.cdb
copy /y xc5vlx30\ff324\jpegenc.cdb ..\data\xc5vlx30ff324.cdb
copy /y xc5vlx30\ff676\jpegenc.cdb ..\data\xc5vlx30ff676.cdb
copy /y xc5vlx30t\ff323\jpegenc.cdb ..\data\xc5vlx30tff323.cdb
copy /y xc5vlx30t\ff665\jpegenc.cdb ..\data\xc5vlx30tff665.cdb
copy /y xc5vlx330\ff1760\jpegenc.cdb ..\data\xc5vlx330ff1760.cdb
copy /y xc5vlx330t\ff1738\jpegenc.cdb ..\data\xc5vlx330tff1738.cdb
copy /y xc5vlx50\ff1153\jpegenc.cdb ..\data\xc5vlx50ff1153.cdb
copy /y xc5vlx50\ff324\jpegenc.cdb ..\data\xc5vlx50ff324.cdb
copy /y xc5vlx50\ff676\jpegenc.cdb ..\data\xc5vlx50ff676.cdb
copy /y xc5vlx50t\ff1136\jpegenc.cdb ..\data\xc5vlx50tff1136.cdb
copy /y xc5vlx50t\ff665\jpegenc.cdb ..\data\xc5vlx50tff665.cdb
copy /y xc5vlx85\ff1153\jpegenc.cdb ..\data\xc5vlx85ff1153.cdb
copy /y xc5vlx85\ff676\jpegenc.cdb ..\data\xc5vlx85ff676.cdb
copy /y xc5vlx85t\ff1136\jpegenc.cdb ..\data\xc5vlx85tff1136.cdb
copy /y xc5vsx240t\ff1738\jpegenc.cdb ..\data\xc5vsx240tff1738.cdb
copy /y xc5vsx35t\ff665\jpegenc.cdb ..\data\xc5vsx35tff665.cdb
copy /y xc5vsx50t\ff1136\jpegenc.cdb ..\data\xc5vsx50tff1136.cdb
copy /y xc5vsx50t\ff665\jpegenc.cdb ..\data\xc5vsx50tff665.cdb
copy /y xc5vsx95t\ff1136\jpegenc.cdb ..\data\xc5vsx95tff1136.cdb
copy /y xc5vtx150t\ff1156\jpegenc.cdb ..\data\xc5vtx150tff1156.cdb
copy /y xc5vtx150t\ff1759\jpegenc.cdb ..\data\xc5vtx150tff1759.cdb
copy /y xc5vtx240t\ff1759\jpegenc.cdb ..\data\xc5vtx240tff1759.cdb
echo;

:end