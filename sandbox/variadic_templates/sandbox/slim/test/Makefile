BENCHMARK.suffix=mini
BENCHMARK.suffix=tree_builder
GUAGE=guage_gprof #how to measure the performance (python class in command_guage.py)
#GUAGE=guage_time
GUAGE=guage_heapprof

TIMEFMT:=%Y%m%d_%H%M%S_%N
TIMEVAL:=$(shell date +$(TIMEFMT))
#RUN_ID=20121119_073644_814249638
RUN_ID?=_
RUN_ID?=$(TIMEVAL)

PYTHON=python

#Filename macros:
SRC_BASENAME=$(shell $(PYTHON) tuple_benchmark_filenames.py 'src_basename' $(BENCHMARK.suffix))
SRC_EXT=$(shell $(PYTHON) tuple_benchmark_filenames.py 'src_ext')
OUT_SUFFIX=$(shell $(PYTHON) tuple_benchmark_filenames.py 'out_suffix' $(GUAGE) $(RUN_ID))
RUN_EXT=$(shell $(PYTHON) tuple_benchmark_filenames.py 'run_ext')
PKL_EXT=$(shell $(PYTHON) tuple_benchmark_filenames.py 'pkl_ext')
FILT_EXT=$(shell $(PYTHON) tuple_benchmark_filenames.py 'filt_ext')

RUN_PY=tuple_benchmark_run.py
DOM_PY=tuple_benchmark_domain.py
FILT_PY=tuple_benchmark_filt.py

#The stem (%) in the following pattern rules should be $(SRC_BASENAME)

%.$(OUT_SUFFIX).$(RUN_EXT): %.$(SRC_EXT) $(DOM_PY) $(RUN_PY)
	#runs compiler on $<, recording preformance in $@
	-python3.1 tuple_benchmark_run.py $(BENCHMARK.suffix) $(RUN_ID) $(GUAGE)

.PHONY: domain
domain: #prints the domains(inputs) used in $(RUN_FILENAME) target.
	$(PYTHON) tuple_benchmark_domain.py

%.$(OUT_SUFFIX).$(PKL_EXT): %.$(OUT_SUFFIX).$(RUN_EXT) 
	#produces parsed and pickled version of $< in $@
	$(PYTHON) tuple_benchmark_pickle.py $<

%.$(OUT_SUFFIX).$(FILT_EXT): %.$(OUT_SUFFIX).$(PKL_EXT) $(FILT_PY)
	#filters $< to produce $@
	$(PYTHON) tuple_benchmark_filt.py $< |tee $@

#The following targets are just shorthand for other targets.
.PHONY: brun
brun: $(SRC_BASENAME).$(OUT_SUFFIX).$(RUN_EXT)

.PHONY: pkl
pkl: $(SRC_BASENAME).$(OUT_SUFFIX).$(PKL_EXT)

.PHONY: filt
filt: $(SRC_BASENAME).$(OUT_SUFFIX).$(FILT_EXT)

.PHONY: show
show: #shows selected macro values.
	@echo "SRC_BASENAME:"$(SRC_BASENAME)
	@echo "OUT_SUFFIX:"$(OUT_SUFFIX)
	@echo "RUN_FILENAME:"$(SRC_BASENAME).$(OUT_SUFFIX).$(RUN_EXT)

