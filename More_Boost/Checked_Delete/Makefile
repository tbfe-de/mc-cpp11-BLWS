demo: demo.cpp Base.h Derived.h Derived.cpp
	g++ -std=c++0x demo.cpp Derived.cpp -w -o $@
demo2: demo2.cpp Base.h Derived.h Derived.cpp
	g++ -std=c++0x demo2.cpp Derived.cpp -o $@
demo3: demo3.cpp Base.h Derived.h Derived.cpp
	g++ -std=c++0x demo3.cpp Derived.cpp -o $@
clean:
	rm -f demo demo2 demo3 a.out core *.o
