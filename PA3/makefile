# CC and CFLAGS are varilables
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3
TARGET = src/main.cpp
all	: 
	$(CXX) $(CXXFLAGS) $(TARGET)  -o cb 

clean : 
	rm -rf ./cb *.out *.log
