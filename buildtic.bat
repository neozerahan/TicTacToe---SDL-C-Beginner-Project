echo off

SETLOCAL

REM Sets the project path to the path where the build file is...
set projectPath=%~dp0
set executableName=game

REM Build flags...
set buildFlags=

REM LIBRARIES... 
set libs=%projectPath%\Bin\SDL2.dll %projectPath%\Bin\SDL2_image.dll %projectPath%\Bin\SDL2_ttf.dll 

REM SOURCE... 
set source=%projectPath%\Source\*.c 

REM EXE... 
set exe=-o %projectPath%\Bin\%executableName%

REM INCLUDES... 
set includes=-I %projectPath%\Include

REM SET TERMINAL DEBUG WINDOW...
set terminalWindow=

echo.
if "%1"=="b" (
    echo BUILD MODE
    set buildFlags=-g
    ) 

if "%1"=="f" (
    echo FINAL MODE
    set terminalWindow=-mwindows
    ) 

if [%1]==[] (
    echo DEV MODE
    )
echo.

REM COMPILE... 
gcc %buildFlags% %exe% %source% %libs% %includes% %terminalWindow%       
   
echo.
if %ERRORLEVEL%==1 (
    echo RESULT = BUILD FAILED!
) else (

    echo RESULT = BUILD SUCCESS!
    cd %projectPath%Bin
    %executableName%.exe

    REM Going back to project root folder... 
    cd %projectPath% 
)

ENDLOCAL
