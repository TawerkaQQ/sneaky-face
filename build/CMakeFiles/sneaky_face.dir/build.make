# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tawerka/temep/sneaky-face

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tawerka/temep/sneaky-face/build

# Include any dependencies generated for this target.
include CMakeFiles/sneaky_face.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sneaky_face.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sneaky_face.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sneaky_face.dir/flags.make

CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o: CMakeFiles/sneaky_face.dir/flags.make
CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o: sneaky_face_autogen/mocs_compilation.cpp
CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o: CMakeFiles/sneaky_face.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tawerka/temep/sneaky-face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o -MF CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o -c /home/tawerka/temep/sneaky-face/build/sneaky_face_autogen/mocs_compilation.cpp

CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tawerka/temep/sneaky-face/build/sneaky_face_autogen/mocs_compilation.cpp > CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.i

CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tawerka/temep/sneaky-face/build/sneaky_face_autogen/mocs_compilation.cpp -o CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.s

CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o: CMakeFiles/sneaky_face.dir/flags.make
CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o: ../sneaky_face/main.cpp
CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o: CMakeFiles/sneaky_face.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tawerka/temep/sneaky-face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o -MF CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o.d -o CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o -c /home/tawerka/temep/sneaky-face/sneaky_face/main.cpp

CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tawerka/temep/sneaky-face/sneaky_face/main.cpp > CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.i

CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tawerka/temep/sneaky-face/sneaky_face/main.cpp -o CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.s

CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o: CMakeFiles/sneaky_face.dir/flags.make
CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o: ../sneaky_face/mainwindow.cpp
CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o: CMakeFiles/sneaky_face.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tawerka/temep/sneaky-face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o -MF CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o.d -o CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o -c /home/tawerka/temep/sneaky-face/sneaky_face/mainwindow.cpp

CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tawerka/temep/sneaky-face/sneaky_face/mainwindow.cpp > CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.i

CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tawerka/temep/sneaky-face/sneaky_face/mainwindow.cpp -o CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.s

CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o: CMakeFiles/sneaky_face.dir/flags.make
CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o: ../sneaky_face/videowindow.cpp
CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o: CMakeFiles/sneaky_face.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tawerka/temep/sneaky-face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o -MF CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o.d -o CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o -c /home/tawerka/temep/sneaky-face/sneaky_face/videowindow.cpp

CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tawerka/temep/sneaky-face/sneaky_face/videowindow.cpp > CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.i

CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tawerka/temep/sneaky-face/sneaky_face/videowindow.cpp -o CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.s

CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o: CMakeFiles/sneaky_face.dir/flags.make
CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o: ../sneaky_face/face_detect.cpp
CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o: CMakeFiles/sneaky_face.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tawerka/temep/sneaky-face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o -MF CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o.d -o CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o -c /home/tawerka/temep/sneaky-face/sneaky_face/face_detect.cpp

CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tawerka/temep/sneaky-face/sneaky_face/face_detect.cpp > CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.i

CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tawerka/temep/sneaky-face/sneaky_face/face_detect.cpp -o CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.s

# Object files for target sneaky_face
sneaky_face_OBJECTS = \
"CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o" \
"CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o" \
"CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o" \
"CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o"

# External object files for target sneaky_face
sneaky_face_EXTERNAL_OBJECTS =

sneaky_face: CMakeFiles/sneaky_face.dir/sneaky_face_autogen/mocs_compilation.cpp.o
sneaky_face: CMakeFiles/sneaky_face.dir/sneaky_face/main.cpp.o
sneaky_face: CMakeFiles/sneaky_face.dir/sneaky_face/mainwindow.cpp.o
sneaky_face: CMakeFiles/sneaky_face.dir/sneaky_face/videowindow.cpp.o
sneaky_face: CMakeFiles/sneaky_face.dir/sneaky_face/face_detect.cpp.o
sneaky_face: CMakeFiles/sneaky_face.dir/build.make
sneaky_face: /opt/onnxruntime/lib/libonnxruntime.so
sneaky_face: /usr/lib/x86_64-linux-gnu/libQt5MultimediaWidgets.so.5.15.3
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_alphamat.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_barcode.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_intensity_transform.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_mcc.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_rapid.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_wechat_qrcode.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.5.4d
sneaky_face: /opt/onnxruntime/lib/libonnxruntime.so
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.5.4d
sneaky_face: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
sneaky_face: /usr/lib/x86_64-linux-gnu/libQt5Multimedia.so.5.15.3
sneaky_face: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.15.3
sneaky_face: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
sneaky_face: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
sneaky_face: CMakeFiles/sneaky_face.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tawerka/temep/sneaky-face/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable sneaky_face"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sneaky_face.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sneaky_face.dir/build: sneaky_face
.PHONY : CMakeFiles/sneaky_face.dir/build

CMakeFiles/sneaky_face.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sneaky_face.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sneaky_face.dir/clean

CMakeFiles/sneaky_face.dir/depend:
	cd /home/tawerka/temep/sneaky-face/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tawerka/temep/sneaky-face /home/tawerka/temep/sneaky-face /home/tawerka/temep/sneaky-face/build /home/tawerka/temep/sneaky-face/build /home/tawerka/temep/sneaky-face/build/CMakeFiles/sneaky_face.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sneaky_face.dir/depend

