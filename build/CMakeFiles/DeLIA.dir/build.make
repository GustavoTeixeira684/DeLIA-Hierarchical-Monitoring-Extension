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
CMAKE_SOURCE_DIR = /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build

# Include any dependencies generated for this target.
include CMakeFiles/DeLIA.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DeLIA.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DeLIA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DeLIA.dir/flags.make

CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o: CMakeFiles/DeLIA.dir/flags.make
CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/libs/jsoncpp/jsoncpp.cpp
CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o: CMakeFiles/DeLIA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o -MF CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o.d -o CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/libs/jsoncpp/jsoncpp.cpp

CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/libs/jsoncpp/jsoncpp.cpp > CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.i

CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/libs/jsoncpp/jsoncpp.cpp -o CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.s

CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o: CMakeFiles/DeLIA.dir/flags.make
CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/ApplicationSettings.cpp
CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o: CMakeFiles/DeLIA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o -MF CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o.d -o CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/ApplicationSettings.cpp

CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/ApplicationSettings.cpp > CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.i

CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/ApplicationSettings.cpp -o CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.s

CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o: CMakeFiles/DeLIA.dir/flags.make
CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Checkpointing.cpp
CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o: CMakeFiles/DeLIA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o -MF CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o.d -o CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Checkpointing.cpp

CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Checkpointing.cpp > CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.i

CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Checkpointing.cpp -o CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.s

CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o: CMakeFiles/DeLIA.dir/flags.make
CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/DeLIA.cpp
CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o: CMakeFiles/DeLIA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o -MF CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o.d -o CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/DeLIA.cpp

CMakeFiles/DeLIA.dir/src/DeLIA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DeLIA.dir/src/DeLIA.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/DeLIA.cpp > CMakeFiles/DeLIA.dir/src/DeLIA.cpp.i

CMakeFiles/DeLIA.dir/src/DeLIA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DeLIA.dir/src/DeLIA.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/DeLIA.cpp -o CMakeFiles/DeLIA.dir/src/DeLIA.cpp.s

CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o: CMakeFiles/DeLIA.dir/flags.make
CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/FaultDetection.cpp
CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o: CMakeFiles/DeLIA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o -MF CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o.d -o CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/FaultDetection.cpp

CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/FaultDetection.cpp > CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.i

CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/FaultDetection.cpp -o CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.s

CMakeFiles/DeLIA.dir/src/Utils.cpp.o: CMakeFiles/DeLIA.dir/flags.make
CMakeFiles/DeLIA.dir/src/Utils.cpp.o: /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Utils.cpp
CMakeFiles/DeLIA.dir/src/Utils.cpp.o: CMakeFiles/DeLIA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/DeLIA.dir/src/Utils.cpp.o"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DeLIA.dir/src/Utils.cpp.o -MF CMakeFiles/DeLIA.dir/src/Utils.cpp.o.d -o CMakeFiles/DeLIA.dir/src/Utils.cpp.o -c /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Utils.cpp

CMakeFiles/DeLIA.dir/src/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DeLIA.dir/src/Utils.cpp.i"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Utils.cpp > CMakeFiles/DeLIA.dir/src/Utils.cpp.i

CMakeFiles/DeLIA.dir/src/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DeLIA.dir/src/Utils.cpp.s"
	/usr/bin/mpic++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/src/Utils.cpp -o CMakeFiles/DeLIA.dir/src/Utils.cpp.s

# Object files for target DeLIA
DeLIA_OBJECTS = \
"CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o" \
"CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o" \
"CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o" \
"CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o" \
"CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o" \
"CMakeFiles/DeLIA.dir/src/Utils.cpp.o"

# External object files for target DeLIA
DeLIA_EXTERNAL_OBJECTS =

libDeLIA.a: CMakeFiles/DeLIA.dir/libs/jsoncpp/jsoncpp.cpp.o
libDeLIA.a: CMakeFiles/DeLIA.dir/src/ApplicationSettings.cpp.o
libDeLIA.a: CMakeFiles/DeLIA.dir/src/Checkpointing.cpp.o
libDeLIA.a: CMakeFiles/DeLIA.dir/src/DeLIA.cpp.o
libDeLIA.a: CMakeFiles/DeLIA.dir/src/FaultDetection.cpp.o
libDeLIA.a: CMakeFiles/DeLIA.dir/src/Utils.cpp.o
libDeLIA.a: CMakeFiles/DeLIA.dir/build.make
libDeLIA.a: CMakeFiles/DeLIA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libDeLIA.a"
	$(CMAKE_COMMAND) -P CMakeFiles/DeLIA.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DeLIA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DeLIA.dir/build: libDeLIA.a
.PHONY : CMakeFiles/DeLIA.dir/build

CMakeFiles/DeLIA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DeLIA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DeLIA.dir/clean

CMakeFiles/DeLIA.dir/depend:
	cd /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build /home/gustavo/repo/DeLIA-Hierarchical-Monitoring-Extension/build/CMakeFiles/DeLIA.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DeLIA.dir/depend

