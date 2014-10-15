GXX = g++

.PHONY: all clean

all: Maze.o
	$(GXX) -o Maze $<
	
%.o: %.cpp
	$(GXX) -c -o $@ $<

clean:
	rm -f Maze Maze.o
