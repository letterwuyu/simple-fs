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
include CMakeFiles/instance_management.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/instance_management.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/instance_management.dir/flags.make

CMakeFiles/instance_management.dir/instance_management.o: CMakeFiles/instance_management.dir/flags.make
CMakeFiles/instance_management.dir/instance_management.o: instance_management.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/instance_management.dir/instance_management.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/instance_management.dir/instance_management.o -c /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/instance_management.cpp

CMakeFiles/instance_management.dir/instance_management.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/instance_management.dir/instance_management.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/instance_management.cpp > CMakeFiles/instance_management.dir/instance_management.i

CMakeFiles/instance_management.dir/instance_management.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/instance_management.dir/instance_management.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/instance_management.cpp -o CMakeFiles/instance_management.dir/instance_management.s

CMakeFiles/instance_management.dir/instance_management.o.requires:
.PHONY : CMakeFiles/instance_management.dir/instance_management.o.requires

CMakeFiles/instance_management.dir/instance_management.o.provides: CMakeFiles/instance_management.dir/instance_management.o.requires
	$(MAKE) -f CMakeFiles/instance_management.dir/build.make CMakeFiles/instance_management.dir/instance_management.o.provides.build
.PHONY : CMakeFiles/instance_management.dir/instance_management.o.provides

CMakeFiles/instance_management.dir/instance_management.o.provides.build: CMakeFiles/instance_management.dir/instance_management.o

# Object files for target instance_management
instance_management_OBJECTS = \
"CMakeFiles/instance_management.dir/instance_management.o"

# External object files for target instance_management
instance_management_EXTERNAL_OBJECTS =

instance_management: CMakeFiles/instance_management.dir/instance_management.o
instance_management: CMakeFiles/instance_management.dir/build.make
instance_management: CMakeFiles/instance_management.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable instance_management"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/instance_management.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/instance_management.dir/build: instance_management
.PHONY : CMakeFiles/instance_management.dir/build

CMakeFiles/instance_management.dir/requires: CMakeFiles/instance_management.dir/instance_management.o.requires
.PHONY : CMakeFiles/instance_management.dir/requires

CMakeFiles/instance_management.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/instance_management.dir/cmake_clean.cmake
.PHONY : CMakeFiles/instance_management.dir/clean

CMakeFiles/instance_management.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/mongocxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles/instance_management.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/instance_management.dir/depend

