SRC = mkl_benchmark.cpp
OBJ = $(SRC:%.cpp=%.o)
DEPENDFILE = .depend
CC  = g++
BIN = mkl_benchmark
CFLAGS = -O3 -std=c++0x -fopenmp -DMKL_ILP64 -m64 -I/opt/boost_1_52_0/ -I$$MKLROOT/include
LDFLAGS = -Wl,--start-group  $$MKLROOT/lib/intel64/libmkl_intel_ilp64.a $$MKLROOT/lib/intel64/libmkl_gnu_thread.a $$MKLROOT/lib/intel64/libmkl_core.a -Wl,--end-group -ldl -lpthread -lm -lgomp

all: $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(BIN) $(OBJ)

dep: $(SRC)
	$(CC) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)


