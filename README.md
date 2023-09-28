# Windows Build Instructions
## Prerequisites
* MinGW32 or MSYS
* SDL2-2.28.3, 32 Bit MinGW Version (if it does not compile, try the x64 version)
* g++ Compiler
* C++ 17

## Step by step guide
* Copy the contents of the 32 Bit MinGW library into the lib/SDL2 folder
* For visual executable run: "make visual"
* For performance evaluation executable run: "make performance"

# Usage

convexhull.exe --type [performance | visual] --algo [giftwrapping | quickhull] --import [path=NULL] --points [amount=15] --iterations [amount=0] --output [true | false]

* --type: The runtime type, must be either performance or visual
* --algo: The algorithm that will be run, must be either giftwrapping or quickhull
* --import: Optional parameter to import a point file
* --points: Optional parameter to randomly generate the given amount of points
* --iterations: Optional parameter to increase performance mode iterations
* --output: Optional parameter to disable [false] command line output of results

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