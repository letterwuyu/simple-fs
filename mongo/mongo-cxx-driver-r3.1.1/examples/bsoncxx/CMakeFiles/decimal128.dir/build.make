# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx

# Include any dependencies generated for this target.
include CMakeFiles/decimal128.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/decimal128.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/decimal128.dir/flags.make

CMakeFiles/decimal128.dir/decimal128.o: CMakeFiles/decimal128.dir/flags.make
CMakeFiles/decimal128.dir/decimal128.o: decimal128.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/decimal128.dir/decimal128.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/decimal128.dir/decimal128.o -c /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/decimal128.cpp

CMakeFiles/decimal128.dir/decimal128.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/decimal128.dir/decimal128.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/decimal128.cpp > CMakeFiles/decimal128.dir/decimal128.i

CMakeFiles/decimal128.dir/decimal128.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/decimal128.dir/decimal128.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/decimal128.cpp -o CMakeFiles/decimal128.dir/decimal128.s

CMakeFiles/decimal128.dir/decimal128.o.requires:
.PHONY : CMakeFiles/decimal128.dir/decimal128.o.requires

CMakeFiles/decimal128.dir/decimal128.o.provides: CMakeFiles/decimal128.dir/decimal128.o.requires
	$(MAKE) -f CMakeFiles/decimal128.dir/build.make CMakeFiles/decimal128.dir/decimal128.o.provides.build
.PHONY : CMakeFiles/decimal128.dir/decimal128.o.provides

CMakeFiles/decimal128.dir/decimal128.o.provides.build: CMakeFiles/decimal128.dir/decimal128.o

# Object files for target decimal128
decimal128_OBJECTS = \
"CMakeFiles/decimal128.dir/decimal128.o"

# External object files for target decimal128
decimal128_EXTERNAL_OBJECTS =

decimal128: CMakeFiles/decimal128.dir/decimal128.o
decimal128: CMakeFiles/decimal128.dir/build.make
decimal128: CMakeFiles/decimal128.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable decimal128"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/decimal128.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/decimal128.dir/build: decimal128
.PHONY : CMakeFiles/decimal128.dir/build

CMakeFiles/decimal128.dir/requires: CMakeFiles/decimal128.dir/decimal128.o.requires
.PHONY : CMakeFiles/decimal128.dir/requires

CMakeFiles/decimal128.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/decimal128.dir/cmake_clean.cmake
.PHONY : CMakeFiles/decimal128.dir/clean

CMakeFiles/decimal128.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/CMakeFiles/decimal128.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/decimal128.dir/depend

