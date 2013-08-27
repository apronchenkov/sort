CC = g++-4.6
CXX = g++-4.6
CXXFLAGS = -std=c++0x -Wall -Wextra -pedantic -O2 -g

.PHONY: all clean

all: test print_time_series

test.o: InsertionSort.h QuickSort.h RadixSort.h

clean:
	${RM} test print_time_series *.o
