FILES = board.cpp initial.cpp display.cpp move.cpp input.cpp legal.cpp debug.cpp bitboards.cpp sdl.cpp collider.cpp 

SDL = -framework SDL2

OBJECTS = $(FILES:.cpp=.o)

EXECUTABLE = collider

CXX = clang++

CXXFLAGS = -Wall -pedantic -ferror-limit=256 -std=c++11 -c -I../include/  

LDFLAGS = $(SDL)

all: $(FILES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ 

clean:
	rm *.o && rm $(EXECUTABLE)
