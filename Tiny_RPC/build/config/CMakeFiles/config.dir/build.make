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
include config/CMakeFiles/config.dir/depend.make

# Include the progress variables for this target.
include config/CMakeFiles/config.dir/progress.make

# Include the compile flags for this target's objects.
include config/CMakeFiles/config.dir/flags.make

config/CMakeFiles/config.dir/Config.cpp.o: config/CMakeFiles/config.dir/flags.make
config/CMakeFiles/config.dir/Config.cpp.o: ../config/Config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/myhome/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object config/CMakeFiles/config.dir/Config.cpp.o"
	cd /home/hy/myhome/Tiny_RPC/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/config.dir/Config.cpp.o -c /home/hy/myhome/Tiny_RPC/config/Config.cpp

config/CMakeFiles/config.dir/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/config.dir/Config.cpp.i"
	cd /home/hy/myhome/Tiny_RPC/build/config && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/myhome/Tiny_RPC/config/Config.cpp > CMakeFiles/config.dir/Config.cpp.i

config/CMakeFiles/config.dir/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/config.dir/Config.cpp.s"
	cd /home/hy/myhome/Tiny_RPC/build/config && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/myhome/Tiny_RPC/config/Config.cpp -o CMakeFiles/config.dir/Config.cpp.s

# Object files for target config
config_OBJECTS = \
"CMakeFiles/config.dir/Config.cpp.o"

# External object files for target config
config_EXTERNAL_OBJECTS =

config/libconfig.a: config/CMakeFiles/config.dir/Config.cpp.o
config/libconfig.a: config/CMakeFiles/config.dir/build.make
config/libconfig.a: config/CMakeFiles/config.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hy/myhome/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libconfig.a"
	cd /home/hy/myhome/Tiny_RPC/build/config && $(CMAKE_COMMAND) -P CMakeFiles/config.dir/cmake_clean_target.cmake
	cd /home/hy/myhome/Tiny_RPC/build/config && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/config.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
config/CMakeFiles/config.dir/build: config/libconfig.a

.PHONY : config/CMakeFiles/config.dir/build

config/CMakeFiles/config.dir/clean:
	cd /home/hy/myhome/Tiny_RPC/build/config && $(CMAKE_COMMAND) -P CMakeFiles/config.dir/cmake_clean.cmake
.PHONY : config/CMakeFiles/config.dir/clean

config/CMakeFiles/config.dir/depend:
	cd /home/hy/myhome/Tiny_RPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hy/myhome/Tiny_RPC /home/hy/myhome/Tiny_RPC/config /home/hy/myhome/Tiny_RPC/build /home/hy/myhome/Tiny_RPC/build/config /home/hy/myhome/Tiny_RPC/build/config/CMakeFiles/config.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : config/CMakeFiles/config.dir/depend

