CXX = gcc
CXXFLAGS = -Wall -std=c99

part1: part1.o
	$(CXX) $(CXXFLAGS) part1.o -o part1

part1.o: part1.c part1.h
	$(CXX) $(CXXFLAGS) -c part1.c

clean:
	rm -rf part1 *.o