# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/Admin/AppData/Local/JetBrains/CLion2021.2/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Admin/AppData/Local/JetBrains/CLion2021.2/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Krestic_nulik.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Krestic_nulik.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Krestic_nulik.dir/flags.make

CMakeFiles/Krestic_nulik.dir/main.c.o: CMakeFiles/Krestic_nulik.dir/flags.make
CMakeFiles/Krestic_nulik.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Krestic_nulik.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Krestic_nulik.dir/main.c.o -c /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/main.c

CMakeFiles/Krestic_nulik.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Krestic_nulik.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/main.c > CMakeFiles/Krestic_nulik.dir/main.c.i

CMakeFiles/Krestic_nulik.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Krestic_nulik.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/main.c -o CMakeFiles/Krestic_nulik.dir/main.c.s

# Object files for target Krestic_nulik
Krestic_nulik_OBJECTS = \
"CMakeFiles/Krestic_nulik.dir/main.c.o"

# External object files for target Krestic_nulik
Krestic_nulik_EXTERNAL_OBJECTS =

Krestic_nulik.exe: CMakeFiles/Krestic_nulik.dir/main.c.o
Krestic_nulik.exe: CMakeFiles/Krestic_nulik.dir/build.make
Krestic_nulik.exe: CMakeFiles/Krestic_nulik.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Krestic_nulik.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Krestic_nulik.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Krestic_nulik.dir/build: Krestic_nulik.exe
.PHONY : CMakeFiles/Krestic_nulik.dir/build

CMakeFiles/Krestic_nulik.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Krestic_nulik.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Krestic_nulik.dir/clean

CMakeFiles/Krestic_nulik.dir/depend:
	cd /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug /cygdrive/c/Users/Admin/CLionProjects/MR2021/Elkin_Maxim/Krestik_nulik/cmake-build-debug/CMakeFiles/Krestic_nulik.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Krestic_nulik.dir/depend
