#include <jni.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <android/bitmap.h>

using namespace cv;
extern "C" {
void bitmapToMat(JNIEnv *env, jobject bitmap, Mat &dst) {
    AndroidBitmapInfo info;
    void *pixels = 0;

    AndroidBitmap_getInfo(env, bitmap, &info);
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    dst.create(info.height, info.width, CV_8UC4);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat tmp(info.height, info.width, CV_8UC4, pixels);
        cvtColor(tmp, dst, COLOR_RGBA2BGRA);
    } else {
        Mat tmp(info.height, info.width, CV_8UC2, pixels);
        cvtColor(tmp, dst, COLOR_BGR5652BGRA);
    }

    AndroidBitmap_unlockPixels(env, bitmap);
}

void matToBitmap(JNIEnv *env, Mat src, jobject bitmap) {
    AndroidBitmapInfo info;
    void *pixels = 0;

    AndroidBitmap_getInfo(env, bitmap, &info);
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat tmp(info.height, info.width, CV_8UC4, pixels);
        if (src.type() == CV_8UC1) {
            cvtColor(src, tmp, COLOR_GRAY2RGBA);
        } else if (src.type() == CV_8UC3) {
            cvtColor(src, tmp, COLOR_BGR2RGBA);
        } else if (src.type() == CV_8UC4) {
            cvtColor(src, tmp, COLOR_BGRA2RGBA);
        }
    } else {
        // Handle other formats if needed
    }

    AndroidBitmap_unlockPixels(env, bitmap);
}

// Our new JNI function to process the image
JNIEXPORT void JNICALL
Java_com_example_flam_1rnd_1assignment_MainActivity_detectEdges(
        JNIEnv *env,
        jobject /* this */,
        jobject inBitmap,
        jobject outBitmap) {

    Mat inMat;
    bitmapToMat(env, inBitmap, inMat);

    // Create a grayscale Mat
    Mat grayMat;
    cvtColor(inMat, grayMat, COLOR_BGR2GRAY);

    // Create an output Mat for Canny
    Mat cannyMat;
    Canny(grayMat, cannyMat, 80, 100);

    // Convert the Canny output back to the output bitmap
    matToBitmap(env, cannyMat, outBitmap);
}

// The original stringFromJNI function (we can leave it)
JNIEXPORT jstring JNICALL
Java_com_example_flam_1rnd_1assignment_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

} // extern "C"