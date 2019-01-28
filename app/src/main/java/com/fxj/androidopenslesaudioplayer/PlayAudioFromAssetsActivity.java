package com.fxj.androidopenslesaudioplayer;

import android.os.Bundle;
import android.app.Activity;
import android.widget.Button;

public class PlayAudioFromAssetsActivity extends Activity {

    private Button btnPlay;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play_audio_from_assets);

        btnPlay = findViewById(R.id.btn_play);

    }

}
