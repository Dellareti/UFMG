CXX=g++
CXXFLAGS=-I. -Wall -Wextra -Werror -pedantic -O2
DEPS = campanha.h
OBJ = campanha.o main.o 
EXEC = tp01

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC)