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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Tic_tac_toe.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Tic_tac_toe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tic_tac_toe.dir/flags.make

CMakeFiles/Tic_tac_toe.dir/main.c.obj: CMakeFiles/Tic_tac_toe.dir/flags.make
CMakeFiles/Tic_tac_toe.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Tic_tac_toe.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Tic_tac_toe.dir\main.c.obj -c C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\main.c

CMakeFiles/Tic_tac_toe.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Tic_tac_toe.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\main.c > CMakeFiles\Tic_tac_toe.dir\main.c.i

CMakeFiles/Tic_tac_toe.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Tic_tac_toe.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\main.c -o CMakeFiles\Tic_tac_toe.dir\main.c.s

# Object files for target Tic_tac_toe
Tic_tac_toe_OBJECTS = \
"CMakeFiles/Tic_tac_toe.dir/main.c.obj"

# External object files for target Tic_tac_toe
Tic_tac_toe_EXTERNAL_OBJECTS =

Tic_tac_toe.exe: CMakeFiles/Tic_tac_toe.dir/main.c.obj
Tic_tac_toe.exe: CMakeFiles/Tic_tac_toe.dir/build.make
Tic_tac_toe.exe: CMakeFiles/Tic_tac_toe.dir/linklibs.rsp
Tic_tac_toe.exe: CMakeFiles/Tic_tac_toe.dir/objects1.rsp
Tic_tac_toe.exe: CMakeFiles/Tic_tac_toe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Tic_tac_toe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Tic_tac_toe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tic_tac_toe.dir/build: Tic_tac_toe.exe
.PHONY : CMakeFiles/Tic_tac_toe.dir/build

CMakeFiles/Tic_tac_toe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Tic_tac_toe.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Tic_tac_toe.dir/clean

CMakeFiles/Tic_tac_toe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\cmake-build-debug C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\cmake-build-debug C:\Users\kozyu\GIT\MR2021\Koziura_Konstantin\Tic_tac_toe\cmake-build-debug\CMakeFiles\Tic_tac_toe.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tic_tac_toe.dir/depend

