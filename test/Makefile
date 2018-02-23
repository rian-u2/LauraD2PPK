 ############################################################################
 # Copyright 2017 University of Warwick                                     #
 #                                                                          #
 # Licensed under the Apache License, Version 2.0 (the "License");          #
 # you may not use this file except in compliance with the License.         #
 # You may obtain a copy of the License at                                  #
 #                                                                          #
 #     http://www.apache.org/licenses/LICENSE-2.0                           #
 #                                                                          #
 # Unless required by applicable law or agreed to in writing, software      #
 # distributed under the License is distributed on an "AS IS" BASIS,        #
 # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. #
 # See the License for the specific language governing permissions and      #
 # limitations under the License.                                           #
 #                                                                          #
 # Laura++ package authors:                                                 #
 # John Back                                                                #
 # Paul Harrison                                                            #
 # Thomas Latham                                                            #
 #                                                                          #
 ############################################################################
 #                                                                          #
 # -------------------------------------                                    #
 # Standalone Makefile for Laura++ tests                                    #
 # -------------------------------------                                    #
 #                                                                          #
 # Instructions                                                             #
 #     - Review 'external configuration' section below                      #
 #       to match systems compilers setup                                   #
 #                                                                          #
 #     - Make sure the ROOTSYS environment variable is set and points       #
 #       to your ROOT release or the root-config script is in your PATH     #
 #                                                                          #
 #     - run 'make <target>'                                                #
 #                                                                          #
 # Build targets                                                            #
 #   bin   - make all examples (default)                                    #
 #   <name> - make the specific example                                     #
 #   clean - delete all intermediate and final build objects                #
 #                                                                          #
 ############################################################################


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
