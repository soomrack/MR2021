# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\CLion\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\CCCCCC\btree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\CCCCCC\btree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/btree.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/btree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/btree.dir/flags.make

CMakeFiles/btree.dir/main.cpp.obj: CMakeFiles/btree.dir/flags.make
CMakeFiles/btree.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CCCCCC\btree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/btree.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\btree.dir\main.cpp.obj -c C:\CCCCCC\btree\main.cpp

CMakeFiles/btree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/btree.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CCCCCC\btree\main.cpp > CMakeFiles\btree.dir\main.cpp.i

CMakeFiles/btree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/btree.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CCCCCC\btree\main.cpp -o CMakeFiles\btree.dir\main.cpp.s

# Object files for target btree
btree_OBJECTS = \
"CMakeFiles/btree.dir/main.cpp.obj"

# External object files for target btree
btree_EXTERNAL_OBJECTS =

btree.exe: CMakeFiles/btree.dir/main.cpp.obj
btree.exe: CMakeFiles/btree.dir/build.make
btree.exe: CMakeFiles/btree.dir/linklibs.rsp
btree.exe: CMakeFiles/btree.dir/objects1.rsp
btree.exe: CMakeFiles/btree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CCCCCC\btree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable btree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\btree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/btree.dir/build: btree.exe
.PHONY : CMakeFiles/btree.dir/build

CMakeFiles/btree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\btree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/btree.dir/clean

CMakeFiles/btree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\CCCCCC\btree C:\CCCCCC\btree C:\CCCCCC\btree\cmake-build-debug C:\CCCCCC\btree\cmake-build-debug C:\CCCCCC\btree\cmake-build-debug\CMakeFiles\btree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/btree.dir/depend
