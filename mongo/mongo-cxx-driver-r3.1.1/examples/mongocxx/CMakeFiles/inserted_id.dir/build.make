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
include CMakeFiles/inserted_id.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/inserted_id.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/inserted_id.dir/flags.make

CMakeFiles/inserted_id.dir/inserted_id.o: CMakeFiles/inserted_id.dir/flags.make
CMakeFiles/inserted_id.dir/inserted_id.o: inserted_id.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/inserted_id.dir/inserted_id.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/inserted_id.dir/inserted_id.o -c /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/inserted_id.cpp

CMakeFiles/inserted_id.dir/inserted_id.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/inserted_id.dir/inserted_id.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/inserted_id.cpp > CMakeFiles/inserted_id.dir/inserted_id.i

CMakeFiles/inserted_id.dir/inserted_id.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/inserted_id.dir/inserted_id.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/inserted_id.cpp -o CMakeFiles/inserted_id.dir/inserted_id.s

CMakeFiles/inserted_id.dir/inserted_id.o.requires:
.PHONY : CMakeFiles/inserted_id.dir/inserted_id.o.requires

CMakeFiles/inserted_id.dir/inserted_id.o.provides: CMakeFiles/inserted_id.dir/inserted_id.o.requires
	$(MAKE) -f CMakeFiles/inserted_id.dir/build.make CMakeFiles/inserted_id.dir/inserted_id.o.provides.build
.PHONY : CMakeFiles/inserted_id.dir/inserted_id.o.provides

CMakeFiles/inserted_id.dir/inserted_id.o.provides.build: CMakeFiles/inserted_id.dir/inserted_id.o

# Object files for target inserted_id
inserted_id_OBJECTS = \
"CMakeFiles/inserted_id.dir/inserted_id.o"

# External object files for target inserted_id
inserted_id_EXTERNAL_OBJECTS =

inserted_id: CMakeFiles/inserted_id.dir/inserted_id.o
inserted_id: CMakeFiles/inserted_id.dir/build.make
inserted_id: CMakeFiles/inserted_id.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable inserted_id"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inserted_id.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/inserted_id.dir/build: inserted_id
.PHONY : CMakeFiles/inserted_id.dir/build

CMakeFiles/inserted_id.dir/requires: CMakeFiles/inserted_id.dir/inserted_id.o.requires
.PHONY : CMakeFiles/inserted_id.dir/requires

CMakeFiles/inserted_id.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/inserted_id.dir/cmake_clean.cmake
.PHONY : CMakeFiles/inserted_id.dir/clean

CMakeFiles/inserted_id.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/mongocxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles/inserted_id.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/inserted_id.dir/depend
