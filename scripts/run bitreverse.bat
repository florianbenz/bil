@echo off
setlocal

set /p ans=Run bitreverse for all bitfiles in testbase? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\test"
call:bitreverse "xc5vfx100t\ff1136\jpegenc.bit" ff1136 "xc5vfx100t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vfx100t\ff1136\jpegenc.bit" ff1136 "xc5vfx100t\ff1136\jpegenc.rev.xdl" 
call:bitreverse "xc5vfx100t\ff1738\jpegenc.bit" ff1738 "xc5vfx100t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vfx130t\ff1738\jpegenc.bit" ff1738 "xc5vfx130t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vfx200t\ff1738\jpegenc.bit" ff1738 "xc5vfx200t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vfx30t\ff665\jpegenc.bit" ff665 "xc5vfx30t\ff665\jpegenc.rev.xdl"
call:bitreverse "xc5vfx70t\ff1136\jpegenc.bit" ff1136 "xc5vfx70t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vfx70t\ff665\jpegenc.bit" ff665 "xc5vfx70t\ff665\jpegenc.rev.xdl"
call:bitreverse "xc5vlx110\ff1153\jpegenc.bit" ff1153 "xc5vlx110\ff1153\jpegenc.rev.xdl"
call:bitreverse "xc5vlx110\ff1760\jpegenc.bit" ff1760 "xc5vlx110\ff1760\jpegenc.rev.xdl"
call:bitreverse "xc5vlx110\ff676\jpegenc.bit" ff676 "xc5vlx110\ff676\jpegenc.rev.xdl"
call:bitreverse "xc5vlx110t\ff1136\jpegenc.bit" ff1136 "xc5vlx110t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vlx110t\ff1738\jpegenc.bit" ff1738 "xc5vlx110t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vlx155\ff1153\jpegenc.bit" ff1153 "xc5vlx155\ff1153\jpegenc.rev.xdl"
call:bitreverse "xc5vlx155\ff1760\jpegenc.bit" ff1760 "xc5vlx155\ff1760\jpegenc.rev.xdl"
call:bitreverse "xc5vlx155t\ff1136\jpegenc.bit" ff1136 "xc5vlx155t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vlx155t\ff1738\jpegenc.bit" ff1738 "xc5vlx155t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vlx20t\ff323\jpegenc.bit" ff323 "xc5vlx20t\ff323\jpegenc.rev.xdl"
call:bitreverse "xc5vlx220\ff1760\jpegenc.bit" ff1760 "xc5vlx220\ff1760\jpegenc.rev.xdl"
call:bitreverse "xc5vlx220t\ff1738\jpegenc.bit" ff1738 "xc5vlx220t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vlx30\ff324\jpegenc.bit" ff324 "xc5vlx30\ff324\jpegenc.rev.xdl"
call:bitreverse "xc5vlx30\ff324\twofish_S128.bit" ff324 "xc5vlx30\ff324\twofish_S128.rev.xdl"
call:bitreverse "xc5vlx30\ff676\jpegenc.bit" ff676 "xc5vlx30\ff676\jpegenc.rev.xdl"
call:bitreverse "xc5vlx30t\ff323\jpegenc.bit" ff323 "xc5vlx30t\ff323\jpegenc.rev.xdl"
call:bitreverse "xc5vlx30t\ff665\jpegenc.bit" ff665 "xc5vlx30t\ff665\jpegenc.rev.xdl"
call:bitreverse "xc5vlx330\ff1760\jpegenc.bit" ff1760 "xc5vlx330\ff1760\jpegenc.rev.xdl"
call:bitreverse "xc5vlx330t\ff1738\jpegenc.bit" ff1738 "xc5vlx330t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vlx50\ff1153\jpegenc.bit" ff1153 "xc5vlx50\ff1153\jpegenc.rev.xdl"
call:bitreverse "xc5vlx50\ff324\jpegenc.bit" ff324 "xc5vlx50\ff324\jpegenc.rev.xdl"
call:bitreverse "xc5vlx50\ff676\jpegenc.bit" ff676 "xc5vlx50\ff676\jpegenc.rev.xdl"
call:bitreverse "xc5vlx50t\ff1136\jpegenc.bit" ff1136 "xc5vlx50t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vlx50t\ff665\jpegenc.bit" ff665 "xc5vlx50t\ff665\jpegenc.rev.xdl"
call:bitreverse "xc5vlx85\ff1153\jpegenc.bit" ff1153 "xc5vlx85\ff1153\jpegenc.rev.xdl"
call:bitreverse "xc5vlx85\ff676\jpegenc.bit" ff676 "xc5vlx85\ff676\jpegenc.rev.xdl"
call:bitreverse "xc5vlx85t\ff1136\jpegenc.bit" ff1136 "xc5vlx85t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vsx240t\ff1738\jpegenc.bit" ff1738 "xc5vsx240t\ff1738\jpegenc.rev.xdl"
call:bitreverse "xc5vsx35t\ff665\jpegenc.bit" ff665 "xc5vsx35t\ff665\jpegenc.rev.xdl"
call:bitreverse "xc5vsx50t\ff1136\jpegenc.bit" ff1136 "xc5vsx50t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vsx50t\ff665\jpegenc.bit" ff665 "xc5vsx50t\ff665\jpegenc.rev.xdl"
call:bitreverse "xc5vsx95t\ff1136\jpegenc.bit" ff1136 "xc5vsx95t\ff1136\jpegenc.rev.xdl"
call:bitreverse "xc5vtx150t\ff1156\jpegenc.bit" ff1156 "xc5vtx150t\ff1156\jpegenc.rev.xdl"
call:bitreverse "xc5vtx150t\ff1759\jpegenc.bit" ff1759 "xc5vtx150t\ff1759\jpegenc.rev.xdl"
call:bitreverse "xc5vtx240t\ff1759\jpegenc.bit" ff1759 "xc5vtx240t\ff1759\jpegenc.rev.xdl"
goto end

:bitreverse
echo ----------------------------------------------------------------------
echo bitreverse
echo   -dp "..\data"
echo   %1
echo   %2
echo   %3
echo ----------------------------------------------------------------------
echo;
"%~dp0..\bin\win32\MSVC 2008\bitreverse\Release\bitreverse" -dp "..\data" %~1 %~2 %~3
echo;
echo;
goto:eof

:end