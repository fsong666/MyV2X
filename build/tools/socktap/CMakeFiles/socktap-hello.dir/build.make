# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sf/Documents/vanetza-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sf/Documents/vanetza-master/build

# Include any dependencies generated for this target.
include tools/socktap/CMakeFiles/socktap-hello.dir/depend.make

# Include the progress variables for this target.
include tools/socktap/CMakeFiles/socktap-hello.dir/progress.make

# Include the compile flags for this target's objects.
include tools/socktap/CMakeFiles/socktap-hello.dir/flags.make

tools/socktap/CMakeFiles/socktap-hello.dir/hello_application.cpp.o: tools/socktap/CMakeFiles/socktap-hello.dir/flags.make
tools/socktap/CMakeFiles/socktap-hello.dir/hello_application.cpp.o: ../tools/socktap/hello_application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Documents/vanetza-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/socktap/CMakeFiles/socktap-hello.dir/hello_application.cpp.o"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socktap-hello.dir/hello_application.cpp.o -c /home/sf/Documents/vanetza-master/tools/socktap/hello_application.cpp

tools/socktap/CMakeFiles/socktap-hello.dir/hello_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socktap-hello.dir/hello_application.cpp.i"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sf/Documents/vanetza-master/tools/socktap/hello_application.cpp > CMakeFiles/socktap-hello.dir/hello_application.cpp.i

tools/socktap/CMakeFiles/socktap-hello.dir/hello_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socktap-hello.dir/hello_application.cpp.s"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sf/Documents/vanetza-master/tools/socktap/hello_application.cpp -o CMakeFiles/socktap-hello.dir/hello_application.cpp.s

tools/socktap/CMakeFiles/socktap-hello.dir/main_hello.cpp.o: tools/socktap/CMakeFiles/socktap-hello.dir/flags.make
tools/socktap/CMakeFiles/socktap-hello.dir/main_hello.cpp.o: ../tools/socktap/main_hello.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sf/Documents/vanetza-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tools/socktap/CMakeFiles/socktap-hello.dir/main_hello.cpp.o"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socktap-hello.dir/main_hello.cpp.o -c /home/sf/Documents/vanetza-master/tools/socktap/main_hello.cpp

tools/socktap/CMakeFiles/socktap-hello.dir/main_hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socktap-hello.dir/main_hello.cpp.i"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sf/Documents/vanetza-master/tools/socktap/main_hello.cpp > CMakeFiles/socktap-hello.dir/main_hello.cpp.i

tools/socktap/CMakeFiles/socktap-hello.dir/main_hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socktap-hello.dir/main_hello.cpp.s"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sf/Documents/vanetza-master/tools/socktap/main_hello.cpp -o CMakeFiles/socktap-hello.dir/main_hello.cpp.s

# Object files for target socktap-hello
socktap__hello_OBJECTS = \
"CMakeFiles/socktap-hello.dir/hello_application.cpp.o" \
"CMakeFiles/socktap-hello.dir/main_hello.cpp.o"

# External object files for target socktap-hello
socktap__hello_EXTERNAL_OBJECTS =

bin/socktap-hello: tools/socktap/CMakeFiles/socktap-hello.dir/hello_application.cpp.o
bin/socktap-hello: tools/socktap/CMakeFiles/socktap-hello.dir/main_hello.cpp.o
bin/socktap-hello: tools/socktap/CMakeFiles/socktap-hello.dir/build.make
bin/socktap-hello: lib/static/libsocktap-common.a
bin/socktap-hello: /usr/local/lib/libboost_system.so
bin/socktap-hello: /usr/local/lib/libboost_program_options.so
bin/socktap-hello: /usr/lib/x86_64-linux-gnu/libgps.so
bin/socktap-hello: lib/static/libvanetza_btp.a
bin/socktap-hello: lib/static/libvanetza_facilities.a
bin/socktap-hello: lib/static/libvanetza_asn1.a
bin/socktap-hello: lib/static/libvanetza_geonet.a
bin/socktap-hello: lib/static/libvanetza_dcc.a
bin/socktap-hello: lib/static/libvanetza_access.a
bin/socktap-hello: lib/static/libvanetza_gnss.a
bin/socktap-hello: lib/static/libvanetza_security.a
bin/socktap-hello: lib/static/libvanetza_net.a
bin/socktap-hello: lib/static/libvanetza_common.a
bin/socktap-hello: /usr/local/lib/libboost_date_time.so
bin/socktap-hello: /usr/local/lib/libGeographic.so
bin/socktap-hello: /usr/lib/x86_64-linux-gnu/libcryptopp.so
bin/socktap-hello: tools/socktap/CMakeFiles/socktap-hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sf/Documents/vanetza-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/socktap-hello"
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socktap-hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/socktap/CMakeFiles/socktap-hello.dir/build: bin/socktap-hello

.PHONY : tools/socktap/CMakeFiles/socktap-hello.dir/build

tools/socktap/CMakeFiles/socktap-hello.dir/clean:
	cd /home/sf/Documents/vanetza-master/build/tools/socktap && $(CMAKE_COMMAND) -P CMakeFiles/socktap-hello.dir/cmake_clean.cmake
.PHONY : tools/socktap/CMakeFiles/socktap-hello.dir/clean

tools/socktap/CMakeFiles/socktap-hello.dir/depend:
	cd /home/sf/Documents/vanetza-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sf/Documents/vanetza-master /home/sf/Documents/vanetza-master/tools/socktap /home/sf/Documents/vanetza-master/build /home/sf/Documents/vanetza-master/build/tools/socktap /home/sf/Documents/vanetza-master/build/tools/socktap/CMakeFiles/socktap-hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/socktap/CMakeFiles/socktap-hello.dir/depend

