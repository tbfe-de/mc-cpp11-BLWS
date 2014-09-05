named_bits-test_run: named_bits-test
	@./named_bits-test

test1.o:test1.cpp named_bits.h
	g++ -c -O2 -I../.. test1.cpp
test1.s:test1.cpp named_bits.h
	g++ -S -O2 -DNDEBUG test1.cpp
test2.s:test2.cpp
	g++ -S -O2 -DNDEBUG test2.cpp

named_bits-test: named_bits-test.o
	g++ -o $@ named_bits-test.o

named_bits-test.o: named_bits-test.cpp named_bits.h
	g++ -c -Wno-overflow -I../.. named_bits-test.cpp

clean:
	-rm -f test1.o test1.s test2.s
	-rm -f a.out core named_bits-test
