SRC = omp_fibonacci.cpp
OBJ = $(SRC:%.cpp=%.o)
DEPENDFILE = .depend
CC  = g++
BIN = fibonacci
CFLAGS = -O3 -std=c++0x -fopenmp -I/opt/boost_1_52_0/
LDFLAGS = -lgomp

all: $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(BIN) $(OBJ)

dep: $(SRC)
	$(CC) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)


