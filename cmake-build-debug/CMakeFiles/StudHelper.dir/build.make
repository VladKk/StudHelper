# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vladpc/Programming/C++/Projects/StudHelper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StudHelper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StudHelper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StudHelper.dir/flags.make

CMakeFiles/StudHelper.dir/main.cpp.o: CMakeFiles/StudHelper.dir/flags.make
CMakeFiles/StudHelper.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StudHelper.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StudHelper.dir/main.cpp.o -c /home/vladpc/Programming/C++/Projects/StudHelper/main.cpp

CMakeFiles/StudHelper.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StudHelper.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladpc/Programming/C++/Projects/StudHelper/main.cpp > CMakeFiles/StudHelper.dir/main.cpp.i

CMakeFiles/StudHelper.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StudHelper.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladpc/Programming/C++/Projects/StudHelper/main.cpp -o CMakeFiles/StudHelper.dir/main.cpp.s

CMakeFiles/StudHelper.dir/StudHelper.cpp.o: CMakeFiles/StudHelper.dir/flags.make
CMakeFiles/StudHelper.dir/StudHelper.cpp.o: ../StudHelper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/StudHelper.dir/StudHelper.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StudHelper.dir/StudHelper.cpp.o -c /home/vladpc/Programming/C++/Projects/StudHelper/StudHelper.cpp

CMakeFiles/StudHelper.dir/StudHelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StudHelper.dir/StudHelper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladpc/Programming/C++/Projects/StudHelper/StudHelper.cpp > CMakeFiles/StudHelper.dir/StudHelper.cpp.i

CMakeFiles/StudHelper.dir/StudHelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StudHelper.dir/StudHelper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladpc/Programming/C++/Projects/StudHelper/StudHelper.cpp -o CMakeFiles/StudHelper.dir/StudHelper.cpp.s

# Object files for target StudHelper
StudHelper_OBJECTS = \
"CMakeFiles/StudHelper.dir/main.cpp.o" \
"CMakeFiles/StudHelper.dir/StudHelper.cpp.o"

# External object files for target StudHelper
StudHelper_EXTERNAL_OBJECTS =

StudHelper: CMakeFiles/StudHelper.dir/main.cpp.o
StudHelper: CMakeFiles/StudHelper.dir/StudHelper.cpp.o
StudHelper: CMakeFiles/StudHelper.dir/build.make
StudHelper: /usr/lib/x86_64-linux-gnu/libxl.so
StudHelper: CMakeFiles/StudHelper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable StudHelper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StudHelper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StudHelper.dir/build: StudHelper

.PHONY : CMakeFiles/StudHelper.dir/build

CMakeFiles/StudHelper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StudHelper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StudHelper.dir/clean

CMakeFiles/StudHelper.dir/depend:
	cd /home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vladpc/Programming/C++/Projects/StudHelper /home/vladpc/Programming/C++/Projects/StudHelper /home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug /home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug /home/vladpc/Programming/C++/Projects/StudHelper/cmake-build-debug/CMakeFiles/StudHelper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StudHelper.dir/depend
