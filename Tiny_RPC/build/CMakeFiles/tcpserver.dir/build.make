# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hy/TinyRPC/Tiny_RPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hy/TinyRPC/Tiny_RPC/build

# Include any dependencies generated for this target.
include CMakeFiles/tcpserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcpserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcpserver.dir/flags.make

CMakeFiles/tcpserver.dir/test/test_reactor.cpp.o: CMakeFiles/tcpserver.dir/flags.make
CMakeFiles/tcpserver.dir/test/test_reactor.cpp.o: ../test/test_reactor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/TinyRPC/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcpserver.dir/test/test_reactor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcpserver.dir/test/test_reactor.cpp.o -c /home/hy/TinyRPC/Tiny_RPC/test/test_reactor.cpp

CMakeFiles/tcpserver.dir/test/test_reactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpserver.dir/test/test_reactor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/TinyRPC/Tiny_RPC/test/test_reactor.cpp > CMakeFiles/tcpserver.dir/test/test_reactor.cpp.i

CMakeFiles/tcpserver.dir/test/test_reactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpserver.dir/test/test_reactor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/TinyRPC/Tiny_RPC/test/test_reactor.cpp -o CMakeFiles/tcpserver.dir/test/test_reactor.cpp.s

# Object files for target tcpserver
tcpserver_OBJECTS = \
"CMakeFiles/tcpserver.dir/test/test_reactor.cpp.o"

# External object files for target tcpserver
tcpserver_EXTERNAL_OBJECTS =

tcpserver: CMakeFiles/tcpserver.dir/test/test_reactor.cpp.o
tcpserver: CMakeFiles/tcpserver.dir/build.make
tcpserver: config/libconfig.a
tcpserver: net/libnet.a
tcpserver: coroutine/libcoroutine.a
tcpserver: Log/libLog.a
tcpserver: LOCK/libLOCK.a
tcpserver: hook/libhook.a
tcpserver: net/libnet.a
tcpserver: coroutine/libcoroutine.a
tcpserver: Log/libLog.a
tcpserver: LOCK/libLOCK.a
tcpserver: CMakeFiles/tcpserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hy/TinyRPC/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tcpserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcpserver.dir/build: tcpserver

.PHONY : CMakeFiles/tcpserver.dir/build

CMakeFiles/tcpserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcpserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcpserver.dir/clean

CMakeFiles/tcpserver.dir/depend:
	cd /home/hy/TinyRPC/Tiny_RPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hy/TinyRPC/Tiny_RPC /home/hy/TinyRPC/Tiny_RPC /home/hy/TinyRPC/Tiny_RPC/build /home/hy/TinyRPC/Tiny_RPC/build /home/hy/TinyRPC/Tiny_RPC/build/CMakeFiles/tcpserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcpserver.dir/depend

