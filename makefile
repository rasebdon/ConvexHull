CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC_DIR = src
OUTPUT_DIR = out

SDL2DIR= lib\\SDL2

INCLFLAGS = -I $(SDL2DIR)\\include\\SDL2
LDFLAGS = -L $(SDL2DIR)\\lib -lmingw32 -lSDL2main -lSDL2

SRCS = $(SRC_DIR)\\*.cpp

quickhull_visual: convexHull
	.\\$(OUTPUT_DIR)\convexHull.exe --type visual --algo quickhull

quickhull: convexHull
	.\\$(OUTPUT_DIR)\convexHull.exe --type performance --algo quickhull

giftwrapping_visual: convexHull
	.\\$(OUTPUT_DIR)\convexHull.exe --type visual --algo giftwrapping

giftwrapping: convexHull
	.\\$(OUTPUT_DIR)\convexHull.exe --type performance --algo giftwrapping

convexHull: copy
	$(CXX) $(CXXFLAGS) $(SRCS) $(INCLFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)\\convexHull.exe

test:
	$(CXX) $(CXXFLAGS) .\\src\\quickhull.cpp .\\src\\giftwrapping.cpp .\\tests\\test.cpp -Isrc -Itests -o $(OUTPUT_DIR)\\test.exe
	.\\$(OUTPUT_DIR)\\test.exe

copy:
	.\\copy.bat

clean:
	.\\del.bat
