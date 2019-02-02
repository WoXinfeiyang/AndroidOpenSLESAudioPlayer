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

/**引擎接口*/
SLObjectItf engineObject=NULL;
SLEngineItf engineEngine=NULL;

/*混音器*/
SLObjectItf outputMixObject=NULL;
SLEnvironmentalReverbItf outputMixEnvironmentalReverb=NULL;
SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

//assets播放器
SLObjectItf fdPlayerObject = NULL;
SLPlayItf fdPlayerPlay = NULL;
SLVolumeItf fdPlayerVolume = NULL; //声音控制接口

void createEngine(){
    SLresult result;
    result=slCreateEngine(&engineObject,0,NULL,0,NULL,NULL);/*创建引擎*/
    result=(*engineObject)->Realize(engineObject,SL_BOOLEAN_FALSE);/*实现engineObject对象*/
    result=(*engineObject)->GetInterface(engineObject,SL_IID_ENGINE,&engineEngine);/*通过engineObject初始化engineEngine*/
}


JNIEXPORT void JNICALL
Java_com_fxj_androidopenslesaudioplayer_palayAudioFromAssets(JNIEnv *env, jobject instance, jobject assetManager, jstring filename) {
    const char *tag="palayAudioFromAssets";
    LogI(tag,"palayAudioFromAssets start");
    const char *fileName=(*env)->GetStringUTFChars(env,filename, NULL);

    AAssetManager *msg=AAssetManager_fromJava(env,assetManager);
    AAsset*asset= AAssetManager_open(msg,fileName,AASSET_MODE_UNKNOWN);

    off_t start,end;
    int fd= AAsset_openFileDescriptor(asset,&start,&end);

    AAsset_close(asset);
    (*env)->ReleaseStringUTFChars(env,filename,fileName);/*释放字符串资源*/

    SLresult result;
    createEngine();/*创建引擎*/

    /*创建混音器*/
    const SLInterfaceID mIds[1]={SL_IID_ENVIRONMENTALREVERB};
    (*engineEngine)->CreateOutputMix(engineEngine,&outputMixObject,1,mIds,SL_BOOLEAN_FALSE);/*利用引擎接口对象创建混音器对象*/
    (*outputMixObject)->Realize(&outputMixObject,SL_BOOLEAN_FALSE);/*实现混音器对象*/
    result=(*outputMixObject)->GetInterface(&outputMixObject,SL_IID_ENVIRONMENTALREVERB,&outputMixEnvironmentalReverb);
    if(result==SL_RESULT_SUCCESS){
        (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(outputMixEnvironmentalReverb,&reverbSettings);
    }

    /*1、配置 audio source*/
    SLDataLocator_AndroidFD locator_fd={SL_DATALOCATOR_ANDROIDFD,fd,start,end};
    SLDataFormat_MIME format_mime={SL_DATAFORMAT_MIME,NULL,SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc={&locator_fd,&format_mime};

    /*2、配置 audio sink*/
    SLDataLocator_OutputMix locator_outputMix={SL_DATALOCATOR_OUTPUTMIX,outputMixObject};
    SLDataSink sink={&locator_outputMix,NULL};

    const SLInterfaceID ids[3]={SL_IID_SEEK,SL_IID_MUTESOLO,SL_IID_VOLUME};
    const SLboolean req[3]={SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE};
    (*engineEngine)->CreateAudioPlayer(engineEngine,&fdPlayerObject,&audioSrc,&sink,3,ids,req);/*创建播放器*/
    (*fdPlayerObject)->Realize(fdPlayerObject,SL_BOOLEAN_TRUE);/*实现fdPlayerObject*/
    

    LogI(tag,"palayAudioFromAssets end");
}

