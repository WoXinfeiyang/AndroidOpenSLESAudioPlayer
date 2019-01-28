package com.fxj.androidopenslesaudioplayer;

import android.content.res.AssetManager;

public class PlayAudio {
    static{
        System.loadLibrary("PlayAudio");
    }

    public native void palayAudioFromAssets(AssetManager assetManager, String filename);
}
