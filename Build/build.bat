echo off

set BUILD_COMMAND=%CD%\..\tools\util\bin\make.exe -f %CD%\..\Make\make_stm32l432kc.gmk all TYP_OS=win

echo Build command is: %BUILD_COMMAND%

%BUILD_COMMAND%
