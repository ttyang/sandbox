MAIN=test
BENCHMARK=mini
MAIN=tuple.benchmark.$(BENCHMARK)
MEASURE=time
THISFILE=Makefile
PYTHON=python3.1

DIR.root := $(shell dirup_dir_file.pl $(PWD) root.imk)
include $(DIR.root)/root.imk
#include compiler_macros.imk

HOW=gcc4_8n
HOW=clangxx_rel

HOWS=gcc4_8n clangxx

SLIM_DIR=../slim/include 
#INCS:= -I$(SLIM_DIR) $(INCS)

BFLAGS=-DTUPLE_SIZE=4 -DLAST_LESS=2 -DTUPLE_IMPL=tuple_impl_compstor.hpp -DTUPLE_CHUNK=4
BFNAME:=$(shell ./flags2filename.pl -S $(BFLAGS))
PROF_BASE=$(MAIN).$(HOW).$(BFNAME)
COMPILER.clangxx_ins-rt=$(PATH.llvm.top)/llvm/projects/compiler-rt

.PHONY: bfname
bfname:
	./flags2filename.pl $(BFLAGS)

.PHONY: compiler_help
compiler_help:
	#$(COMPILER.$(HOW)) --help-hidden
	$(COMPILER.$(HOW)) --help|grep -e ' -time\| -print-stat'

compiler.hashes3.out: $(MAIN).cpp
	$(COMPILE.$(HOW)) -S -### $(BFLAGS) $(MAIN).cpp 2> $@

compiler.hashes3.cmd: compiler.hashes3.out
	#1) get just the compiler command line (tail -1 compiler.hashes3.out).
	#2) strip the double quote marks from the command line (s/\"//g).
	#3) send result to target (>$@)
	perl -e 'my $$args=join(" ",@ARGV);$$args=~s/\"//g;print $$args' `tail -1 compiler.hashes3`>$@

gmon.out: compiler.hashes3.cmd
	@echo $<"="
	@cat $<
	@echo ""
	$(SHELL) compiler.hashes3.cmd

gprof.out: gmon.out
	gprof $(COMPILER.$(HOW)) > gprof.out

.PHONY: mv_gmon_gprof
mv_gmon_gprof: gprof.out
	mv gmon.out $(PROF_BASE).gmon.out
	mv gprof.out $(PROF_BASE).gprof.out

$(PROF_BASE).gprof.out: mv_gmon_gprof

.PHONY: gprof_main
gprof_main:$(PROF_BASE).gprof.out

.PHONY: gprof2dot
gprof2dot:
	gprof2dot.py $(PROF_BASE).gprof.out|dot -Tgif -o $(PROF_BASE).gprof.gif

.PHONY: gdb.commands
gdb.commands:
	@echo "#gdb commands:" > $@
	@echo cd $(PWD) >> $@
	@echo file $(COMPILER.clangxx_dbg) >> $@
	@echo set args $(COMPILER.clangxx_dbg.libcxx) -c $(COMPILE.clangxx.flags.all) -c $(MAIN).cpp >> $@

.PHONY: compiler_help_driver
compiler_help_driver: compiler_help compiler_driver

.PHONY: main.o
main.o : $(MAIN).cpp
	$(COMPILE.$(HOW)) -c -std=c++11 $(BFLAGS) $(INCS) $<

.PHONY: tuple.benchmark.report
tuple.benchmark.report: $(MAIN).$(HOW).$(MEASURE)
	echo "DATE:" `date` >$@
	$(PYTHON) time-report_tbl.py $(HOW) < $< >> $@

.PHONY: tuple.benchmark.measure
tuple.benchmark.measure: $(MAIN).$(HOW).$(MEASURE).txt

TIME_FORMAT="user:%U\nsystem:%S\nelapsed:%e"
TUPLE_MAX_SIZE=4
TUPLE_MIN_SIZE=4
TUPLE_DEL_SIZE=4
TUPLE_SIZES=$(TUPLE_MAX_SIZE) 
TUPLE_IMPLS=\
  tuple_impl_horizontal.hpp\
  tuple_impl_vertical.hpp\
  #

.PHONY: $(MAIN).$(HOW).$(MEASURE).txt
$(MAIN).$(HOW).$(MEASURE).txt: $(MAIN).cpp
	-rm $@
	echo -n "COMPILER:" >>$@ ; \
	echo $(HOW) >>$@ ; \
	for VALU_AT in -DVALU_AT ; do \
	  echo "VALU_AT:"$$VALU_AT >>$@ ; \
	  for TUPLE_IMPL in $(TUPLE_IMPLS) ; do \
	    echo "TUPLE_IMPL:"$$TUPLE_IMPL >>$@ ; \
	    for TUPLE_SIZE in $(TUPLE_SIZES) ; do \
	      echo "TUPLE_SIZE:"$$TUPLE_SIZE >>$@ ; \
	      for LAST_LESS in `python ./first_to_last_ints.py $(TUPLE_MIN_SIZE) $(TUPLE_DEL_SIZE) $$TUPLE_SIZE ` ; do \
	        echo "LAST_LESS:"$$LAST_LESS >>$@ ; \
	        $(MEASURE) --format $(TIME_FORMAT) $(COMPILE.$(HOW)) \
                  $(INCS) \
                  -DTUPLE_IMPL=$$TUPLE_IMPL \
                  -DTUPLE_SIZE=$$TUPLE_SIZE \
                  -DLAST_LESS=$$LAST_LESS \
                  $$VALU_AT \
		  $(MAIN).cpp 2>>$@ ; \
	      done \
	    done \
	  done \
	done \
	#

.PHONY: tuple.benchmark.$(MEASURE)
tuple.benchmark.$(MEASURE):
	for COMPILE_HOW in $(HOWS) ; do \
	  make -W$(MAIN).cpp HOW=$$COMPILE_HOW $(MAIN).$$COMPILE_HOW.$(MEASURE).txt ; \
	done

.PHONY: nest_loop
nest_loop:
	for TUPLE_SIZE in $(TUPLE_SIZES) ; do \
	  echo "TUPLE_SIZE:"$$TUPLE_SIZE ; \
	  for LAST_LESS in `python ./first_to_last_ints.py $(TUPLE_MIN_SIZE) 2 $$TUPLE_SIZE ` ; do \
	    echo "  LAST_LESS:"$$LAST_LESS ; \
	  done \
	done \
	#

.PHONY: echo
echo:
	@echo "SHELL="$(SHELL)

.PHONY: python
python:
	$(PYTHON) tuple_benchmark_run.py
