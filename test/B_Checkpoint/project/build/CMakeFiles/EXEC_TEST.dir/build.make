# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build

# Include any dependencies generated for this target.
include CMakeFiles/EXEC_TEST.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/EXEC_TEST.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/EXEC_TEST.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EXEC_TEST.dir/flags.make

CMakeFiles/EXEC_TEST.dir/Main.cpp.o: CMakeFiles/EXEC_TEST.dir/flags.make
CMakeFiles/EXEC_TEST.dir/Main.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/Main.cpp
CMakeFiles/EXEC_TEST.dir/Main.cpp.o: CMakeFiles/EXEC_TEST.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EXEC_TEST.dir/Main.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/EXEC_TEST.dir/Main.cpp.o -MF CMakeFiles/EXEC_TEST.dir/Main.cpp.o.d -o CMakeFiles/EXEC_TEST.dir/Main.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/Main.cpp

CMakeFiles/EXEC_TEST.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/EXEC_TEST.dir/Main.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/Main.cpp > CMakeFiles/EXEC_TEST.dir/Main.cpp.i

CMakeFiles/EXEC_TEST.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/EXEC_TEST.dir/Main.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/Main.cpp -o CMakeFiles/EXEC_TEST.dir/Main.cpp.s

# Object files for target EXEC_TEST
EXEC_TEST_OBJECTS = \
"CMakeFiles/EXEC_TEST.dir/Main.cpp.o"

# External object files for target EXEC_TEST
EXEC_TEST_EXTERNAL_OBJECTS =

EXEC_TEST: CMakeFiles/EXEC_TEST.dir/Main.cpp.o
EXEC_TEST: CMakeFiles/EXEC_TEST.dir/build.make
EXEC_TEST: liblibGC.a
EXEC_TEST: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/DeLIA_lib/libDeLIA.a
EXEC_TEST: CMakeFiles/EXEC_TEST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EXEC_TEST"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EXEC_TEST.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EXEC_TEST.dir/build: EXEC_TEST
.PHONY : CMakeFiles/EXEC_TEST.dir/build

CMakeFiles/EXEC_TEST.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EXEC_TEST.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EXEC_TEST.dir/clean

CMakeFiles/EXEC_TEST.dir/depend:
	cd /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/test/B_Checkpoint/project/build/CMakeFiles/EXEC_TEST.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/EXEC_TEST.dir/depend

