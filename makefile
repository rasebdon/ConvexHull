CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC_DIR = src
OUTPUT_DIR = out

SDL2DIR= .\lib\SDL2

INCLFLAGS = -I $(SDL2DIR)\include\SDL2
LDFLAGS = -L $(SDL2DIR)\lib -lmingw32 -lSDL2main -lSDL2

SRCS = $(SRC_DIR)/*.cpp

visual_r: visual
	.\$(OUTPUT_DIR)\visual.exe

visual: copy
	$(CXX) $(CXXFLAGS) $(SRCS) $(INCLFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)\visual.exe

copy:
	xcopy /Y $(SDL2DIR)\bin\SDL2.dll $(OUTPUT_DIR)\

clean:
	del /f /q $(OUTPUT_DIR)\*