# Copyright Fabian Bösch 2013
#
# Use, modification and distribution are subject to the
# Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)

NAME=t1
SOURCES = main.cpp
ACMLDIR := /opt/acml5.2.0/gfortran64_int64
CPLUSPLUS := g++
CPLUSPLUSFLAGS := -I$(ACMLDIR)/include -I /opt/boost_1_52_0 -D BOOST_TEST_DYN_LINK
CPLUSPLUSLINK := $(CPLUSPLUS)
CPLUSPLUSLINKFLAGS :=  
CPLUSPLUSLINKLIBS := /opt/boost_1_52_0/stage/lib/libboost_unit_test_framework.so -lgfortran -lrt -ldl -lm
LIBACML := $(ACMLDIR)/lib/libacml.a
OBJFILES = $(SOURCES:.cpp=.o)

all: build

build: $(OBJFILES)
	@echo -e "\033[1mLinking $(OBJFILES) to $(NAME)...\033[0m"
	@$(CPLUSPLUSLINK) $(CPLUSPLUSLINKFLAGS) $(OBJFILES) $(LIBACML) $(CPLUSPLUSLINKLIBS) -o $(NAME)

%.o: %.cpp
	@echo -e "\033[1mCompiling $<...\033[0m"
	@$(CPLUSPLUS) -c $(CPLUSPLUSFLAGS) $< -o $@

clean:
	@echo -e "\033[1mCleaning up...\033[0m"
	@rm -f $(OBJFILES)

.PHONY: all build clean

