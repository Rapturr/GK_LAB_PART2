@ECHO OFF
SetLocal EnableDelayedExpansion


REM Get a list of all the .cpp files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

REM output exe file
SET assembly=main

REM flags, to show warnings etc
SET compilerFlags=-Wall

REM include headers from other libs and local ones. -I and path
SET includeFlags=-Isrc -I..\include

ECHO "Building %assembly%..."
g++ %cppFilenames% -o %assembly% %compilerFlags% %includeFlags%