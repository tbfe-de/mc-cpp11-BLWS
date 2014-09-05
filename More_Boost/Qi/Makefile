DEMOS=demo perf
include ../Makefile
perf:	perf.o
	g++ -o $@ perf.o
	@echo -n "now running "
	./$@
