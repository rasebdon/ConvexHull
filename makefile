CXX = g++
CXXFLAGS = -std=c++17
DEBUGFLAGS = -Wall -g

SRC_DIR = src
OUTPUT_DIR = out

SDL2DIR= lib\\SDL2

INCLFLAGS = -I $(SDL2DIR)\\include\\SDL2
LDFLAGS = -L $(SDL2DIR)\\lib -lmingw32 -lSDL2main -lSDL2

SRCS = $(SRC_DIR)\\*.cpp

TARGET = convexhull

quickhull_visual: $(TARGET)
	.\\$(OUTPUT_DIR)\\$(TARGET).exe --type visual --algo quickhull

quickhull: $(TARGET)
	.\\$(OUTPUT_DIR)\\$(TARGET).exe --type performance --algo quickhull

giftwrapping_visual: $(TARGET)
	.\\$(OUTPUT_DIR)\\$(TARGET).exe --type visual --algo giftwrapping

giftwrapping: $(TARGET)
	.\\$(OUTPUT_DIR)\\$(TARGET).exe --type performance --algo giftwrapping

convexhull: copy
	$(CXX) $(CXXFLAGS) $(SRCS) $(INCLFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)\\convexhull.exe

convexhull_debug: copy
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(SRCS) $(INCLFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)\\convexhull_debug.exe

test:
	$(CXX) $(CXXFLAGS) .\\src\\quickhull.cpp .\\src\\giftwrapping.cpp .\\tests\\test.cpp -Isrc -Itests -o $(OUTPUT_DIR)\\test.exe
	.\\$(OUTPUT_DIR)\\test.exe

copy:
	.\\copy.bat

clean:
	.\\del.bat
