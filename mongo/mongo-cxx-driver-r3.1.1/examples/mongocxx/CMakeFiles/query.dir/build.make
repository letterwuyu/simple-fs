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
CMAKE_SOURCE_DIR = /root/mongo-cxx-driver-r3.1.1/examples/mongocxx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/mongo-cxx-driver-r3.1.1/examples/mongocxx

# Include any dependencies generated for this target.
include CMakeFiles/query.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/query.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/query.dir/flags.make

CMakeFiles/query.dir/query.o: CMakeFiles/query.dir/flags.make
CMakeFiles/query.dir/query.o: query.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/query.dir/query.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/query.dir/query.o -c /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/query.cpp

CMakeFiles/query.dir/query.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/query.dir/query.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/query.cpp > CMakeFiles/query.dir/query.i

CMakeFiles/query.dir/query.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/query.dir/query.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/query.cpp -o CMakeFiles/query.dir/query.s

CMakeFiles/query.dir/query.o.requires:
.PHONY : CMakeFiles/query.dir/query.o.requires

CMakeFiles/query.dir/query.o.provides: CMakeFiles/query.dir/query.o.requires
	$(MAKE) -f CMakeFiles/query.dir/build.make CMakeFiles/query.dir/query.o.provides.build
.PHONY : CMakeFiles/query.dir/query.o.provides

CMakeFiles/query.dir/query.o.provides.build: CMakeFiles/query.dir/query.o

# Object files for target query
query_OBJECTS = \
"CMakeFiles/query.dir/query.o"

# External object files for target query
query_EXTERNAL_OBJECTS =

query: CMakeFiles/query.dir/query.o
query: CMakeFiles/query.dir/build.make
query: CMakeFiles/query.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable query"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/query.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/query.dir/build: query
.PHONY : CMakeFiles/query.dir/build

CMakeFiles/query.dir/requires: CMakeFiles/query.dir/query.o.requires
.PHONY : CMakeFiles/query.dir/requires

CMakeFiles/query.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/query.dir/cmake_clean.cmake
.PHONY : CMakeFiles/query.dir/clean

CMakeFiles/query.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/mongocxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles/query.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/query.dir/depend

