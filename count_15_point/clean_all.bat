echo ��������VS2015�����в���Ҫ���ļ�
echo ��ȷ�����ļ������ڹ���Ŀ¼֮�в��ر�VS2015
echo ��ʼ�������Ե�......

echo �����ļ���
@echo off
rd/s/q "..\Debug"
rd/s/q ".\Debug"
rd/s/q "..\release"
rd/s/q ".\release"
rd/s/q "..\x64"
rd/s/q ".\x64"
rd/s/q "..\.vs"

echo ����sdf�ļ�
del /q/a/f/s *.sdf

echo ����db�ļ�
del /q/a/f/s ..\*.db


echo ����Temp�ļ�
del /q/a/f/s Temp\*.*

ECHO �ļ�������ϣ���������3����˳������ڽ��뵹��ʱ.........
@echo off
echo WScript.Sleep 300 > %temp%.\tmp$$$.vbs
set /a i =3
:Timeout
if %i% == 0 goto Next
setlocal
set /a i = %i% - 1
echo ����ʱ����%i%
cscript //nologo %temp%.\tmp$$$.vbs
goto Timeout
goto End
:Next
cls &
echo.