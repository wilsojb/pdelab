
# examples makefile

# Source files 
SRC  := example.cpp
1D := advec.cpp
2D := 

#header files
HEADER = $(SRC:.cpp=.h) $(1D:.cpp=.h) $(2D:.cpp=.h)



# Object files
OBJ_SRC = $(SRC:.cpp=.o)
OBJ_1D = $(1D:.cpp=.o)
OBJ_2D = $(2D:.cpp=.o)
OBJ = $(OBJ_SRC) $(OBJ_1D) $(OBJ_2D)

# Important directories
ROOTDIR = $(CURDIR)
1DDIR = $(ROOTDIR)/1D
2DDIR = $(ROOTDIR)/2D
LAINC = $(LADIR)/include


# GCC Flags
CPPFLAGS = -c -Wall -Wextra -O3 #-D NDEBUG #-pg
LDFLAGS = -O3 #-pg
INC = -I$(LAINC) -I$(1DDIR) -I$(2DDIR) -I$(ROOTDIR)
C++ = /usr/bin/g++
LD = /usr/bin/g++

# INTEL Flags
#CPPFLAGS = -c -O3 #-D NDEBUG #-pg
#LDFLAGS = -O3 #-pg
#INC = -I$(LAINC) -I$(1DDIR) -I$(2DDIR) -I$(ROOTDIR) 
#C++ = /usr/local/intel/Compiler/11.1/072/bin/ia32/icpc
#LD = /usr/local/intel/Compiler/11.1/072/bin/ia32/icpc

shared: libEX.a

libEX.a: $(OBJ)
	@echo
	@echo --- Creating static library $@ ---
	rm -rf libEX.a
	ar cr $@ $(OBJ)
	ranlib $@
	@echo
	@echo --- Finished making static library $@ ---
	@echo

$(OBJ_SRC) : %.o : %.cpp
	@echo
	@echo --- Compiling $< ---
	$(C++) $(CPPFLAGS) -o $@ $< $(INC)

$(OBJ_2D) : %.o : $(2DDIR)/%.cpp
	@echo
	@echo --- Compiling $< ---
	$(C++) $(CPPFLAGS) -o $@ $< $(INC)

$(OBJ_1D) : %.o : $(1DDIR)/%.cpp
	@echo
	@echo --- Compiling $< ---
	$(C++) $(CPPFLAGS) -o $@ $< $(INC)

clean:
	rm -rf *.o
	rm -rf *.a

cleandepend:
	rm -rf depend


depend : $(SRC) \
	$(addprefix $(1DDIR)/, $(1D)) \
	$(addprefix $(2DDIR)/, $(2D))
	$(C++) $(CPPFLAGS) -M $^ > $@ $(INC)
include depend
