CK_demo_run: CK_demo
	@./${@:_run=}
OBJS=CK_demo.o CK.o
CK_demo: $(OBJS)
	g++ $(OBJS) -o $@
$(OBJS): CK.h
CK.o: CK.cpp
	gcc -c -O$(OPT) CK.cpp
CK_demo.o: CK_demo.cpp
	g++ -c -O2 CK_demo.cpp

# -------------------------
# 			default targets
all: CK.o
clean:
	-rm -f a.out core
	-rm $(OBJS) CK_demo
