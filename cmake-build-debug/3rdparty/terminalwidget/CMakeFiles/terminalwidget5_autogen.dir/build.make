# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/mapmap/Jetbrains/clion-2020.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mapmap/Jetbrains/clion-2020.2.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maomao/deepin/pr/deepin-terminal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug

# Utility rule file for terminalwidget5_autogen.

# Include the progress variables for this target.
include 3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/progress.make

3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/maomao/deepin/pr/deepin-terminal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target terminalwidget5"
	cd /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug/3rdparty/terminalwidget && /home/mapmap/Jetbrains/clion-2020.2.4/bin/cmake/linux/bin/cmake -E cmake_autogen /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug/3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/AutogenInfo.json Debug

terminalwidget5_autogen: 3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen
terminalwidget5_autogen: 3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/build.make

.PHONY : terminalwidget5_autogen

# Rule to build all files generated by this target.
3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/build: terminalwidget5_autogen

.PHONY : 3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/build

3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/clean:
	cd /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug/3rdparty/terminalwidget && $(CMAKE_COMMAND) -P CMakeFiles/terminalwidget5_autogen.dir/cmake_clean.cmake
.PHONY : 3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/clean

3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/depend:
	cd /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maomao/deepin/pr/deepin-terminal /home/maomao/deepin/pr/deepin-terminal/3rdparty/terminalwidget /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug/3rdparty/terminalwidget /home/maomao/deepin/pr/deepin-terminal/cmake-build-debug/3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rdparty/terminalwidget/CMakeFiles/terminalwidget5_autogen.dir/depend
