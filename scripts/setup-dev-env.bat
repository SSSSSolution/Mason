@echo off
setlocal

:: get the path to the current script
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%/.."

:: clone vcpkg
if exist vcpkg (
    echo vcpkg already exists. Skipping clone and bootstrap.
    cd vcpkg
) else (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
    if errorlevel 1 (
        echo Failed to clone vcpkg.
        exit /b 1
    )

    :: bootstrap vcpkg
    echo Bootstrapping vcpkg...
    cd vcpkg
    call bootstrap-vcpkg.bat
    if errorlevel 1 (
        echo Failed to bootstrap vcpkg.
        exit /b 1
    )
)

:: install dependencies
echo Installing dependencies...

:: install gtest
echo Installing gtest...
call vcpkg install gtest:x64-windows
if errorlevel 1 (
    echo Failed to install gtest.
    exit /b 1
)

:: install spdlog
echo Installing spdlog...
call vcpkg install spdlog:x64-windows
if errorlevel 1 (
    echo Failed to install spdlog.
    exit /b 1
)

:: install bullet3
echo Installing bullet3
call vcpkg install bullet3:x64-windows
if errorlevel 1 (
    echo Failed to install bullet3.
    exit /b 1
)

:: return to the original directory
cd /d "%SCRIPT_DIR%/.."

:: print instructions
echo Setup complete. When running CMake, use the following command line:
echo cmake -DCMAKE_TOOLCHAIN_FILE=%cd%/vcpkg/scripts/buildsystems/vcpkg.cmake

endlocal
