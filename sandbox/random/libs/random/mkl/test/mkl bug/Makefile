# Copyright Fabian Bösch 2013
#
# Use, modification and distribution are subject to the
# Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)


NAME=example.out
SOURCES = example.cpp
MKLDIR := $(MKLROOT)
LIBMKL := -Wl,--start-group  $(MKLDIR)/lib/intel64/libmkl_intel_ilp64.a $(MKLDIR)/lib/intel64/libmkl_sequential.a $(MKLDIR)/lib/intel64/libmkl_core.a -Wl,--end-group 
CPLUSPLUS := g++
CPLUSPLUSFLAGS :=  -DMKL_ILP64 -m64 -I$(MKLDIR)/include -O0 -g
CPLUSPLUSLINK := $(CPLUSPLUS)
CPLUSPLUSLINKFLAGS :=  
CPLUSPLUSLINKLIBS := -lpthread -lm
OBJFILES = $(SOURCES:.cpp=.o)

all: build

build: $(OBJFILES)
	@echo -e "\033[1mLinking $(OBJFILES) to $(NAME)...\033[0m"
	@$(CPLUSPLUSLINK) $(CPLUSPLUSLINKFLAGS) $(OBJFILES) $(LIBMKL) $(CPLUSPLUSLINKLIBS) -o $(NAME)

%.o: %.cpp
	@echo -e "\033[1mCompiling $<...\033[0m"
	@$(CPLUSPLUS) -c $(CPLUSPLUSFLAGS) $< -o $@

clean:
	@echo -e "\033[1mCleaning up...\033[0m"
	@rm -f $(OBJFILES)

.PHONY: all build clean

