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
include source/non_matching/CMakeFiles/obj_non_matching_debug.dir/depend.make

# Include the progress variables for this target.
include source/non_matching/CMakeFiles/obj_non_matching_debug.dir/progress.make

# Include the compile flags for this target's objects.
include source/non_matching/CMakeFiles/obj_non_matching_debug.dir/flags.make

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/coupling.cc.o: source/non_matching/CMakeFiles/obj_non_matching_debug.dir/flags.make
source/non_matching/CMakeFiles/obj_non_matching_debug.dir/coupling.cc.o: source/non_matching/coupling.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/non_matching/CMakeFiles/obj_non_matching_debug.dir/coupling.cc.o"
	cd /workspaces/dealii/source/non_matching && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/obj_non_matching_debug.dir/coupling.cc.o -c /workspaces/dealii/source/non_matching/coupling.cc

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/coupling.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obj_non_matching_debug.dir/coupling.cc.i"
	cd /workspaces/dealii/source/non_matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/dealii/source/non_matching/coupling.cc > CMakeFiles/obj_non_matching_debug.dir/coupling.cc.i

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/coupling.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obj_non_matching_debug.dir/coupling.cc.s"
	cd /workspaces/dealii/source/non_matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/dealii/source/non_matching/coupling.cc -o CMakeFiles/obj_non_matching_debug.dir/coupling.cc.s

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.o: source/non_matching/CMakeFiles/obj_non_matching_debug.dir/flags.make
source/non_matching/CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.o: source/non_matching/immersed_surface_quadrature.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object source/non_matching/CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.o"
	cd /workspaces/dealii/source/non_matching && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.o -c /workspaces/dealii/source/non_matching/immersed_surface_quadrature.cc

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.i"
	cd /workspaces/dealii/source/non_matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/dealii/source/non_matching/immersed_surface_quadrature.cc > CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.i

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.s"
	cd /workspaces/dealii/source/non_matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/dealii/source/non_matching/immersed_surface_quadrature.cc -o CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.s

obj_non_matching_debug: source/non_matching/CMakeFiles/obj_non_matching_debug.dir/coupling.cc.o
obj_non_matching_debug: source/non_matching/CMakeFiles/obj_non_matching_debug.dir/immersed_surface_quadrature.cc.o
obj_non_matching_debug: source/non_matching/CMakeFiles/obj_non_matching_debug.dir/build.make

.PHONY : obj_non_matching_debug

# Rule to build all files generated by this target.
source/non_matching/CMakeFiles/obj_non_matching_debug.dir/build: obj_non_matching_debug

.PHONY : source/non_matching/CMakeFiles/obj_non_matching_debug.dir/build

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/clean:
	cd /workspaces/dealii/source/non_matching && $(CMAKE_COMMAND) -P CMakeFiles/obj_non_matching_debug.dir/cmake_clean.cmake
.PHONY : source/non_matching/CMakeFiles/obj_non_matching_debug.dir/clean

source/non_matching/CMakeFiles/obj_non_matching_debug.dir/depend:
	cd /workspaces/dealii && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/dealii /workspaces/dealii/source/non_matching /workspaces/dealii /workspaces/dealii/source/non_matching /workspaces/dealii/source/non_matching/CMakeFiles/obj_non_matching_debug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/non_matching/CMakeFiles/obj_non_matching_debug.dir/depend

