This project was done in a three person group as a part of the object oriented programming course with C++ at Aalto University.
You need to have SFML installed on your computer for this to work. Tested with SFML 2.5.1 (MinGW 32-bit) https://www.sfml-dev.org/download/sfml/2.5.1/
Build instructions (Windows with MinGW32):
1. mkdir build, navigate to build directory
2. Edit CMakeLists.txt to find your local SFML installation
3. cmake -G "MinGW Makefiles" ../
4. mingw32-make
5. Copy SFML .dlls to build directory
6. run dungeon_crawler.exe
