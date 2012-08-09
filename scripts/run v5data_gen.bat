@echo off
setlocal

set /p ans=Run v5data_gen? [y/n] 
if not "%ans%"=="y" goto end
echo;

cd /D "%~dp0..\data"
set DATA_DIR=%CD%
cd /D "%~dp0..\bin\win32\MSVC 2008\v5data_gen\Release"
echo ----------------------------------------------------------------------
echo v5data_gen "%DATA_DIR%"
echo ----------------------------------------------------------------------
v5data_gen "%DATA_DIR%"
echo;
echo;

:end