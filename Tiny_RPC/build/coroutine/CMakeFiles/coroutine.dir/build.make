# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /home/hy/c++/Tiny_RPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hy/c++/Tiny_RPC/build

# Include any dependencies generated for this target.
include coroutine/CMakeFiles/coroutine.dir/depend.make

# Include the progress variables for this target.
include coroutine/CMakeFiles/coroutine.dir/progress.make

# Include the compile flags for this target's objects.
include coroutine/CMakeFiles/coroutine.dir/flags.make

coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o: coroutine/CMakeFiles/coroutine.dir/flags.make
coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o: ../coroutine/coroutine_hook.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/c++/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coroutine.dir/coroutine_hook.cpp.o -c /home/hy/c++/Tiny_RPC/coroutine/coroutine_hook.cpp

coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coroutine.dir/coroutine_hook.cpp.i"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/c++/Tiny_RPC/coroutine/coroutine_hook.cpp > CMakeFiles/coroutine.dir/coroutine_hook.cpp.i

coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coroutine.dir/coroutine_hook.cpp.s"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/c++/Tiny_RPC/coroutine/coroutine_hook.cpp -o CMakeFiles/coroutine.dir/coroutine_hook.cpp.s

coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.requires:

.PHONY : coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.requires

coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.provides: coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.requires
	$(MAKE) -f coroutine/CMakeFiles/coroutine.dir/build.make coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.provides.build
.PHONY : coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.provides

coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.provides.build: coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o


coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o: coroutine/CMakeFiles/coroutine.dir/flags.make
coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o: ../coroutine/coroutine_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/c++/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coroutine.dir/coroutine_pool.cpp.o -c /home/hy/c++/Tiny_RPC/coroutine/coroutine_pool.cpp

coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coroutine.dir/coroutine_pool.cpp.i"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/c++/Tiny_RPC/coroutine/coroutine_pool.cpp > CMakeFiles/coroutine.dir/coroutine_pool.cpp.i

coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coroutine.dir/coroutine_pool.cpp.s"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/c++/Tiny_RPC/coroutine/coroutine_pool.cpp -o CMakeFiles/coroutine.dir/coroutine_pool.cpp.s

coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.requires:

.PHONY : coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.requires

coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.provides: coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.requires
	$(MAKE) -f coroutine/CMakeFiles/coroutine.dir/build.make coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.provides.build
.PHONY : coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.provides

coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.provides.build: coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o


coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o: coroutine/CMakeFiles/coroutine.dir/flags.make
coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o: ../coroutine/coroutine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/c++/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coroutine.dir/coroutine.cpp.o -c /home/hy/c++/Tiny_RPC/coroutine/coroutine.cpp

coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coroutine.dir/coroutine.cpp.i"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/c++/Tiny_RPC/coroutine/coroutine.cpp > CMakeFiles/coroutine.dir/coroutine.cpp.i

coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coroutine.dir/coroutine.cpp.s"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/c++/Tiny_RPC/coroutine/coroutine.cpp -o CMakeFiles/coroutine.dir/coroutine.cpp.s

coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.requires:

.PHONY : coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.requires

coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.provides: coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.requires
	$(MAKE) -f coroutine/CMakeFiles/coroutine.dir/build.make coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.provides.build
.PHONY : coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.provides

coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.provides.build: coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o


coroutine/CMakeFiles/coroutine.dir/memory.cpp.o: coroutine/CMakeFiles/coroutine.dir/flags.make
coroutine/CMakeFiles/coroutine.dir/memory.cpp.o: ../coroutine/memory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/c++/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object coroutine/CMakeFiles/coroutine.dir/memory.cpp.o"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coroutine.dir/memory.cpp.o -c /home/hy/c++/Tiny_RPC/coroutine/memory.cpp

coroutine/CMakeFiles/coroutine.dir/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coroutine.dir/memory.cpp.i"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hy/c++/Tiny_RPC/coroutine/memory.cpp > CMakeFiles/coroutine.dir/memory.cpp.i

