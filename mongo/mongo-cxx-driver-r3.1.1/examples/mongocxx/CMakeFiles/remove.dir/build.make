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
include CMakeFiles/remove.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/remove.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/remove.dir/flags.make

CMakeFiles/remove.dir/remove.o: CMakeFiles/remove.dir/flags.make
CMakeFiles/remove.dir/remove.o: remove.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remove.dir/remove.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remove.dir/remove.o -c /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/remove.cpp

CMakeFiles/remove.dir/remove.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remove.dir/remove.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/remove.cpp > CMakeFiles/remove.dir/remove.i

CMakeFiles/remove.dir/remove.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remove.dir/remove.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/remove.cpp -o CMakeFiles/remove.dir/remove.s

CMakeFiles/remove.dir/remove.o.requires:
.PHONY : CMakeFiles/remove.dir/remove.o.requires

CMakeFiles/remove.dir/remove.o.provides: CMakeFiles/remove.dir/remove.o.requires
	$(MAKE) -f CMakeFiles/remove.dir/build.make CMakeFiles/remove.dir/remove.o.provides.build
.PHONY : CMakeFiles/remove.dir/remove.o.provides

CMakeFiles/remove.dir/remove.o.provides.build: CMakeFiles/remove.dir/remove.o

# Object files for target remove
remove_OBJECTS = \
"CMakeFiles/remove.dir/remove.o"

# External object files for target remove
remove_EXTERNAL_OBJECTS =

remove: CMakeFiles/remove.dir/remove.o
remove: CMakeFiles/remove.dir/build.make
remove: CMakeFiles/remove.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable remove"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/remove.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/remove.dir/build: remove
.PHONY : CMakeFiles/remove.dir/build

CMakeFiles/remove.dir/requires: CMakeFiles/remove.dir/remove.o.requires
.PHONY : CMakeFiles/remove.dir/requires

CMakeFiles/remove.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/remove.dir/cmake_clean.cmake
.PHONY : CMakeFiles/remove.dir/clean

CMakeFiles/remove.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/mongocxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles/remove.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/remove.dir/depend

