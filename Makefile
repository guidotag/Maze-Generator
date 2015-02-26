CXX = g++
CXXFLAGS = -O2 -Wall -std=c++0x -pedantic

BIN = Maze
OBJS = Maze.o

.PHONY: clean

$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $(BIN)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(BIN)
	rm -f $(OBJS)