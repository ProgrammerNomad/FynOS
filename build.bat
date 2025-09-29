@echo off
REM FynOS Build Script for Windows
REM Requires NASM and QEMU to be in PATH

echo Building FynOS...

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Build the boot sector
nasm -f bin boot\bios\boot.asm -o build\boot.bin

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build successful!
echo.

REM Ask user if they want to run in QEMU
set /p choice="Run in QEMU? (y/n): "
if /i "%choice%"=="y" (
    echo Starting QEMU...
    qemu-system-i386 -drive format=raw,file=build\boot.bin
)

pause