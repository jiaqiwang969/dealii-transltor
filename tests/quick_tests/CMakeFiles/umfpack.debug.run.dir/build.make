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

# Utility rule file for umfpack.debug.run.

# Include the progress variables for this target.
include tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/progress.make

tests/quick_tests/CMakeFiles/umfpack.debug.run: tests/quick_tests/umfpack.debug
	cd /workspaces/dealii/tests/quick_tests && /workspaces/dealii/tests/quick_tests/umfpack.debug > umfpack.debug-OK 2>&1 || ( echo umfpack.debug:\ RUN\ failed.\ Output: && cat umfpack.debug-OK && rm umfpack.debug-OK && exit 1 )
	cd /workspaces/dealii/tests/quick_tests && echo umfpack.debug:\ PASSED.

umfpack.debug.run: tests/quick_tests/CMakeFiles/umfpack.debug.run
umfpack.debug.run: tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/build.make

.PHONY : umfpack.debug.run

# Rule to build all files generated by this target.
tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/build: umfpack.debug.run

.PHONY : tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/build

tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/clean:
	cd /workspaces/dealii/tests/quick_tests && $(CMAKE_COMMAND) -P CMakeFiles/umfpack.debug.run.dir/cmake_clean.cmake
.PHONY : tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/clean

tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/depend:
	cd /workspaces/dealii && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/dealii /workspaces/dealii/tests/quick_tests /workspaces/dealii /workspaces/dealii/tests/quick_tests /workspaces/dealii/tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/quick_tests/CMakeFiles/umfpack.debug.run.dir/depend

