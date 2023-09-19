# Windows Build Instructions
## Prerequisites
* MinGW32
* SDL2-2.28.3, 32 Bit MinGW Version (if it does not compile, try the x64 version)
* g++ Compiler
* C++ 17

## Step by step guide
* Copy the contents of the 32 Bit MinGW library into the lib/SDL2 folder
* For visual executable run: "make visual"
* For performance evaluation executable run: "make performance"