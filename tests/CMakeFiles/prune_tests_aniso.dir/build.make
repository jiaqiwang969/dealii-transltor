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

# Utility rule file for prune_tests_aniso.

# Include the progress variables for this target.
include tests/CMakeFiles/prune_tests_aniso.dir/progress.make

tests/CMakeFiles/prune_tests_aniso:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/workspaces/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Processing tests/aniso"
	cd /workspaces/dealii/tests && /usr/bin/cmake -E remove_directory /workspaces/dealii/tests/aniso
	cd /workspaces/dealii/tests && /usr/bin/cmake -E make_directory /workspaces/dealii/tests/aniso

prune_tests_aniso: tests/CMakeFiles/prune_tests_aniso
prune_tests_aniso: tests/CMakeFiles/prune_tests_aniso.dir/build.make

.PHONY : prune_tests_aniso

# Rule to build all files generated by this target.
tests/CMakeFiles/prune_tests_aniso.dir/build: prune_tests_aniso

.PHONY : tests/CMakeFiles/prune_tests_aniso.dir/build

tests/CMakeFiles/prune_tests_aniso.dir/clean:
	cd /workspaces/dealii/tests && $(CMAKE_COMMAND) -P CMakeFiles/prune_tests_aniso.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/prune_tests_aniso.dir/clean

tests/CMakeFiles/prune_tests_aniso.dir/depend:
	cd /workspaces/dealii && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/dealii /workspaces/dealii/tests /workspaces/dealii /workspaces/dealii/tests /workspaces/dealii/tests/CMakeFiles/prune_tests_aniso.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/prune_tests_aniso.dir/depend

