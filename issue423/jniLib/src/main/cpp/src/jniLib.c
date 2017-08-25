/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <android/log.h>
#include <stdint.h>
#include <jni.h>
#include "native.h"
#include "jniLib.h"

#if defined(__GNUC__) && __GNUC__ >= 4
#define GMATH_EXPORT __attribute__((visibility("default")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)
#define GMATH_EXPORT __attribute__((visibility("default")))
#else
#define GMATH_EXPORT
#endif

#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, "gmath::", __VA_ARGS__))

static unsigned internalCompute(unsigned n) {
  if (n == 0)
    return 1;
  unsigned val =  internalCompute(n/2) * internalCompute(n/2);
  if (n & 1) {
    val *= 2;
  }
  return val;
}

/*
 * fake some function
 */
GMATH_EXPORT unsigned jnilibNativeService(unsigned n, uint64_t *time) {
    uint64_t ticks = GetTicks();

    unsigned val = internalCompute(n);
    ticks = GetTicks() - ticks;
    if (time)
      *time += ticks;

    return val;
}

JNIEXPORT jlong JNICALL
   Java_com_google_sample_jnilib_AndroidService_JavaHelperI(JNIEnv *env, jobject instance,
                                                           jint n) {
  uint64_t ticks = (uint64_t)0;
  jlong result = (jlong) jnilibNativeService(n, &ticks);
  return result;
}

