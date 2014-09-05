# =============================================================================
# Makefile for Boost-Workshop Examples
# =============================================================================
# This is the master Makefile to be included from Makefiles in subdirectories.
# Hence only the generic stuff goes here. Especially note that if there is a
# need for linking to libraries supplied with Boost, these have to be specified
# as value of BOOST_ADDLIBS in the individual Makefiles. The make variables
# BOOST_LIB_DIR (or BOOST_VERSION) and BOOST_BUILD may be used as part of the
# individual library specifications, so that future adaptions can (hopefully)
# be done centralized.
#
# NOTE:
# It is expected that a make process using a Makefile from a subdirectory is
# executed with this subdirectory as working directory, so the names of files
# and directories have to be specified from "one level below" the directory in
# which this master Makefile is located.

# ----------------------------------------------------- Set Boost Configuration
#
BOOST_VERSION=		1_49_0
BOOST_INC_DIR=		/usr/include
BOOST_LIB_DIR=		/home/mb/mb_old/Boost/boost_1_49_0/stage/lib/

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
	$(LINK) $< -L$(BOOST_LIB_DIR) $(BOOST_ADDLIBS) -o $@
.cpp.s:
	$(COMPILE) $(OPTIMIZE) $(WARN) -I../.. -I$(BOOST_INC_DIR) -S $<
.cpp.o:
	$(COMPILE) $(OPTIMIZE) $(WARN) -I../.. -I$(BOOST_INC_DIR) $<
.cpp:
	$(COMPILE) $(OPTIMIZE) $(WARN) -I../.. -I$(BOOST_INC_DIR) $<
	$(LINK) -L$(BOOST_LIB_DIR) $(BOOST_ADDLIBS) $(<:.cpp=.o) -o $@

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
