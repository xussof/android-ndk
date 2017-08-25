package com.google.sample.jnilib;

import android.util.Log;

/**
 * Created by gfan on 8/24/17.
 */

public class AndroidService {
    final String moduleName = new String ("AndroidService");
    private int reference;
    public void init() {
        reference = 0;
    }
    public int addRef() {
        reference++;
        return reference;
    }
    public int delRef() {
        if (reference <= 0) {
            Log.i(moduleName, "Error de-referencing service object");
        } else {
            reference--;
        }
        return reference;
    }

    // 3 Java service functions to clients
    public  long javaComputeIntensive(int n) {
        return JavaHelperI(n);
    }

    public long javaComputeIntermediate(int val1, int val2) {
       return javaHelperM(val1, val2);
    }

    public long javaComputelight(int val1, int val2) {
        return (val1 + val2);
    }

    // 2 Native functions to accelerate 2 java interface functions
    // JavaHelperI() implemented inside jnilib's c/C++ code.
    public native long JavaHelperI(int n);

    // javaHelperM() is implemented directly inside :native module's c/C++ code
    public native long javaHelperM(int val1, int val2);

    static {
        System.loadLibrary("jniLib");
    }
}
