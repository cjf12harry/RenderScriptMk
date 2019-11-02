package com.packtpub.renderscriptmk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle saveInstanceState) {
        super.onCreate(saveInstanceState);
        TextView tv = new TextView(this);
        tv.setText( ""+stringFromJNI());
        setContentView(tv);
    }

    public native String stringFromJNI();

    static {
        System.loadLibrary("hello-libs");
    }
}
