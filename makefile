CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC_DIR = src
OUTPUT_DIR = out

SDL2DIR= lib\\SDL2

INCLFLAGS = -I $(SDL2DIR)\\include\\SDL2
LDFLAGS = -L $(SDL2DIR)\\lib -lmingw32 -lSDL2main -lSDL2

SRCS = $(SRC_DIR)\\*.cpp

visual_r: visual
	.\\$(OUTPUT_DIR)\visual.exe

visual: copy
	$(CXX) $(CXXFLAGS) $(SRCS) $(INCLFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)\\visual.exe

test:
	$(CXX) $(CXXFLAGS) .\\src\\quickhull.cpp .\\src\\giftwrapping.cpp .\\tests\\test.cpp -Isrc -Itests -o $(OUTPUT_DIR)\\test.exe
	.\\$(OUTPUT_DIR)\\test.exe

copy:
	./copy.bat

clean:
	./del.bat
