@echo off
REM FynOS Build Script v0.1.0
REM Builds multi-stage bootloader with 32-bit protected mode kernel

echo.
echo ========================================
echo        Building FynOS v0.1.0
echo ========================================
echo.

if not exist build mkdir build

echo [1/3] Building Stage 1 bootloader...
nasm -f bin boot\bios\boot.asm -o build\boot.bin
if %errorlevel% neq 0 (
    echo ERROR: Stage 1 build failed!
    pause
    exit /b 1
)

echo [2/3] Building Stage 2 bootloader...
nasm -f bin boot\bios\stage2.asm -o build\stage2.bin
if %errorlevel% neq 0 (
    echo ERROR: Stage 2 build failed!
    pause
    exit /b 1
)

echo [3/3] Building 32-bit kernel...
nasm -f bin kernel\kernel-simple.asm -o build\kernel.bin
if %errorlevel% neq 0 (
    echo ERROR: Kernel build failed!
    pause
    exit /b 1
)

echo [4/4] Creating bootable OS image...
powershell -Command "Get-Content build\boot.bin, build\stage2.bin, build\kernel.bin -Encoding Byte | Set-Content build\fynos.img -Encoding Byte"

echo.
echo ========================================
echo     FynOS v0.1.0 Built Successfully!
echo ========================================
echo.

set /p choice="Launch in QEMU? (y/n): "
if /i "%choice%"=="y" (
    echo Starting FynOS...
    "C:\Program Files\qemu\qemu-system-i386.exe" -drive format=raw,file=build\fynos.img
)

pause