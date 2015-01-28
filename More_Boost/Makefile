# =============================================================================
# Makefile for Boost-Workshop Examples
# =============================================================================
# This is the master Makefile to be included from Makefiles in subdirectories.
# Hence only the generic stuff goes here. Especially note that if there is a
# need for linking to libraries supplied with Boost, these have to be specified
# as value of BOOST_ADDLIBS in the individual Makefiles.
#
# NOTE:
# It is expected that a make process using a Makefile from a subdirectory is
# executed with this subdirectory as working directory, so the names of files
# and directories have to be specified from "one level below" the directory in
# which this master Makefile is located.

# ----------------------------------------------------- Set Boost Configuration
#
BOOST_ADDLIBS=

# -------------------------------------------------- More Generic Configuration
#
COMPILE=	g++ -c -std=c++0x
LINK=		g++
OPTIMIZE=	-O2
WARN=		-Wall

# ----------------------------------------------------------- Derived Variables
#

# ---------------------------------------------------------------- Suffix Rules
#
.o:
	$(LINK) $< $(BOOST_ADDLIBS) -o $@
.cpp.s:
	$(COMPILE) $(OPTIMIZE) $(WARN) -I../.. $<
.cpp.o:
	$(COMPILE) $(OPTIMIZE) $(WARN) -I../.. $<
.cpp:
	$(COMPILE) $(OPTIMIZE) $(WARN) -I../.. $<
	$(LINK) $(<:.cpp=.o) $(BOOST_ADDLIBS) -o $@

# -------------------------------------------------------- Per Default Run Demo
#
demo_run: demo
	@./demo

# ------------------------------------------------------ Create all Executables
#
all: $(DEMOS)
	@echo "Executables available: $(DEMOS)"
	
# --------------------------------------------------------------------- CLEANUP
#
clean:
	-rm -f *.o $(DEMOS) a.out core
