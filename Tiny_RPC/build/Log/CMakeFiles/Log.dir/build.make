# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hy/myhome/Tiny_RPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hy/myhome/Tiny_RPC/build

# Include any dependencies generated for this target.
include Log/CMakeFiles/Log.dir/depend.make

# Include the progress variables for this target.
include Log/CMakeFiles/Log.dir/progress.make

# Include the compile flags for this target's objects.
include Log/CMakeFiles/Log.dir/flags.make

Log/CMakeFiles/Log.dir/Log.cpp.o: Log/CMakeFiles/Log.dir/flags.make
Log/CMakeFiles/Log.dir/Log.cpp.o: ../Log/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/myhome/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Log/CMakeFiles/Log.dir/Log.cpp.o"
	cd /home/hy/myhome/Tiny_RPC/build/Log && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Log.dir/Log.cpp.o -c /home/hy/myhome/Tiny_RPC/Log/Log.cpp

Log/CMakeFiles/Log.dir/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Log.dir/Log.cpp.i"
	cd /home/hy/myhome/Tiny_RPC/build/Log && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/myhome/Tiny_RPC/Log/Log.cpp > CMakeFiles/Log.dir/Log.cpp.i

Log/CMakeFiles/Log.dir/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Log.dir/Log.cpp.s"
	cd /home/hy/myhome/Tiny_RPC/build/Log && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/myhome/Tiny_RPC/Log/Log.cpp -o CMakeFiles/Log.dir/Log.cpp.s

# Object files for target Log
Log_OBJECTS = \
"CMakeFiles/Log.dir/Log.cpp.o"

# External object files for target Log
Log_EXTERNAL_OBJECTS =

Log/libLog.a: Log/CMakeFiles/Log.dir/Log.cpp.o
Log/libLog.a: Log/CMakeFiles/Log.dir/build.make
Log/libLog.a: Log/CMakeFiles/Log.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hy/myhome/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libLog.a"
	cd /home/hy/myhome/Tiny_RPC/build/Log && $(CMAKE_COMMAND) -P CMakeFiles/Log.dir/cmake_clean_target.cmake
	cd /home/hy/myhome/Tiny_RPC/build/Log && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Log.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Log/CMakeFiles/Log.dir/build: Log/libLog.a

.PHONY : Log/CMakeFiles/Log.dir/build

Log/CMakeFiles/Log.dir/clean:
	cd /home/hy/myhome/Tiny_RPC/build/Log && $(CMAKE_COMMAND) -P CMakeFiles/Log.dir/cmake_clean.cmake
.PHONY : Log/CMakeFiles/Log.dir/clean

Log/CMakeFiles/Log.dir/depend:
	cd /home/hy/myhome/Tiny_RPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hy/myhome/Tiny_RPC /home/hy/myhome/Tiny_RPC/Log /home/hy/myhome/Tiny_RPC/build /home/hy/myhome/Tiny_RPC/build/Log /home/hy/myhome/Tiny_RPC/build/Log/CMakeFiles/Log.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Log/CMakeFiles/Log.dir/depend

