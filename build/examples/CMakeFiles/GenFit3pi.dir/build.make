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
include examples/CMakeFiles/GenFit3pi.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/GenFit3pi.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/GenFit3pi.dir/flags.make

examples/CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.o: examples/CMakeFiles/GenFit3pi.dir/flags.make
examples/CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.o: ../examples/GenFit3pi.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oryan/laura/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.o"
	cd /home/oryan/laura/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.o -c /home/oryan/laura/examples/GenFit3pi.cc

examples/CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.i"
	cd /home/oryan/laura/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oryan/laura/examples/GenFit3pi.cc > CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.i

examples/CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.s"
	cd /home/oryan/laura/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oryan/laura/examples/GenFit3pi.cc -o CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.s

# Object files for target GenFit3pi
GenFit3pi_OBJECTS = \
"CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.o"

# External object files for target GenFit3pi
GenFit3pi_EXTERNAL_OBJECTS =

examples/GenFit3pi: examples/CMakeFiles/GenFit3pi.dir/GenFit3pi.cc.o
examples/GenFit3pi: examples/CMakeFiles/GenFit3pi.dir/build.make
examples/GenFit3pi: lib/libLaura++.so.3.6.0
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libMinuit.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libEG.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libPhysics.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libGenVector.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libGraf3d.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libGpad.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libGraf.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libHist.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libMatrix.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libTree.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libMathCore.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libImt.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libMultiProc.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libNet.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libRIO.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libThread.so
examples/GenFit3pi: /home/oryan/root-6.30.06-install/lib/libCore.so
examples/GenFit3pi: examples/CMakeFiles/GenFit3pi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oryan/laura/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GenFit3pi"
	cd /home/oryan/laura/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GenFit3pi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/GenFit3pi.dir/build: examples/GenFit3pi

.PHONY : examples/CMakeFiles/GenFit3pi.dir/build

examples/CMakeFiles/GenFit3pi.dir/clean:
	cd /home/oryan/laura/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/GenFit3pi.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/GenFit3pi.dir/clean

examples/CMakeFiles/GenFit3pi.dir/depend:
	cd /home/oryan/laura/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oryan/laura /home/oryan/laura/examples /home/oryan/laura/build /home/oryan/laura/build/examples /home/oryan/laura/build/examples/CMakeFiles/GenFit3pi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/GenFit3pi.dir/depend

