STEPS=step1 step2 step3

all: ${STEPS}

clean: -rm -f a.out core ${ALL} *.o *.s

.cpp:
	g++ -std=c++11 -I../../Utilities/PT $< -o $@

.SUFFIXES: .tdd
.cpp.tdd:
	g++ -std=c++11 -I../../Utilities/PT -DTDD $< -o $@
	@echo "RUNNING $@ NOW:"
	./$@

