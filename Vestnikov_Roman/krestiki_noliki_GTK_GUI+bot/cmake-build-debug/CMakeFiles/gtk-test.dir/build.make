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
CMAKE_COMMAND = "F:\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gtk-test.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/gtk-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtk-test.dir/flags.make

CMakeFiles/gtk-test.dir/main.obj: CMakeFiles/gtk-test.dir/flags.make
CMakeFiles/gtk-test.dir/main.obj: CMakeFiles/gtk-test.dir/includes_C.rsp
CMakeFiles/gtk-test.dir/main.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gtk-test.dir/main.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gtk-test.dir\main.obj -c D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\main.c

CMakeFiles/gtk-test.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtk-test.dir/main.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\main.c > CMakeFiles\gtk-test.dir\main.i

CMakeFiles/gtk-test.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtk-test.dir/main.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\main.c -o CMakeFiles\gtk-test.dir\main.s

CMakeFiles/gtk-test.dir/check_library.obj: CMakeFiles/gtk-test.dir/flags.make
CMakeFiles/gtk-test.dir/check_library.obj: CMakeFiles/gtk-test.dir/includes_C.rsp
CMakeFiles/gtk-test.dir/check_library.obj: ../check_library.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gtk-test.dir/check_library.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gtk-test.dir\check_library.obj -c D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\check_library.c

CMakeFiles/gtk-test.dir/check_library.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtk-test.dir/check_library.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\check_library.c > CMakeFiles\gtk-test.dir\check_library.i

CMakeFiles/gtk-test.dir/check_library.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtk-test.dir/check_library.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\check_library.c -o CMakeFiles\gtk-test.dir\check_library.s

CMakeFiles/gtk-test.dir/bot.obj: CMakeFiles/gtk-test.dir/flags.make
CMakeFiles/gtk-test.dir/bot.obj: CMakeFiles/gtk-test.dir/includes_C.rsp
CMakeFiles/gtk-test.dir/bot.obj: ../bot.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gtk-test.dir/bot.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gtk-test.dir\bot.obj -c D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\bot.c

CMakeFiles/gtk-test.dir/bot.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtk-test.dir/bot.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\bot.c > CMakeFiles\gtk-test.dir\bot.i

CMakeFiles/gtk-test.dir/bot.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtk-test.dir/bot.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\bot.c -o CMakeFiles\gtk-test.dir\bot.s

# Object files for target gtk-test
gtk__test_OBJECTS = \
"CMakeFiles/gtk-test.dir/main.obj" \
"CMakeFiles/gtk-test.dir/check_library.obj" \
"CMakeFiles/gtk-test.dir/bot.obj"

# External object files for target gtk-test
gtk__test_EXTERNAL_OBJECTS =

gtk-test.exe: CMakeFiles/gtk-test.dir/main.obj
gtk-test.exe: CMakeFiles/gtk-test.dir/check_library.obj
gtk-test.exe: CMakeFiles/gtk-test.dir/bot.obj
gtk-test.exe: CMakeFiles/gtk-test.dir/build.make
gtk-test.exe: CMakeFiles/gtk-test.dir/linklibs.rsp
gtk-test.exe: CMakeFiles/gtk-test.dir/objects1.rsp
gtk-test.exe: CMakeFiles/gtk-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable gtk-test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gtk-test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtk-test.dir/build: gtk-test.exe
.PHONY : CMakeFiles/gtk-test.dir/build

CMakeFiles/gtk-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\gtk-test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/gtk-test.dir/clean

CMakeFiles/gtk-test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug D:\GIt\MR2021\Vestnikov_Roman\krestiki_noliki_GTK_GUI+bot\cmake-build-debug\CMakeFiles\gtk-test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtk-test.dir/depend

