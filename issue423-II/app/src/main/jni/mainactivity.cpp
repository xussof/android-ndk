#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <android/log.h>
#include <jniLib.h>


#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "hello-libs::", __VA_ARGS__))



extern "C" jlong JNICALL
Java_com_google_sample_demoapp_MainActivity_appCallJniLib(JNIEnv *env,
                                                          jobject instance,
                                                          jint seed) {
  // Just for simplicity, we do this right away; correct way would do it in
  // another thread...
  uint64_t ticks = static_cast<uint64_t>(0);

  for (auto exp = 0; exp < seed; ++exp) {
    uint64_t thisTime = 0;
    volatile unsigned val = jnilibNativeService(exp, &thisTime);
    (void) val;  // to silence compiler warning
    ticks += thisTime;
  }

  LOGI("calculation time: %" PRIu64, ticks);

  return static_cast<jlong>(ticks);
}