@echo off

REM Build the project
echo [BUILD] Starting parallel build...
cmake --build build -j

REM Check for build failure
if %ERRORLEVEL% neq 0 (
    echo [ERROR] Build failed. Check the compilation errors.
    pause
    exit /b 1
)

REM Run the executable
echo [RUN] Build successful. Executing application...
cd build
.\space-rescue-mission.exe

REM Pause the terminal
pause