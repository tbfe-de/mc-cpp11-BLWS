DEMOS=bitcount bitcount2 # bitcount3
include ../Makefile
BOOST_ADDLIBS += -lboost_thread

.cpp:
	g++ -o $@ $(OPTIMIZE) -I$(BOOST_INC_DIR) $<\
		 -L$(BOOST_LIB_DIR) $(BOOST_ADDLIBS)

bitcount3: bitcount3.o ../Forked/Forked.o
	g++ -o $@ bitcount3.o ../Forked/Forked.o\
		-L$(BOOST_LIB_DIR) -lboost_program_options
