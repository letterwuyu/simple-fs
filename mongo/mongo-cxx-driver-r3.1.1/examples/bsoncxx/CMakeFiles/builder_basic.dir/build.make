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
include CMakeFiles/builder_basic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/builder_basic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/builder_basic.dir/flags.make

CMakeFiles/builder_basic.dir/builder_basic.o: CMakeFiles/builder_basic.dir/flags.make
CMakeFiles/builder_basic.dir/builder_basic.o: builder_basic.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/builder_basic.dir/builder_basic.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/builder_basic.dir/builder_basic.o -c /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/builder_basic.cpp

CMakeFiles/builder_basic.dir/builder_basic.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/builder_basic.dir/builder_basic.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/builder_basic.cpp > CMakeFiles/builder_basic.dir/builder_basic.i

CMakeFiles/builder_basic.dir/builder_basic.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/builder_basic.dir/builder_basic.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/builder_basic.cpp -o CMakeFiles/builder_basic.dir/builder_basic.s

CMakeFiles/builder_basic.dir/builder_basic.o.requires:
.PHONY : CMakeFiles/builder_basic.dir/builder_basic.o.requires

CMakeFiles/builder_basic.dir/builder_basic.o.provides: CMakeFiles/builder_basic.dir/builder_basic.o.requires
	$(MAKE) -f CMakeFiles/builder_basic.dir/build.make CMakeFiles/builder_basic.dir/builder_basic.o.provides.build
.PHONY : CMakeFiles/builder_basic.dir/builder_basic.o.provides

CMakeFiles/builder_basic.dir/builder_basic.o.provides.build: CMakeFiles/builder_basic.dir/builder_basic.o

# Object files for target builder_basic
builder_basic_OBJECTS = \
"CMakeFiles/builder_basic.dir/builder_basic.o"

# External object files for target builder_basic
builder_basic_EXTERNAL_OBJECTS =

builder_basic: CMakeFiles/builder_basic.dir/builder_basic.o
builder_basic: CMakeFiles/builder_basic.dir/build.make
builder_basic: CMakeFiles/builder_basic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable builder_basic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/builder_basic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/builder_basic.dir/build: builder_basic
.PHONY : CMakeFiles/builder_basic.dir/build

CMakeFiles/builder_basic.dir/requires: CMakeFiles/builder_basic.dir/builder_basic.o.requires
.PHONY : CMakeFiles/builder_basic.dir/requires

CMakeFiles/builder_basic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/builder_basic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/builder_basic.dir/clean

CMakeFiles/builder_basic.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx /root/mongo-cxx-driver-r3.1.1/examples/bsoncxx/CMakeFiles/builder_basic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/builder_basic.dir/depend

