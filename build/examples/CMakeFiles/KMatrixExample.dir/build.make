# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oryan/laura

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oryan/laura/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/KMatrixExample.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/KMatrixExample.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/KMatrixExample.dir/flags.make

examples/CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.o: examples/CMakeFiles/KMatrixExample.dir/flags.make
examples/CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.o: ../examples/KMatrixExample.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oryan/laura/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.o"
	cd /home/oryan/laura/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.o -c /home/oryan/laura/examples/KMatrixExample.cc

examples/CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.i"
	cd /home/oryan/laura/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oryan/laura/examples/KMatrixExample.cc > CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.i

examples/CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.s"
	cd /home/oryan/laura/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oryan/laura/examples/KMatrixExample.cc -o CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.s

# Object files for target KMatrixExample
KMatrixExample_OBJECTS = \
"CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.o"

# External object files for target KMatrixExample
KMatrixExample_EXTERNAL_OBJECTS =

examples/KMatrixExample: examples/CMakeFiles/KMatrixExample.dir/KMatrixExample.cc.o
examples/KMatrixExample: examples/CMakeFiles/KMatrixExample.dir/build.make
examples/KMatrixExample: lib/libLaura++.so.3.6.0
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libMinuit.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libEG.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libPhysics.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libGenVector.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libGraf3d.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libGpad.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libGraf.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libHist.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libMatrix.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libTree.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libMathCore.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libImt.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libMultiProc.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libNet.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libRIO.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libThread.so
examples/KMatrixExample: /home/oryan/root-6.30.06-install/lib/libCore.so
examples/KMatrixExample: examples/CMakeFiles/KMatrixExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oryan/laura/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable KMatrixExample"
	cd /home/oryan/laura/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KMatrixExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/KMatrixExample.dir/build: examples/KMatrixExample

.PHONY : examples/CMakeFiles/KMatrixExample.dir/build

examples/CMakeFiles/KMatrixExample.dir/clean:
	cd /home/oryan/laura/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/KMatrixExample.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/KMatrixExample.dir/clean

examples/CMakeFiles/KMatrixExample.dir/depend:
	cd /home/oryan/laura/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oryan/laura /home/oryan/laura/examples /home/oryan/laura/build /home/oryan/laura/build/examples /home/oryan/laura/build/examples/CMakeFiles/KMatrixExample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/KMatrixExample.dir/depend

