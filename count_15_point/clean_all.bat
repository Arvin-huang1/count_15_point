echo 正在清理VS2015工程中不需要的文件
echo 请确保本文件放置在工程目录之中并关闭VS2015
echo 开始清理请稍等......

echo 清理文件夹
@echo off
rd/s/q "..\Debug"
rd/s/q ".\Debug"
rd/s/q "..\release"
rd/s/q ".\release"
rd/s/q "..\x64"
rd/s/q ".\x64"
rd/s/q "..\.vs"

echo 清理sdf文件
del /q/a/f/s *.sdf

echo 清理db文件
del /q/a/f/s ..\*.db


echo 清理Temp文件
del /q/a/f/s Temp\*.*

ECHO 文件清理完毕！本程序将在3秒后退出！现在进入倒计时.........
@echo off
echo WScript.Sleep 300 > %temp%.\tmp$$$.vbs
set /a i =3
:Timeout
if %i% == 0 goto Next
setlocal
set /a i = %i% - 1
echo 倒计时……%i%
cscript //nologo %temp%.\tmp$$$.vbs
goto Timeout
goto End
:Next
cls &
echo.