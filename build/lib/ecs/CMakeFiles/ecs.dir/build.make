# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /home/Pywwo/rtype

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Pywwo/rtype/build

# Include any dependencies generated for this target.
include lib/ecs/CMakeFiles/ecs.dir/depend.make

# Include the progress variables for this target.
include lib/ecs/CMakeFiles/ecs.dir/progress.make

# Include the compile flags for this target's objects.
include lib/ecs/CMakeFiles/ecs.dir/flags.make

lib/ecs/CMakeFiles/ecs.dir/sources/components/Component.cpp.o: lib/ecs/CMakeFiles/ecs.dir/flags.make
lib/ecs/CMakeFiles/ecs.dir/sources/components/Component.cpp.o: ../lib/ecs/sources/components/Component.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Pywwo/rtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/ecs/CMakeFiles/ecs.dir/sources/components/Component.cpp.o"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs.dir/sources/components/Component.cpp.o -c /home/Pywwo/rtype/lib/ecs/sources/components/Component.cpp

lib/ecs/CMakeFiles/ecs.dir/sources/components/Component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs.dir/sources/components/Component.cpp.i"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Pywwo/rtype/lib/ecs/sources/components/Component.cpp > CMakeFiles/ecs.dir/sources/components/Component.cpp.i

lib/ecs/CMakeFiles/ecs.dir/sources/components/Component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs.dir/sources/components/Component.cpp.s"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Pywwo/rtype/lib/ecs/sources/components/Component.cpp -o CMakeFiles/ecs.dir/sources/components/Component.cpp.s

lib/ecs/CMakeFiles/ecs.dir/sources/entities/Entity.cpp.o: lib/ecs/CMakeFiles/ecs.dir/flags.make
lib/ecs/CMakeFiles/ecs.dir/sources/entities/Entity.cpp.o: ../lib/ecs/sources/entities/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Pywwo/rtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/ecs/CMakeFiles/ecs.dir/sources/entities/Entity.cpp.o"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs.dir/sources/entities/Entity.cpp.o -c /home/Pywwo/rtype/lib/ecs/sources/entities/Entity.cpp

lib/ecs/CMakeFiles/ecs.dir/sources/entities/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs.dir/sources/entities/Entity.cpp.i"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Pywwo/rtype/lib/ecs/sources/entities/Entity.cpp > CMakeFiles/ecs.dir/sources/entities/Entity.cpp.i

lib/ecs/CMakeFiles/ecs.dir/sources/entities/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs.dir/sources/entities/Entity.cpp.s"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Pywwo/rtype/lib/ecs/sources/entities/Entity.cpp -o CMakeFiles/ecs.dir/sources/entities/Entity.cpp.s

lib/ecs/CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.o: lib/ecs/CMakeFiles/ecs.dir/flags.make
lib/ecs/CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.o: ../lib/ecs/sources/entities/EntityManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Pywwo/rtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/ecs/CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.o"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.o -c /home/Pywwo/rtype/lib/ecs/sources/entities/EntityManager.cpp

lib/ecs/CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.i"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Pywwo/rtype/lib/ecs/sources/entities/EntityManager.cpp > CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.i

lib/ecs/CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.s"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Pywwo/rtype/lib/ecs/sources/entities/EntityManager.cpp -o CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.s

lib/ecs/CMakeFiles/ecs.dir/sources/systems/System.cpp.o: lib/ecs/CMakeFiles/ecs.dir/flags.make
lib/ecs/CMakeFiles/ecs.dir/sources/systems/System.cpp.o: ../lib/ecs/sources/systems/System.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Pywwo/rtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/ecs/CMakeFiles/ecs.dir/sources/systems/System.cpp.o"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs.dir/sources/systems/System.cpp.o -c /home/Pywwo/rtype/lib/ecs/sources/systems/System.cpp

lib/ecs/CMakeFiles/ecs.dir/sources/systems/System.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs.dir/sources/systems/System.cpp.i"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Pywwo/rtype/lib/ecs/sources/systems/System.cpp > CMakeFiles/ecs.dir/sources/systems/System.cpp.i

lib/ecs/CMakeFiles/ecs.dir/sources/systems/System.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs.dir/sources/systems/System.cpp.s"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Pywwo/rtype/lib/ecs/sources/systems/System.cpp -o CMakeFiles/ecs.dir/sources/systems/System.cpp.s

lib/ecs/CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.o: lib/ecs/CMakeFiles/ecs.dir/flags.make
lib/ecs/CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.o: ../lib/ecs/sources/systems/SystemManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Pywwo/rtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lib/ecs/CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.o"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.o -c /home/Pywwo/rtype/lib/ecs/sources/systems/SystemManager.cpp

lib/ecs/CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.i"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Pywwo/rtype/lib/ecs/sources/systems/SystemManager.cpp > CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.i

lib/ecs/CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.s"
	cd /home/Pywwo/rtype/build/lib/ecs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Pywwo/rtype/lib/ecs/sources/systems/SystemManager.cpp -o CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.s

# Object files for target ecs
ecs_OBJECTS = \
"CMakeFiles/ecs.dir/sources/components/Component.cpp.o" \
"CMakeFiles/ecs.dir/sources/entities/Entity.cpp.o" \
"CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.o" \
"CMakeFiles/ecs.dir/sources/systems/System.cpp.o" \
"CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.o"

# External object files for target ecs
ecs_EXTERNAL_OBJECTS =

lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/sources/components/Component.cpp.o
lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/sources/entities/Entity.cpp.o
lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/sources/entities/EntityManager.cpp.o
lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/sources/systems/System.cpp.o
lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/sources/systems/SystemManager.cpp.o
lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/build.make
lib/libecs.a: lib/ecs/CMakeFiles/ecs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Pywwo/rtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library ../libecs.a"
	cd /home/Pywwo/rtype/build/lib/ecs && $(CMAKE_COMMAND) -P CMakeFiles/ecs.dir/cmake_clean_target.cmake
	cd /home/Pywwo/rtype/build/lib/ecs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ecs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/ecs/CMakeFiles/ecs.dir/build: lib/libecs.a

.PHONY : lib/ecs/CMakeFiles/ecs.dir/build

lib/ecs/CMakeFiles/ecs.dir/clean:
	cd /home/Pywwo/rtype/build/lib/ecs && $(CMAKE_COMMAND) -P CMakeFiles/ecs.dir/cmake_clean.cmake
.PHONY : lib/ecs/CMakeFiles/ecs.dir/clean

lib/ecs/CMakeFiles/ecs.dir/depend:
	cd /home/Pywwo/rtype/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Pywwo/rtype /home/Pywwo/rtype/lib/ecs /home/Pywwo/rtype/build /home/Pywwo/rtype/build/lib/ecs /home/Pywwo/rtype/build/lib/ecs/CMakeFiles/ecs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/ecs/CMakeFiles/ecs.dir/depend

