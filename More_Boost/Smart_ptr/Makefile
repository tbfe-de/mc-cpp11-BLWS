DEMOS=demo demo2
include ../Makefile

CDCA_DIR=../../Util/CDCA_Tracer
demo.o:	demo.cpp
	$(COMPILE) -I../.. -I$(BOOST_INC_DIR) demo.cpp
demo:	demo.o
	$(LINK) demo.o $(CDCA_DIR)/CDCA_Tracer.o -o $@
