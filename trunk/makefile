
# PDELAB MAKEFILE ###################################

# Source files
SRC := 	solver.cpp \
	instruction.cpp \
	terminal.cpp \
	sentence.cpp \
	eventhandler.cpp \
	System_Manager.cpp

#header files
HD = 	$(SRC:.cpp=.h) \
	stringqueue.h \
	System_Manager.h

# Object files
OBJ = 	$(SRC:.cpp=.o)

# The final product - the binary files
PROG =  $(BINDIR)/pdelab

# Important directories
ROOTDIR   = $(CURDIR)
EXDIR = $(ROOTDIR)/examples
1DDIR  = $(EXDIR)/1D
2DDIR = $(EXDIR)/2D
BINDIR    = $(ROOTDIR)/bin
SRCDIR = $(ROOTDIR)/src
GP = $(ROOTDIR)/gp
DAT = $(ROOTDIR)/dat
PDE = $(ROOTDIR)/pde

# GCC Flags, Compilers, and Linkers
CPPFLAGS = -c -Wall -Wextra -O3 #-D NDEBUG #-pg
LDFLAGS = -O3 #-pg
LIB = -lm  -L$(EXDIR) -lEX
INC = -I$(1DDIR) -I$(2DDIR) -I$(EXDIR) -I$(SRCDIR) 
LD = /usr/bin/g++
C++ = /usr/bin/g++


# Libraries
LIBRARIES =  $(EXDIR)/libEX.a

all: makelib $(PROG)

makelib:
	@echo
	@echo -- Making EXlib.a --
	cd $(EXDIR); $(MAKE) shared
	@echo
	@echo -- Finished making libraries -- 
	@echo

$(BINDIR)/pdelab : $(OBJ) $(LIBRARIES)
	@echo
	@echo -- Linking $(notdir $@) --
	$(LD) -o $@ $(LIBDIR) $^ $(LIB)
	chmod a+x $@
	@echo
	@echo --- Finished making $(notdir $@) ---
	@echo
$(OBJ) : %.o : $(SRCDIR)/%.cpp
	@echo 
	@echo --- Compiling $(notdir $<) ---
	$(C++) $(CPPFLAGS) -o $@ $< $(INC)

clean:
	@echo 
	@echo --- Cleaning ---
	rm -rf $(BINDIR)/*
	rm -rf *.o
	@echo 

cleanlib:
	@echo --- Cleaning libraries ---
	cd $(EXDIR); $(MAKE) clean; $(MAKE) cleandepend
	@echo

cleangp:
	@echo --- Cleaning $(GP) ---
	rm -rf $(GP)/*.gp
	@echo

cleanpde:
	@echo --- Cleaning $(PDE) ---
	rm -rf $(PDE)/*.pde
	@echo

cleandat:
	@echo --- Cleaning $(DAT) ---
	rm -rf $(DAT)/*
	@echo

cleandepend:
	rm -rf depend

spotless:
	make clean
	make cleanlib
	make cleandat
	make cleanpde
	make cleangp
	make cleandepend
	
depend : $(addprefix $(SRCDIR)/, $(SRC))
	 $(C++) $(CPPFLAGS) $(INC) -M $^ > $@
include depend
include helpfile
