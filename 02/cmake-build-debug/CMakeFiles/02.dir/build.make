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
CMAKE_COMMAND = /home/leonid/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5457.51/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/leonid/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5457.51/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leonid/CLionProjects/msu_cpp_spring_2022/02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/02.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/02.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02.dir/flags.make

CMakeFiles/02.dir/test_02.cpp.o: CMakeFiles/02.dir/flags.make
CMakeFiles/02.dir/test_02.cpp.o: ../test_02.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/02.dir/test_02.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/02.dir/test_02.cpp.o -c /home/leonid/CLionProjects/msu_cpp_spring_2022/02/test_02.cpp

CMakeFiles/02.dir/test_02.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02.dir/test_02.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leonid/CLionProjects/msu_cpp_spring_2022/02/test_02.cpp > CMakeFiles/02.dir/test_02.cpp.i

CMakeFiles/02.dir/test_02.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02.dir/test_02.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leonid/CLionProjects/msu_cpp_spring_2022/02/test_02.cpp -o CMakeFiles/02.dir/test_02.cpp.s

CMakeFiles/02.dir/Allocator.cpp.o: CMakeFiles/02.dir/flags.make
CMakeFiles/02.dir/Allocator.cpp.o: ../Allocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/02.dir/Allocator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/02.dir/Allocator.cpp.o -c /home/leonid/CLionProjects/msu_cpp_spring_2022/02/Allocator.cpp

CMakeFiles/02.dir/Allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02.dir/Allocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leonid/CLionProjects/msu_cpp_spring_2022/02/Allocator.cpp > CMakeFiles/02.dir/Allocator.cpp.i

CMakeFiles/02.dir/Allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02.dir/Allocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leonid/CLionProjects/msu_cpp_spring_2022/02/Allocator.cpp -o CMakeFiles/02.dir/Allocator.cpp.s

# Object files for target 02
02_OBJECTS = \
"CMakeFiles/02.dir/test_02.cpp.o" \
"CMakeFiles/02.dir/Allocator.cpp.o"

# External object files for target 02
02_EXTERNAL_OBJECTS =

02: CMakeFiles/02.dir/test_02.cpp.o
02: CMakeFiles/02.dir/Allocator.cpp.o
02: CMakeFiles/02.dir/build.make
02: CMakeFiles/02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable 02"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/02.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02.dir/build: 02
.PHONY : CMakeFiles/02.dir/build

CMakeFiles/02.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/02.dir/cmake_clean.cmake
.PHONY : CMakeFiles/02.dir/clean

CMakeFiles/02.dir/depend:
	cd /home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leonid/CLionProjects/msu_cpp_spring_2022/02 /home/leonid/CLionProjects/msu_cpp_spring_2022/02 /home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug /home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug /home/leonid/CLionProjects/msu_cpp_spring_2022/02/cmake-build-debug/CMakeFiles/02.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/02.dir/depend

