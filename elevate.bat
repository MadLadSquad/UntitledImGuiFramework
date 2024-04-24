@echo off
<!-- : --- self-elevating_no_temp.bat ---------------------
fsutil dirty query %systemdrive% >nul && goto :gotAdmin
echo Requesting administrative privileges...
set "ELEVATE_CMDLINE=cd /d "%cd%" & call "%~f0" %*"
cscript //nologo "%~f0?.wsf" //job:Elevate
exit /b

-->
<job id="Elevate"><script language="VBScript">
  Set objShell = CreateObject("Shell.Application")
  Set objWshShell = WScript.CreateObject("WScript.Shell")
  Set objWshProcessEnv = objWshShell.Environment("PROCESS")
  strCommandLine = Trim(objWshProcessEnv("ELEVATE_CMDLINE"))
  objShell.ShellExecute "cmd", "/c " & strCommandLine, "", "runas"
</script></job>
:gotAdmin -------------------------------------------------

echo Running script as admin.
echo Script file : %~f0
echo Arguments   : %*
echo Working dir : %cd%
echo.
%*
for /l %%x in (5, -1, 1) do (
  echo Running next script in %%x seconds
  timeout 1 > NUL
)
