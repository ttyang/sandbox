MAIN=test
MAIN=tuple.benchmark

DIR.root := $(shell dirup_dir_file.pl $(PWD) root.imk)

HOW=gcc4_8n
HOW=clangxx

HOWS=gcc4_8n clangxx

include $(DIR.root)/root.imk

SLIM_DIR=../slim/include 
INCS:= -I$(SLIM_DIR) $(INCS)

.PHONY: tuple.benchmark.report
tuple.benchmark.report: tuple.benchmark.time.$(HOW)
	echo "DATE:" `date` >$@
	python time-report_tbl.py $(HOW) < $< >> $@

.PHONY: tuple.benchmark.time.how
tuple.benchmark.time.how: tuple.benchmark.time.$(HOW)

TIME_FORMAT="user:%U\nsystem:%S\nelapsed:%e"
TUPLE_MAX_SIZE=16
TUPLE_MIN_SIZE=4
TUPLE_DEL_SIZE=4
TUPLE_SIZES=$(TUPLE_MAX_SIZE) 

tuple.benchmark.time.$(HOW).txt: tuple.benchmark.cpp
	-rm $@
	echo -n "COMPILER_VERSION:" >>$@ ; \
	echo $(HOW) >>$@ ; \
	for VALU_AT in -DVALU_AT ; do \
	  echo "VALU_AT:"$$VALU_AT >>$@ ; \
	  for TUPLE_TEST_IMPL in 0 1 ; do \
	    echo "TUPLE_TEST_IMPL:"$$TUPLE_TEST_IMPL >>$@ ; \
	    for TUPLE_SIZE in $(TUPLE_SIZES) ; do \
	      echo "TUPLE_SIZE:"$$TUPLE_SIZE >>$@ ; \
	      for LAST_LESS in `python ./first_to_last_ints.py $(TUPLE_MIN_SIZE) $(TUPLE_DEL_SIZE) $$TUPLE_SIZE ` ; do \
	        echo "LAST_LESS:"$$LAST_LESS >>$@ ; \
	        time --format $(TIME_FORMAT) $(COMPILE.$(HOW)) \
                  $(INCS) \
                  -DTUPLE_TEST_IMPL=$$TUPLE_TEST_IMPL \
                  -DTUPLE_SIZE=$$TUPLE_SIZE \
                  -DLAST_LESS=$$LAST_LESS \
                  $$VALU_AT tuple.benchmark.cpp 2>>$@ ; \
	      done \
	    done \
	  done \
	done \
	#

.PHONY: tuple.benchmark.time
tuple.benchmark.time:
	for COMPILE_HOW in $(HOWS) ; do \
	  make -Wtuple.benchmark.cpp HOW=$$COMPILE_HOW tuple.benchmark.time.$$COMPILE_HOW ; \
	done

.PHONY: compiler_value.txt
compiler_value.txt:
	echo $(HOW)":" >>compiler_values.txt
	echo -n "  * version=" >>compiler_values.txt
	  $(COMPILE.$(HOW)) --version >>compiler_values.txt
	echo    "  * command="$(COMPILE.$(HOW)) >>compiler_values.txt

.PHONY: compiler_values.txt
compiler_values.txt:
	echo "INCS:"$(INCS) >$@
	for COMPILE_HOW in $(HOWS) ; do \
	  make compiler_value.txt HOW=$$COMPILE_HOW ; \
	done \
	#

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
	echo $(COMPILE)
