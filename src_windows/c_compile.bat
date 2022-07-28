
@echo off
title C语言自动编译脚本

echo.
echo "生成上采样、下采样和参数读取程序"
echo.
echo C language is compiling...
echo.
echo Press '1' to start compile
echo.

:input
set INPUT=
set /P INPUT=Type test number: %=%
if "%INPUT%"=="1" goto run1
goto end

:run1
md bin
echo Start compile;
echo.
echo.
gcc -c bmp.c -std=c99 -Wall -lm -o bin/bmp.o
gcc -c scale.c -std=c99 -Wall -lm -o bin/scale.o
gcc downscale_main.c bin/scale.o bin/bmp.o -std=c99 -Wall -lm -o bin/downscale
gcc read_header_main.c bin/bmp.o -std=c99 -Wall -lm -o bin/read_header
gcc upscale_example.c bin/scale.o bin/bmp.o -std=c99 -Wall -lm -o bin/upscale_example

:end