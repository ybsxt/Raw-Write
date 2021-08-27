@echo off
title 安装Raw Write
set guid={DE44C67E-C60C-4206-A81E-5015C0B2BC80}
set installdir=%UserProFile%\AppData\Local\Raw Write
set uninstallreg=HKCU\Software\Microsoft\Windows\CurrentVersion\Uninstall\%guid%
set /p ifinstall=是否要安装Raw Write?(Y/N)
if %ifinstall%==y (goto install)
if %ifinstall%==Y (goto install) else exit
:install
md "%installdir%"
xcopy Files\ "%installdir%" /e /y
reg add %uninstallreg% /f
reg add %uninstallreg% /v DisplayName /t REG_SZ /d "Raw Write" /f
reg add %uninstallreg% /v InstallLocation /t REG_SZ /d "%installdir%" /f
reg add %uninstallreg% /v Publisher /t REG_SZ /d ybsxt /f 
reg add %uninstallreg% /v DisplayIcon /t REG_SZ /d "%installdir%\rawwrite.exe" /f
reg add %uninstallreg% /v UninstallString /t REG_SZ /d "%installdir%\uninstall.bat" /f
reg add %uninstallreg% /v DisplayVersion /t REG_SZ /d 1.0.0 /f
reg add %uninstallreg% /v VersionMajor /t REG_DWORD /d 1 /f
reg add %uninstallreg% /v VersionMinor /t REG_DWORD /d 0 /f
reg add %uninstallreg% /v NoModify /t REG_DWORD /d 1 /f
reg add %uninstallreg% /v NoRepair /t REG_DWORD /d 1 /f
echo 安装完成
pause
exit






