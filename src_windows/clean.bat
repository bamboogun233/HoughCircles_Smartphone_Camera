@echo off
title ����ű�

echo.
echo "ɾ��*.bak�ļ���bin�ļ����µ������ļ�"
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