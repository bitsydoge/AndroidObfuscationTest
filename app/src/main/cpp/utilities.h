//
// Created by Doge on 20/02/2024.
//

#ifndef OBFUSCATIONTEST_UTILITIES_H
#define OBFUSCATIONTEST_UTILITIES_H

#include <jni.h>
#include <string>

std::string jstring_to_stdstring(JNIEnv *env, jstring jStr);
#define  LOG_TAG    "💋◄(KAFKA)►💋"
#ifdef NDEBUG
#define  LOGD(...)
#define  LOGW(...)
#define  LOGE(...)
#else
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGW(...) __android_log_print(ANDROID_LOG_WARNING, LOG_TAG, __VA_ARGS__)
#define  LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif
#endif //OBFUSCATIONTEST_UTILITIES_H