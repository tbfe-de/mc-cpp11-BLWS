ALL=\
	quicksort-mt\
	quicksort-mt3\
	quicksort-mt2\
	quicksort-si\
	quicksort-st

all: $(ALL)
	@echo "all targets up-to-date"

quicksort-mt: quicksort.cpp
	g++ -O2 -std=c++0x -DQUICKSORT_THREADS=4 quicksort.cpp -lpthread -o $@
quicksort-mt3: quicksort.cpp
	g++ -O2 -std=c++0x -DQUICKSORT_THREADS=3 quicksort.cpp -lpthread -o $@
quicksort-mt2: quicksort.cpp
	g++ -O2 -std=c++0x -DQUICKSORT_THREADS=2 quicksort.cpp -lpthread -o $@
quicksort-si: quicksort.cpp
	g++ -O2 -std=c++0x -DQUICKSORT_CONCURRENT=1 quicksort.cpp -lpthread -o $@
quicksort-st: quicksort.cpp
	g++ -O2 -std=c++0x quicksort.cpp -o $@

clean:
	rm -f a.out core *.o $(ALL)
