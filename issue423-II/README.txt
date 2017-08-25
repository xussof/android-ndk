Description
===========
             +-->app-c/C++ -->jniLib-c/C++ --> native-c/C++
             |                  ^
  app-java --+                  |
             |                  |
             +->jniLib-java --->+
                                |
                                +--> native-c/C++ ( this is abnormal )

with the above, libNative.so is always compiled with version 2.3.3
     
