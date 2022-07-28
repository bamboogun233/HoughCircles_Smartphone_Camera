@echo off
title 清理脚本

echo.
echo "删除*.bak文件与bin文件夹下的所有文件"
echo.
echo Windows is cleaning...
echo.
echo Press '1' to start clean
echo.

:input
set INPUT=
set /P INPUT=Type test number: %=%
if "%INPUT%"=="1" goto run1
goto end

:run1
del /Q *.bak
cd bin
del /Q *.*

:end