# Windows Build Instructions
## Prerequisites
* MinGW32
* SDL2-2.28.3, 32 Bit MinGW Version (content of i686-w64-mingw32 folder)
* g++ Compiler
* C++ 17

## Step by step guide
* Copy the contents of the 32 Bit MinGW library into the lib/SDL2 folder
* For visual executable run: "make visual"
* For performance evaluation executable run: "make performance"