set PATH=C:\msys64\mingw64\bin;%PATH%
set SFML_DIR=C:\msys64\mingw64
if not exist build mkdir build
g++ -c -o build/main.o src/main.cpp -D SFML_STATIC
g++ -c -o build/player.o src/player.cpp -D SFML_STATIC
g++ -c -o build/background.o src/background.cpp -D SFML_STATIC
g++ -c -o build/bullet.o src/bullet.cpp -D SFML_STATIC
g++ -o build\main build\main.o build\player.o build\background.o build\bullet.o ^
    -LC:\msys64\mingw64\lib -static -lsfml-graphics-s -lsfml-window-s -lsfml-system-s ^
    -lgdi32 -lopengl32 -lwinmm -luser32 -lversion
echo Build complete. Run build\main.exe to execute.
timeout /t 10 
