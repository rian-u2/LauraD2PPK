 ########################################################################## 
 # Copyright University of Warwick 2004 - 2013.                           #
 # Distributed under the Boost Software License, Version 1.0.             #
 # (See accompanying file LICENSE_1_0.txt or copy at                      #
 # http://www.boost.org/LICENSE_1_0.txt)                                  #
 #                                                                        #
 # Authors:                                                               #
 # Thomas Latham                                                          #
 # John Back                                                              #
 # Paul Harrison                                                          #
 #                                                                        #
 # -------------------------------                                        #
 # Standalone Makefile for Laura++                                        #
 # -------------------------------                                        #
 #                                                                        #
 # Instructions                                                           #
 #     - Review 'external configuration' section below                    #
 #       to match systems compilers setup                                 #
 #                                                                        #
 #     - Make sure the ROOTSYS environment variable is set and points     #
 #       to your ROOT release or the root-config script is in your PATH   #
 #                                                                        #
 #     - run 'make <target>'                                              #
 #                                                                        #
 # Build targets                                                          #
 #   lib   - make libLaura++.a                                            #
 #   shlib - make libLaura++.so (default)                                 #
 #   clean - delete all intermediate and final build objects              #
 #                                                                        #
 ########################################################################## 


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

ROOTCONFIG := $(ROOTBINDIR)/root-config
ARCH       := $(shell $(ROOTCONFIG) --arch)
PLATFORM   := $(shell $(ROOTCONFIG) --platform)

INCLUDES = 
SRCDIR   = src
INCDIR   = inc
LIBDIR   = lib
WORKDIR  = tmp

ifeq ($(findstring linux, $(ARCH)),linux)
# This set here should work for Linux.
CXX      = g++
LD       = g++
CXXFLAGS = -g -O2 -Wall -Wextra -Wshadow -Woverloaded-virtual -Werror -fPIC
MFLAGS   = -MM
SOFLAGS  = -shared
endif

ifeq ($(ARCH),macosx64)
# For Mac OS X you may need to put -m64 in CXXFLAGS and SOFLAGS.
CXX      = g++
LD       = g++
CXXFLAGS = -g -O3 -Wall -Wextra -Wshadow -Woverloaded-virtual -Werror -fPIC -m64
MFLAGS   = -MM
SOFLAGS  = -m64 -dynamiclib -single_module -undefined dynamic_lookup
endif

# --- Internal configuration ----------------------------------
PACKAGE=Laura++
DEPDIR=$(WORKDIR)/dependencies
OBJDIR=$(WORKDIR)/objects

INCLUDES += -I$(INCDIR) -I$(shell $(ROOTBINDIR)/root-config --incdir)
CXXFLAGS += $(INCLUDES)
SKIPLIST  = test.cc
CINTFILE  = $(WORKDIR)/$(PACKAGE)Cint.cc
CINTOBJ   = $(OBJDIR)/$(PACKAGE)Cint.o
LIBFILE   = $(LIBDIR)/lib$(PACKAGE).a
SHLIBFILE = $(LIBDIR)/lib$(PACKAGE).so
ROOTMAPFILE := $(patsubst %.so,%.rootmap,$(SHLIBFILE))

default: shlib

# List of all header files
HHLIST:=$(wildcard $(INCDIR)/*.hh)

# List of all source files to build
CCLIST:=$(filter-out $(SKIPLIST),$(wildcard $(SRCDIR)/*.cc))

# List of all object files to build
OLIST:=$(patsubst %.cc,%.o,$(addprefix $(OBJDIR)/,$(notdir $(CCLIST))))

# List of all dependency files to make
DLIST:=$(patsubst %.cc,%.d,$(addprefix $(DEPDIR)/,$(notdir $(CCLIST))))

# Implicit rule making all dependency Makefiles included at the end of this makefile
$(DEPDIR)/%.d: $(SRCDIR)/%.cc
	@echo "Making $@"
	@mkdir -p $(DEPDIR)
	@set -e; $(CXX) $(MFLAGS) $(CXXFLAGS) $< \
	          | sed 's#\($(notdir $*)\)\.o[ :]*#$(OBJDIR)/\1.o $@ : #g' > $@; \
	        [ -s $@ ] || rm -f $@

# Implicit rule to compile all classes
$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to make ROOTCINT output file
$(CINTOBJ): $(HHLIST) $(INCDIR)/$(PACKAGE)_LinkDef.h
	@mkdir -p $(OBJDIR)
	@echo "Running rootcint"
	@$(ROOTBINDIR)/rootcint -f $(CINTFILE) -c $(INCLUDES) $(notdir $(HHLIST)) $(INCDIR)/$(PACKAGE)_LinkDef.h
	@echo "Compiling $(CINTFILE)"
	@$(CXX) $(CXXFLAGS) -c $(CINTFILE) -o $(CINTOBJ)

# Rule to combine objects into a library
$(LIBFILE): $(OLIST) $(CINTOBJ)
	@echo "Making $(LIBFILE)"
	@mkdir -p $(LIBDIR)
	@rm -f $(LIBFILE)
	@ar rcs $(LIBFILE) $(OLIST) $(CINTOBJ) 

# Rule to combine objects into a shared library
$(SHLIBFILE): $(OLIST) $(CINTOBJ)
	@echo "Making $(SHLIBFILE)"
	@mkdir -p $(LIBDIR)
	@rm -f $(SHLIBFILE)
	@$(CXX) $(OLIST) $(CINTOBJ) $(SOFLAGS) -o $(SHLIBFILE)
	@rlibmap -f -o $(ROOTMAPFILE) -l $(SHLIBFILE) -d libMatrix libHist libTree -c $(INCDIR)/$(PACKAGE)_LinkDef.h

# Useful build targets
lib: $(LIBFILE) 
shlib: $(SHLIBFILE)
clean:
	rm -rf $(WORKDIR)
	rm -f $(LIBFILE)
	rm -f $(SHLIBFILE)
	rm -f $(ROOTMAPFILE)

.PHONY : shlib lib default clean

-include $(DLIST)
