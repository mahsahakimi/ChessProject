# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/mahsa/AP Project/faz2/test"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/mahsa/AP Project/faz2/test"

# Include any dependencies generated for this target.
include CMakeFiles/x.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/x.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/x.dir/flags.make

CMakeFiles/x.dir/test5.cpp.o: CMakeFiles/x.dir/flags.make
CMakeFiles/x.dir/test5.cpp.o: test5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mahsa/AP Project/faz2/test/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/x.dir/test5.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/x.dir/test5.cpp.o -c "/home/mahsa/AP Project/faz2/test/test5.cpp"

CMakeFiles/x.dir/test5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/x.dir/test5.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/mahsa/AP Project/faz2/test/test5.cpp" > CMakeFiles/x.dir/test5.cpp.i

CMakeFiles/x.dir/test5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/x.dir/test5.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/mahsa/AP Project/faz2/test/test5.cpp" -o CMakeFiles/x.dir/test5.cpp.s

# Object files for target x
x_OBJECTS = \
"CMakeFiles/x.dir/test5.cpp.o"

# External object files for target x
x_EXTERNAL_OBJECTS =

x : CMakeFiles/x.dir/test5.cpp.o
x : CMakeFiles/x.dir/build.make
x : CMakeFiles/x.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/mahsa/AP Project/faz2/test/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable x"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/x.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/x.dir/build: x

.PHONY : CMakeFiles/x.dir/build

CMakeFiles/x.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/x.dir/cmake_clean.cmake
.PHONY : CMakeFiles/x.dir/clean

CMakeFiles/x.dir/depend:
	cd "/home/mahsa/AP Project/faz2/test" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/mahsa/AP Project/faz2/test" "/home/mahsa/AP Project/faz2/test" "/home/mahsa/AP Project/faz2/test" "/home/mahsa/AP Project/faz2/test" "/home/mahsa/AP Project/faz2/test/CMakeFiles/x.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/x.dir/depend

