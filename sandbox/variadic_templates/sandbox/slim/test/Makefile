BENCHMARK.suffix=mini
BENCHMARK.suffix=tree_builder
TIMEFMT=%Y-%m-%d_%T_%N
#TIMESTAMP=_
TIMESTAMP?=$(shell date +$(TIMEFMT))
GUAGE=guage_time
PYTHON=python
#The following macros are only used in comments.
SRC_BASENAME=$(shell $(PYTHON) benchmark_filenames.py $(BENCHMARK.suffix))
OUT_BASENAME=$(shell $(PYTHON) benchmark_filenames.py $(BENCHMARK.suffix)\
  $(GUAGE)\
  $(TIMESTAMP)\
  )

.PHONY: brun
brun:#produces $(OUT_BASENAME).txt from $(SRC_BASENAME).cpp
	$(PYTHON) tuple_benchmark_run.py \
	  $(GUAGE) $(BENCHMARK.suffix) $(TIMESTAMP)

.PHONY: domain
domain:#prints the domains(inputs) used in brun target.
	$(PYTHON) tuple_benchmark_domain.py

parse:#produces domain_range.pkl from $(OUT_BASENAME).txt
	$(PYTHON) tuple_benchmark_parserange.py $(OUT_BASENAME).txt

.PHONY: plot
plot: domain_range.pkl#produces filtered output from domain_range.pkl
	$(PYTHON) tuple_benchmark_plot.py domain_range.pkl

.PHONY: show
show:#shows selected macro values.
	echo $(OUT_BASENAME)
