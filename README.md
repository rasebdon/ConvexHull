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

# Algorithms

## Quickhull
* Divide and Conquer
* Take two points A = min(x) and B = max(x)
* Draw a Line
* Repeat the following:
    * Take point farthest away from line (C)
    * Draw lines between A - C and B - C
    * Ignore all points in the newly created shape

### Complexity
* Worst Case: n^2, all Points build the convex hull
* Best Case: n*log(n), partitions are symmetrical and evenly distributed