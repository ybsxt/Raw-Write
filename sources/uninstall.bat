@echo off
title 卸载Raw Write
set guid={DE44C67E-C60C-4206-A81E-5015C0B2BC80}
set installdir=%UserProFile%\AppData\Local\Raw Write
set uninstallreg=HKCU\Software\Microsoft\Windows\CurrentVersion\Uninstall\%guid%
set /p ifuninstall=是否要卸载Raw Write?(Y/N)
if %ifuninstall%==y (goto uninstall)
if %ifuninstall%==Y (goto uninstall) else exit
:uninstall
reg delete %uninstallreg% /f
rd "%installdir%" /s /q
echo 卸载完成
pause
exit
