::@echo off

:: Add SFML bin directory to PATH
set PATH=C:\msys64\mingw64\bin;%PATH%

:: Set the SFML library path
set SFML_DIR=C:\msys64\mingw64

:: Create the build directory if it does not exist
if not exist build mkdir build

:: Compile the source files with SFML static linking
g++ -c -o build/main.o src/main.cpp -D SFML_STATIC
g++ -c -o build/player.o src/player.cpp -D SFML_STATIC

:: Link the object files and SFML static libraries, including required system libraries
g++ -o build\main build\main.o build\player.o ^
    -LC:\msys64\mingw64\lib -static -lsfml-graphics-s -lsfml-window-s -lsfml-system-s ^
    -lgdi32 -lopengl32 -lwinmm -luser32 -lversion

echo Build complete. Run build\main.exe to execute.
pause
