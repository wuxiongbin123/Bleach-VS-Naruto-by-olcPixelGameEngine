# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = "C:\Users\Poker Joker\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\232.9559.58\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\Poker Joker\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\232.9559.58\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bvn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bvn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bvn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bvn.dir/flags.make

CMakeFiles/bvn.dir/main.cpp.obj: CMakeFiles/bvn.dir/flags.make
CMakeFiles/bvn.dir/main.cpp.obj: D:/LearningDocuments_D/Research/olcPixelGameEngine/Bleach-VS-Naruto-by-olcPixelGameEngine/main.cpp
CMakeFiles/bvn.dir/main.cpp.obj: CMakeFiles/bvn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bvn.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bvn.dir/main.cpp.obj -MF CMakeFiles\bvn.dir\main.cpp.obj.d -o CMakeFiles\bvn.dir\main.cpp.obj -c D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\main.cpp

CMakeFiles/bvn.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bvn.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\main.cpp > CMakeFiles\bvn.dir\main.cpp.i

CMakeFiles/bvn.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bvn.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\main.cpp -o CMakeFiles\bvn.dir\main.cpp.s

CMakeFiles/bvn.dir/engine.cpp.obj: CMakeFiles/bvn.dir/flags.make
CMakeFiles/bvn.dir/engine.cpp.obj: D:/LearningDocuments_D/Research/olcPixelGameEngine/Bleach-VS-Naruto-by-olcPixelGameEngine/engine.cpp
CMakeFiles/bvn.dir/engine.cpp.obj: CMakeFiles/bvn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bvn.dir/engine.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bvn.dir/engine.cpp.obj -MF CMakeFiles\bvn.dir\engine.cpp.obj.d -o CMakeFiles\bvn.dir\engine.cpp.obj -c D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\engine.cpp

CMakeFiles/bvn.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bvn.dir/engine.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\engine.cpp > CMakeFiles\bvn.dir\engine.cpp.i

CMakeFiles/bvn.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bvn.dir/engine.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\engine.cpp -o CMakeFiles\bvn.dir\engine.cpp.s

CMakeFiles/bvn.dir/music.cpp.obj: CMakeFiles/bvn.dir/flags.make
CMakeFiles/bvn.dir/music.cpp.obj: D:/LearningDocuments_D/Research/olcPixelGameEngine/Bleach-VS-Naruto-by-olcPixelGameEngine/music.cpp
CMakeFiles/bvn.dir/music.cpp.obj: CMakeFiles/bvn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bvn.dir/music.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bvn.dir/music.cpp.obj -MF CMakeFiles\bvn.dir\music.cpp.obj.d -o CMakeFiles\bvn.dir\music.cpp.obj -c D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\music.cpp

CMakeFiles/bvn.dir/music.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bvn.dir/music.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\music.cpp > CMakeFiles\bvn.dir\music.cpp.i

CMakeFiles/bvn.dir/music.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bvn.dir/music.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\music.cpp -o CMakeFiles\bvn.dir\music.cpp.s

# Object files for target bvn
bvn_OBJECTS = \
"CMakeFiles/bvn.dir/main.cpp.obj" \
"CMakeFiles/bvn.dir/engine.cpp.obj" \
"CMakeFiles/bvn.dir/music.cpp.obj"

# External object files for target bvn
bvn_EXTERNAL_OBJECTS =

bvn.exe: CMakeFiles/bvn.dir/main.cpp.obj
bvn.exe: CMakeFiles/bvn.dir/engine.cpp.obj
bvn.exe: CMakeFiles/bvn.dir/music.cpp.obj
bvn.exe: CMakeFiles/bvn.dir/build.make
bvn.exe: CMakeFiles/bvn.dir/linkLibs.rsp
bvn.exe: CMakeFiles/bvn.dir/objects1.rsp
bvn.exe: CMakeFiles/bvn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bvn.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bvn.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bvn.dir/build: bvn.exe
.PHONY : CMakeFiles/bvn.dir/build

CMakeFiles/bvn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bvn.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bvn.dir/clean

CMakeFiles/bvn.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug D:\LearningDocuments_D\Research\olcPixelGameEngine\Bleach-VS-Naruto-by-olcPixelGameEngine\cmake-build-debug\CMakeFiles\bvn.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bvn.dir/depend

