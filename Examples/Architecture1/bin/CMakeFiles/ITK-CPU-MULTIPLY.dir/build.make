# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pward/Architecture1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pward/Architecture1

# Include any dependencies generated for this target.
include bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/flags.make

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/flags.make
bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o: src/itk-cpu-multiply.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pward/Architecture1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o"
	cd /home/pward/Architecture1/bin && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o -c /home/pward/Architecture1/src/itk-cpu-multiply.cxx

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.i"
	cd /home/pward/Architecture1/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pward/Architecture1/src/itk-cpu-multiply.cxx > CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.i

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.s"
	cd /home/pward/Architecture1/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pward/Architecture1/src/itk-cpu-multiply.cxx -o CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.s

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.requires:
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.requires

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.provides: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.requires
	$(MAKE) -f bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/build.make bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.provides.build
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.provides

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.provides.build: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.provides.build

# Object files for target ITK-CPU-MULTIPLY
ITK__CPU__MULTIPLY_OBJECTS = \
"CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o"

# External object files for target ITK-CPU-MULTIPLY
ITK__CPU__MULTIPLY_EXTERNAL_OBJECTS =

bin/ITK-CPU-MULTIPLY: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o
bin/ITK-CPU-MULTIPLY: /usr/local/cuda/lib64/libcudart.so
bin/ITK-CPU-MULTIPLY: /usr/lib64/libcuda.so
bin/ITK-CPU-MULTIPLY: /home/pward/NVIDIA_GPU_Computing_SDK/C/lib/libcutil.a
bin/ITK-CPU-MULTIPLY: /usr/lib64/libuuid.so
bin/ITK-CPU-MULTIPLY: /usr/local/cuda/lib64/libcudart.so
bin/ITK-CPU-MULTIPLY: /usr/lib64/libcuda.so
bin/ITK-CPU-MULTIPLY: /home/pward/NVIDIA_GPU_Computing_SDK/C/lib/libcutil.a
bin/ITK-CPU-MULTIPLY: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/build.make
bin/ITK-CPU-MULTIPLY: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ITK-CPU-MULTIPLY"
	cd /home/pward/Architecture1/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ITK-CPU-MULTIPLY.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/build: bin/ITK-CPU-MULTIPLY
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/build

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/requires: bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/itk-cpu-multiply.cxx.o.requires
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/requires

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/clean:
	cd /home/pward/Architecture1/bin && $(CMAKE_COMMAND) -P CMakeFiles/ITK-CPU-MULTIPLY.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/clean

bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/depend:
	cd /home/pward/Architecture1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pward/Architecture1 /home/pward/Architecture1/src /home/pward/Architecture1 /home/pward/Architecture1/bin /home/pward/Architecture1/bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/ITK-CPU-MULTIPLY.dir/depend

