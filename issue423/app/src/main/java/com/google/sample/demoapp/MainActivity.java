package com.google.sample.demoapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.google.sample.jnilib.AndroidService;

public class MainActivity extends AppCompatActivity {

    AndroidService service_;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = (TextView)findViewById(R.id.textView);
        service_ = new AndroidService();
        long testMedium = service_.javaComputeIntermediate(10, 20);

        tv.setText("App Self CallToJni: " + appCallJniLib(20) + "\n" +
                "jniLib(J) to jniLib(C-code) to Native(C): " + service_.javaComputeIntensive(10) + "\n" +
                "jniLib(J) to Native(C):" + testMedium + "\n" +
                "jniLib(J)(pure java):"  + service_.javaComputelight(55, 0xaa));
    }

    public native long appCallJniLib(int seed);

    static {
        System.loadLibrary("demoApp");
    }
}
