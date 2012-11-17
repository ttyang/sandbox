BENCHMARK.which=mini
BENCHMARK.which=tree_builder
TIMEFMT=%Y-%m-%d_%T_%N
#TIMESTAMP.value=_
TIMESTAMP.value?=$(shell date +$(TIMEFMT))
GUAGE=guage_time
BENCHMARK.prefix=$(shell python benchmark_prefix_name.py)
MAIN=$(BENCHMARK.prefix).$(BENCHMARK.which)
MEASURED=$(MAIN).$(GUAGE)@$(TIMESTAMP.value)
PYTHON=python

.PHONY: brun
brun:#produces $(MEASURED).txt from $(MAIN).cpp
	$(PYTHON) tuple_benchmark_run.py $(BENCHMARK.which) $(TIMESTAMP.value)

.PHONY: domain
domain:
	$(PYTHON) tuple_benchmark_domain.py

parse:#produces domain_range.pkl from $(MEASURED).txt
	$(PYTHON) tuple_benchmark_parserange.py $(MEASURED).txt

.PHONY: plot
plot: domain_range.pkl#produces filtered output from domain_range.pkl
	$(PYTHON) tuple_benchmark_plot.py domain_range.pkl

.PHONY: show
show:#shows selected macro values.
	echo $(BENCHMARK.prefix)
