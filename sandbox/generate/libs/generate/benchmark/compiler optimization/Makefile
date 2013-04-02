SRC = main.cpp
OBJ = $(SRC:%.cpp=%.o)
DEPENDFILE = .depend
CC  = g++ #icpc #g++
BIN = copt
CFLAGS = -std=c++0x -I/opt/boost_1_52_0/
OPTFLAGS = -O3 -ftree-vectorize -mmmx -msse -msse2 -msse4.1 -msse4.2 -floop-parallelize-all -march=corei7 -ffast-math -fassociative-math #-fast -msse2 -march=corei7 -m64 #-O3 -ftree-vectorize -msse -msse2 -march=corei7 -ffast-math -fassociative-math #-O3 -ftree-vectorize -msse -msse2 -floop-parallelize-all #-march=corei7 #-ffast-math -fassociative-math #-ftree-vectorizer-verbose=5 #-floop-parallelize-loops=8 #-O2 -ftree-vectorize -msse2 -ftree-vectorizer-verbose=5 #-O0 #-floop-optimize
OPTFLAGSSTRMACRO = -D __OPTIMIZATIONS="$(CC)-4.7 $(OPTFLAGS)"
LDFLAGS = 

all: $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OPTFLAGSSTRMACRO) -c $<

clean:
	rm -rf $(BIN) $(OBJ)

dep: $(SRC)
	$(CC) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)


