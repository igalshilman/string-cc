CXX=clang++
CXXFLAGS=-O3 -std=c++14 -Wall -pedantic -flto -march=native
BIN=main.bin

SRC=$(wildcard *.cc)
OBJ=$(SRC:%.cc=%.o)

all: $(OBJ)
	    $(CXX) -o $(BIN) $^

%.o: %.c
	    $(CXX) $@ -c $<

clean:
	    rm -f *.o
			rm -f $(BIN)
