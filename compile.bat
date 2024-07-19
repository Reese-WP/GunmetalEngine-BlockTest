@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

echo Setup required Environment
echo -------------------------------------
SET RAYLIB_PATH=C:\raylib\raylib
SET COMPILER_PATH=C:\raylib\w64devkit\bin
SET PATH=%COMPILER_PATH%;%PATH%
SET CC=g++
SET CFLAGS=%RAYLIB_PATH%\src\raylib.rc.data -s -static -Os -Wall -I%RAYLIB_PATH%\src -Iexternal -DPLATFORM_DESKTOP -I..\headers -g
SET LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm

cd src
echo
echo Clean latest build
echo ------------------------
IF EXIST ..\bin\main.exe del /F ..\bin\main.exe
echo

echo Collecting all .cpp files
echo -------------------------
SET SRCS=
FOR /R %%F IN (*.cpp) DO (
    SET SRCS=!SRCS! %%F
)
echo

echo Compile program
echo -----------------------
%CC% --version
%CC% -o ..\bin\main.exe !SRCS! %CFLAGS% %LDFLAGS%
echo

echo Reset Environment
echo --------------------------
echo

echo Execute program
echo -----------------------
IF EXIST ..\bin\main.exe ..\bin\main.exe
