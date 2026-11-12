@echo off
cd /d "%~dp0"

rem Use MSYS2 ucrt64 for gcc, cmake, ninja, Qt if available
if exist C:\msys64\ucrt64\bin set PATH=C:\msys64\ucrt64\bin;%PATH%

set BUILD_TYPE=Ninja
set BUILD_FOLDER=build_qt
set SOURCE_FOLDER=src

chcp 65001 > nul

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

set GAME_TYPE=Qt

cmake -G %BUILD_TYPE% -DGAME_TYPE=%GAME_TYPE% "..\%SOURCE_FOLDER%"
cmake --build .

cd ..
