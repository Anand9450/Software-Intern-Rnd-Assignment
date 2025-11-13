# Flam R&D Intern Assignment

This is my submission for the Software Engineering Intern (R&D) Assignment.

## 1. Features Implemented (Android + Web)

### Android App (Partial Implementation)

- **Project Setup:** Full Android Studio project configured with NDK (C++) support.
- **OpenCV Integration:** The OpenCV 4.x Android SDK has been imported as a module and linked in Gradle.
- **JNI (C++/Java) Communication:**
  - `MainActivity.java` is implemented to load a static `Bitmap` from resources.
  - A JNI function `detectEdges(Bitmap in, Bitmap out)` is defined to pass the bitmap to C++.
- **C++ OpenCV Logic:**
  - `native-lib.cpp` includes helper functions to convert `jobject` (Bitmap) to `cv::Mat`.
  - OpenCV's `cvtColor` (to grayscale) and `Canny` (for edge detection) are implemented in C++.

### Web Viewer (Complete)

- A minimal `/web` directory containing an HTML, CSS, and TypeScript project.
- The TypeScript file (`app.ts`) demonstrates DOM manipulation by updating a "stats" panel on the page.
- Displays a static sample image.

---

## 2. Screenshots

_(Note: The Android app does not currently build due to a persistent NDK/CMake build error. Screenshots are of the code and the working web viewer.)_

**Working Web Viewer:**
![Web Viewer Screenshot](web/web-viewer-screenshot.png)

**C++ OpenCV Logic (`native-lib.cpp`):**
![C++ Code Screenshot](code-screenshot.png)

---

## 3. Setup Instructions

- **Android:** Project requires the OpenCV Android SDK to be located at `C:/OpenCV-android-sdk/`.
- **Web:** Run `tsc app.ts` inside the `/web` folder to compile the TypeScript, then open `index.html`.

---

## 4. Quick Explanation of Architecture

- **JNI:** `MainActivity.java` calls the native function `detectEdges(Bitmap in, Bitmap out)`.
- **Frame Flow (Intended):**
  1.  Load `Bitmap` in Java.
  2.  Pass to `detectEdges` in `native-lib.cpp`.
  3.  C++: Convert `Bitmap` to `cv::Mat`.
  4.  C++: Process with `cvtColor` and `Canny`.
  5.  C++: Convert processed `cv::Mat` back to `Bitmap`.
  6.  Java: Display the output `Bitmap` in an `ImageView`.
- **TypeScript:** `app.ts` compiles to `app.js` and is loaded by `index.html` to update DOM elements.

### **Build Issue Note**

> During development, I ran into a persistent C++/CMake build error (`ninja: error: ... file missing`) related to linking the prebuilt `libopencv_java4.so` file. Despite confirming the file path is correct (`C:/OpenCV-android-sdk/sdk/native/libs/x86/libopencv_java4.so`), clearing all IDE/build caches (Invalidate, manual .cxx delete), and trying multiple `CMakeLists.txt` configurations, the build cache appears to be stuck. The code in `native-lib.cpp` represents the full logic for the static image processing task, but the project will not compile in its current state due to this linking error.
