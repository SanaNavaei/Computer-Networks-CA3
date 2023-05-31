CC = g++ -g -std=c++11

all: main.out

main.out: main.o command.o graph.o
	$(CC) $^ -o $@

main.o: src/main.cpp include/main.hpp include/command.hpp
	$(CC) -c $< -o $@

command.o: src/command.cpp include/command.hpp include/graph.hpp
	$(CC) -c $< -o $@

graph.o: src/graph.cpp include/graph.hpp
	$(CC) -c $< -o $@

.PHONY: clean

clean:
	rm *.o *.out
