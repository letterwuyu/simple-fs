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
include CMakeFiles/document_validation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/document_validation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/document_validation.dir/flags.make

CMakeFiles/document_validation.dir/document_validation.o: CMakeFiles/document_validation.dir/flags.make
CMakeFiles/document_validation.dir/document_validation.o: document_validation.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/document_validation.dir/document_validation.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/document_validation.dir/document_validation.o -c /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/document_validation.cpp

CMakeFiles/document_validation.dir/document_validation.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/document_validation.dir/document_validation.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/document_validation.cpp > CMakeFiles/document_validation.dir/document_validation.i

CMakeFiles/document_validation.dir/document_validation.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/document_validation.dir/document_validation.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/document_validation.cpp -o CMakeFiles/document_validation.dir/document_validation.s

CMakeFiles/document_validation.dir/document_validation.o.requires:
.PHONY : CMakeFiles/document_validation.dir/document_validation.o.requires

CMakeFiles/document_validation.dir/document_validation.o.provides: CMakeFiles/document_validation.dir/document_validation.o.requires
	$(MAKE) -f CMakeFiles/document_validation.dir/build.make CMakeFiles/document_validation.dir/document_validation.o.provides.build
.PHONY : CMakeFiles/document_validation.dir/document_validation.o.provides

CMakeFiles/document_validation.dir/document_validation.o.provides.build: CMakeFiles/document_validation.dir/document_validation.o

# Object files for target document_validation
document_validation_OBJECTS = \
"CMakeFiles/document_validation.dir/document_validation.o"

# External object files for target document_validation
document_validation_EXTERNAL_OBJECTS =

document_validation: CMakeFiles/document_validation.dir/document_validation.o
document_validation: CMakeFiles/document_validation.dir/build.make
document_validation: CMakeFiles/document_validation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable document_validation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/document_validation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/document_validation.dir/build: document_validation
.PHONY : CMakeFiles/document_validation.dir/build

CMakeFiles/document_validation.dir/requires: CMakeFiles/document_validation.dir/document_validation.o.requires
.PHONY : CMakeFiles/document_validation.dir/requires

CMakeFiles/document_validation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/document_validation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/document_validation.dir/clean

CMakeFiles/document_validation.dir/depend:
	cd /root/mongo-cxx-driver-r3.1.1/examples/mongocxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx /root/mongo-cxx-driver-r3.1.1/examples/mongocxx/CMakeFiles/document_validation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/document_validation.dir/depend
