
# --- External configuration ----------------------------------

# first check that ROOTSYS is defined
ifndef ROOTSYS
  ROOTSYS := $(shell root-config --prefix)
  ROOTBINDIR := $(shell root-config --bindir)
  ifeq ($(ROOTSYS), )
    $(error running of root-config failed or reported null value)
  endif 
else
  ROOTBINDIR := $(ROOTSYS)/bin
endif

# If you don't want to build one or more tests, just add them to the SKIPLIST variable
SKIPLIST =

ROOTCONFIG := $(ROOTBINDIR)/root-config
ARCH       := $(shell $(ROOTCONFIG) --arch)
PLATFORM   := $(shell $(ROOTCONFIG) --platform)

INCLUDES = 
WORKDIR  = tmp

ifeq ($(findstring linux, $(ARCH)),linux)
# This set here should work for Linux.
CXX      = g++
LD       = g++
CXXFLAGS = -g -O2 -Wall -Wextra -Wshadow -Woverloaded-virtual -Werror -fPIC
MFLAGS   = -MM
LDFLAGS  = -g
SOFLAGS  = -shared
endif

ifeq ($(ARCH),macosx64)
# For Mac OS X you may need to put -m64 in CXXFLAGS and SOFLAGS.
CXX      = g++
LD       = g++
CXXFLAGS = -g -O3 -Wall -Wextra -Wshadow -Woverloaded-virtual -Werror -fPIC -m64
MFLAGS   = -MM
LDFLAGS  = -g
SOFLAGS  = -m64 -dynamiclib -single_module -undefined dynamic_lookup
endif

# --- Internal configuration ----------------------------------
INCDIR=../inc
DEPDIR=$(WORKDIR)/dependencies
OBJDIR=$(WORKDIR)/objects

ROOTCFLAGS := $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS   := $(shell $(ROOTCONFIG) --libs)
ROOTLIBS   += -lEG
ROOTLIBS   += -lMinuit
ROOTLIBS   += -lTreePlayer
ifeq ($(strip $(SKIPLIST)),)
	ROOTLIBS   += -lRooFitCore
	ROOTLIBS   += -lRooFit
endif
LAURALIBDIR=$(shell pwd | xargs dirname)/lib
LAURALIB = $(LAURALIBDIR)/libLaura++.so

INCLUDES += -I$(INCDIR)
CXXFLAGS += $(INCLUDES)
CXXFLAGS += $(ROOTCFLAGS)

default: bin

# List of all source files
CCLIST:=$(filter-out $(SKIPLIST), $(wildcard *.cc))

# List of all source files that contain main functions
BINCCLIST:=$(shell egrep -l "^[[:space:]]*int[[:space:]]*main\>" $(CCLIST))

# List of all object files to build
BINOLIST:=$(patsubst %.cc,%.o,$(addprefix $(OBJDIR)/,$(notdir $(BINCCLIST))))

# List of all dependency files to make
DLIST:=$(patsubst %.cc,%.d,$(addprefix $(DEPDIR)/,$(notdir $(CCLIST))))

# List of all binary files to make
BINLIST:=$(patsubst %.cc,%,$(notdir $(BINCCLIST)))

# Implicit rule making all dependency Makefiles included at the end of this makefile
$(DEPDIR)/%.d: %.cc
	@echo "Making $@"
	@mkdir -p $(DEPDIR)
	@set -e; $(CXX) $(MFLAGS) $(CXXFLAGS) $< \
	          | sed 's#\($(notdir $*)\)\.o[ :]*#$(OBJDIR)/\1.o $@ : #g' > $@; \
	        [ -s $@ ] || rm -f $@

# Implicit rule to compile all sources
$(OBJDIR)/%.o : %.cc
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile all binaries
% : $(OBJDIR)/%.o $(LAURALIB)
	@echo "Linking $@"
	@$(CXX) $(LDFLAGS) $< -o $@ $(LAURALIB) $(ROOTLIBS)

bin: $(BINLIST)

clean:
	rm -f $(BINLIST)
	rm -rf $(WORKDIR)

.PHONY : bin default clean

-include $(DLIST)
