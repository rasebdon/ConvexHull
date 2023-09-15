CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

OUTPUT_DIR = out

SDL2LOC = .\lib\SDL2

INCLFLAGS = -I $(SDL2LOC)\include\SDL2
LDFLAGS = -L $(SDL2LOC)\lib -lmingw32 -lSDL2main -lSDL2

visual_r: visual
	.\$(OUTPUT_DIR)\visual.exe

visual: copy
	$(CXX) $(CXXFLAGS) src\main.cpp $(INCLFLAGS) $(LDFLAGS) -o $(OUTPUT_DIR)\visual.exe

copy:
	xcopy /Y .\lib\SDL2\bin\SDL2.dll $(OUTPUT_DIR)\

clean:
	del /f /q $(OUTPUT_DIR)\*