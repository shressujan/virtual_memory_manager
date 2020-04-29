CXX = gcc
CXXFLAGS = -Wall -std=c99

part2: part2.o
	$(CXX) $(CXXFLAGS) part2.o -o part2

part2.o: part2.c part2.h
	$(CXX) $(CXXFLAGS) -c part2.c

clean:
	rm -rf part2 *.o