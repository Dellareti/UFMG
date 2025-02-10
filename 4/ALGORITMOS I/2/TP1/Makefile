CXX=g++
CXXFLAGS=-I. -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -std=c++17 -g
DEPS = estado.h
OBJ = estado.o main.o 
EXEC = tp1

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC)