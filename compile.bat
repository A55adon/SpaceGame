:: Set the PATH to include the MinGW bin directory and the existing PATH
set PATH=C:\msys64\mingw64\bin;%PATH%

:: Set the SFML directory (used for linking)
set SFML_DIR=C:\msys64\mingw64

:: Create a build directory if it doesn't exist
if not exist build mkdir build

:: Compile source files into object files
g++ -c -o build/main.o src/main.cpp -D SFML_STATIC
g++ -c -o build/Game.o src/Game.cpp -D SFML_STATIC
g++ -c -o build/player.o src/player.cpp -D SFML_STATIC
g++ -c -o build/enemy.o src/enemy.cpp -D SFML_STATIC
g++ -c -o build/bullet.o src/bullet.cpp -D SFML_STATIC
g++ -c -o build/UI.o src/UI.cpp -D SFML_STATIC
g++ -c -o build/Button.o src/Button.cpp -D SFML_STATIC
g++ -c -o build/background.o src/background.cpp -D SFML_STATIC

:: Link all object files into the final executable
g++ -o build\main build\main.o build\player.o build\background.o build\bullet.o build\enemy.o build\UI.o build\Button.o build\Game.o ^
    -LC:\msys64\mingw64\lib -static -lsfml-graphics-s -lsfml-window-s -lsfml-system-s ^
    -lgdi32 -lopengl32 -lwinmm -luser32 -lversion

timeout /t 9