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
CMAKE_SOURCE_DIR = /workspaces/dealii

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/dealii

# Include any dependencies generated for this target.
include cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/depend.make

# Include the progress variables for this target.
include cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/progress.make

# Include the compile flags for this target's objects.
include cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/flags.make

cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.o: cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/flags.make
cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.o: cmake/scripts/expand_instantiations.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.o"
	cd /workspaces/dealii/cmake/scripts && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.o -c /workspaces/dealii/cmake/scripts/expand_instantiations.cc

cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.i"
	cd /workspaces/dealii/cmake/scripts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/dealii/cmake/scripts/expand_instantiations.cc > CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.i

cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.s"
	cd /workspaces/dealii/cmake/scripts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/dealii/cmake/scripts/expand_instantiations.cc -o CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.s

# Object files for target expand_instantiations_exe
expand_instantiations_exe_OBJECTS = \
"CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.o"

# External object files for target expand_instantiations_exe
expand_instantiations_exe_EXTERNAL_OBJECTS =

bin/expand_instantiations: cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/expand_instantiations.cc.o
bin/expand_instantiations: cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/build.make
bin/expand_instantiations: cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/expand_instantiations"
	cd /workspaces/dealii/cmake/scripts && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/expand_instantiations_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/build: bin/expand_instantiations

.PHONY : cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/build

cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/clean:
	cd /workspaces/dealii/cmake/scripts && $(CMAKE_COMMAND) -P CMakeFiles/expand_instantiations_exe.dir/cmake_clean.cmake
.PHONY : cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/clean

cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/depend:
	cd /workspaces/dealii && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/dealii /workspaces/dealii/cmake/scripts /workspaces/dealii /workspaces/dealii/cmake/scripts /workspaces/dealii/cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cmake/scripts/CMakeFiles/expand_instantiations_exe.dir/depend

