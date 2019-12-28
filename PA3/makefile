# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c -g -std=c++11 -Wall -pedantic
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3
TARGET = src/main.cpp
all	: 
	$(CC) $(TARGET) -o cb $^

clean : 
	rm -rf ./cb *.out *.log
