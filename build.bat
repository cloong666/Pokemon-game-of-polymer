@echo off
REM Build and run the Pokemon Battle Game
REM Usage: build.bat [--run]

setlocal

set SCRIPT_DIR=%~dp0
set BUILD_DIR=%SCRIPT_DIR%build

echo === Pokemon Battle Game Build Script ===

REM Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

REM Configure with CMake
echo Configuring...
cmake "%SCRIPT_DIR%"
if errorlevel 1 (
    echo CMake configuration failed.
    exit /b 1
)

REM Build
echo Building...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo.
echo Build successful! Executable: %BUILD_DIR%\Release\pokemon_battle.exe
echo.

REM Run if --run flag is provided
if "%1"=="--run" (
    echo === Starting Battle ===
    "%BUILD_DIR%\Release\pokemon_battle.exe"
)
