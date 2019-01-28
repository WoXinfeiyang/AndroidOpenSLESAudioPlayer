#include<jni.h>
#include<stdio.h>
#include <string.h>
#include <malloc.h>

// for opensles
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include"log.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_fxj_androidopenslesaudioplayer_palayAudioFromAssets(JNIEnv *env, jobject instance, jobject assetManager, jstring filename) {
    const char *tag="palayAudioFromAssets";
    LogI(tag,"palayAudioFromAssets start");

    
    LogI(tag,"palayAudioFromAssets end");
}

