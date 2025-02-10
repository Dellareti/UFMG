CXX = g++
CXXFLAGS = -c -I. -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -g -std=c++17
DEPS = rede_eletrica.hpp
OBJ = rede_eletrica.o main.o 
EXEC = tp2

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^

clean:
	rm -f *.o $(EXEC)