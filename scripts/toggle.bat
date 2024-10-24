@ECHO OFF
::makes calling this script possible from any location
PUSHD %~dp0

ECHO %cmdcmdline% | FIND /i "%~0"
SET launchedFromCmd=%ERRORLEVEL%

CD ..
IF EXIST  src\main.cpp GOTO toArduinoIDE
IF EXIST main\main.ino GOTO toPlatformIO

ECHO Project structure is not recognized
ECHO Please consider reseting it
::returns cmd to original location
::if the script was called not from its own one
CALL :popAndPause
EXIT /b 1

:toArduinoIDE
ECHO Changing to ArduinoIDE project structure

RENAME src main
CD     main
RENAME main.cpp main.ino
CALL :popAndPause
EXIT /b

:toPlatformIO
ECHO Changing to PlatformIO project structure

RENAME main src
CD     src
RENAME main.ino main.cpp
CALL :popAndPause
EXIT /b

:popAndPause
POPD
IF %launchedFromCmd%==0 PAUSE