coroutine/CMakeFiles/coroutine.dir/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coroutine.dir/memory.cpp.s"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hy/c++/Tiny_RPC/coroutine/memory.cpp -o CMakeFiles/coroutine.dir/memory.cpp.s

coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.requires:

.PHONY : coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.requires

coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.provides: coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.requires
	$(MAKE) -f coroutine/CMakeFiles/coroutine.dir/build.make coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.provides.build
.PHONY : coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.provides

coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.provides.build: coroutine/CMakeFiles/coroutine.dir/memory.cpp.o


coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o: coroutine/CMakeFiles/coroutine.dir/flags.make
coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o: ../coroutine/coctx_swap.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hy/c++/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building ASM object coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && /usr/bin/cc  $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/coroutine.dir/coctx_swap.S.o -c /home/hy/c++/Tiny_RPC/coroutine/coctx_swap.S

coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.requires:

.PHONY : coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.requires

coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.provides: coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.requires
	$(MAKE) -f coroutine/CMakeFiles/coroutine.dir/build.make coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.provides.build
.PHONY : coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.provides

coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.provides.build: coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o


# Object files for target coroutine
coroutine_OBJECTS = \
"CMakeFiles/coroutine.dir/coroutine_hook.cpp.o" \
"CMakeFiles/coroutine.dir/coroutine_pool.cpp.o" \
"CMakeFiles/coroutine.dir/coroutine.cpp.o" \
"CMakeFiles/coroutine.dir/memory.cpp.o" \
"CMakeFiles/coroutine.dir/coctx_swap.S.o"

# External object files for target coroutine
coroutine_EXTERNAL_OBJECTS =

coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o
coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o
coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o
coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/memory.cpp.o
coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o
coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/build.make
coroutine/libcoroutine.a: coroutine/CMakeFiles/coroutine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hy/c++/Tiny_RPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libcoroutine.a"
	cd /home/hy/c++/Tiny_RPC/build/coroutine && $(CMAKE_COMMAND) -P CMakeFiles/coroutine.dir/cmake_clean_target.cmake
	cd /home/hy/c++/Tiny_RPC/build/coroutine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coroutine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
coroutine/CMakeFiles/coroutine.dir/build: coroutine/libcoroutine.a

.PHONY : coroutine/CMakeFiles/coroutine.dir/build

coroutine/CMakeFiles/coroutine.dir/requires: coroutine/CMakeFiles/coroutine.dir/coroutine_hook.cpp.o.requires
coroutine/CMakeFiles/coroutine.dir/requires: coroutine/CMakeFiles/coroutine.dir/coroutine_pool.cpp.o.requires
coroutine/CMakeFiles/coroutine.dir/requires: coroutine/CMakeFiles/coroutine.dir/coroutine.cpp.o.requires
coroutine/CMakeFiles/coroutine.dir/requires: coroutine/CMakeFiles/coroutine.dir/memory.cpp.o.requires
coroutine/CMakeFiles/coroutine.dir/requires: coroutine/CMakeFiles/coroutine.dir/coctx_swap.S.o.requires

.PHONY : coroutine/CMakeFiles/coroutine.dir/requires

coroutine/CMakeFiles/coroutine.dir/clean:
	cd /home/hy/c++/Tiny_RPC/build/coroutine && $(CMAKE_COMMAND) -P CMakeFiles/coroutine.dir/cmake_clean.cmake
.PHONY : coroutine/CMakeFiles/coroutine.dir/clean

coroutine/CMakeFiles/coroutine.dir/depend:
	cd /home/hy/c++/Tiny_RPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hy/c++/Tiny_RPC /home/hy/c++/Tiny_RPC/coroutine /home/hy/c++/Tiny_RPC/build /home/hy/c++/Tiny_RPC/build/coroutine /home/hy/c++/Tiny_RPC/build/coroutine/CMakeFiles/coroutine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : coroutine/CMakeFiles/coroutine.dir/depend
