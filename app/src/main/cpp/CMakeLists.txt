cmake_minimum_required(VERSION 3.18.1)

# --- OpenCV Path ---
# This should be the path to the 'sdk' folder
set(OpenCV_SDK_DIR "C:/OpenCV-android-sdk/sdk")

# --- Include OpenCV Headers ---
include_directories(${OpenCV_SDK_DIR}/native/jni/include)

# --- Add OpenCV Prebuilt Library ---
# This finds the correct .so file for the current CPU architecture
add_library(lib_opencv SHARED IMPORTED)
set_target_properties(lib_opencv PROPERTIES
        IMPORTED_LOCATION
        ${OpenCV_SDK_DIR}/native/libs/${ANDROID_ABI}/libopencv_java4.so
)

# --- Add Your Native Library ---
# We must add the project() command to fix the warning
project(flam_rnd_assignment)

add_library(
        flam_rnd_assignment # This is your library name
        SHARED
        native-lib.cpp)

# --- Find NDK Libraries ---
find_library(log-lib log)
find_library(android-lib android)
find_library(bitmap-lib jnigraphics) # This is the bitmap library

# --- Link All Libraries ---
target_link_libraries(
        flam_rnd_assignment
        lib_opencv      # Link OpenCV
        ${log-lib}
        ${android-lib}
        ${bitmap-lib})