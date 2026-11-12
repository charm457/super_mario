@echo off
cd /d %~dp0
if exist C:\msys64\ucrt64\bin set PATH=C:\msys64\ucrt64\bin;%PATH%
start "" "build_qt\super_mario.exe"
