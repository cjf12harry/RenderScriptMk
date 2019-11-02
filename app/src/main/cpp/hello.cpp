//
// Created by cjf12 on 2019-11-02.
//

#include <jni.h>
#include <android/log.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   app/src/main/java/com/example/hellolibs/MainActivity.java
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_packtpub_renderscriptmk_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("Hello World");
}
