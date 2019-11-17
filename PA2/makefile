# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2
TARGET = src/main.cpp
all	: 
	$(CC) $(TARGET) -o mps -g

clean : 
	rm -rf ./mps *.out *.log