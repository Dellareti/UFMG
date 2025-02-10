CXX = g++
CXXFLAGS = -c -I. -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -g -std=c++17
DEPS = resolvedor_caixeiro.hpp
OBJ = resolvedor_caixeiro.o forca_bruta.o prog_dinamica.o guloso.o main.o
EXEC = tp3

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^

clean:
	rm -f *.o $(EXEC)