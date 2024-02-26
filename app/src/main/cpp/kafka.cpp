#include <jni.h>
#include <string>
#include <android/log.h>
#include <unordered_map>

#include "base64.h"
#include "utilities.h"
#include "obfuscate_crypt.h"
#include "obfuscate.h"

// Global unordered_map initialized with key-value pairs
std::unordered_map<std::string, std::string> hashmap = {
        {std::string(AY_OBFUSCATE("d0e196a0c25d35dd0a84593cbae0f38333aa58529936444ea26453eab28dfc86")), std::string(AY_CRYPT_OBFUSCATE("https://www.google.com/"))},
        {std::string(AY_OBFUSCATE("0de69f56365c10550d05e65ae8229dd0686f7894a807830daec8caa879731f4d")), std::string(AY_CRYPT_OBFUSCATE("https://mail.google.com/mail/u/0/#inbox"))},
        {std::string(AY_OBFUSCATE("db902c3abfb8b6c3beecc6cb91e014140b2ab1fe9fd5388b838352bc44dd1f92")), std::string(AY_CRYPT_OBFUSCATE("https://outlook.live.com/mail/0/"))},
        {std::string(AY_OBFUSCATE("26a978f15358def42114a8db2419316016e512ad3c8520e73d52c963d2a1effc")), std::string(AY_CRYPT_OBFUSCATE("https://account.proton.me/login"))}
};

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_nessunDorma(JNIEnv *env, jobject thiz, jstring keyJavaString) {
    // Convert Java string to C++ string
    const char *keyCStr = env->GetStringUTFChars(keyJavaString, nullptr);

    LOGD("In Key: %s", keyCStr);
    LOGD("Hashmap:");

    for (const auto &pair : hashmap) {
        LOGD("Key: %s, Value: %s\n", pair.first.c_str(), pair.second.c_str());
    }

    std::string val; // Use std::string to store the result temporarily

    if (hashmap.find(keyCStr) != hashmap.end()) {
        LOGD("Key found");
        std::string value = hashmap[keyCStr];
        val = base64_encode(reinterpret_cast<const BYTE *>(&value.c_str()[0]), strlen(value.c_str()));
    } else {
        LOGD("Key not found");
        const char *error = AY_CRYPT_OBFUSCATE("ERROR");
        val = base64_encode(reinterpret_cast<const BYTE *>(&error[0]), strlen(error));
    }

    // Convert std::string to jbyteArray
    jbyteArray byteArray = env->NewByteArray(val.size());
    env->SetByteArrayRegion(byteArray, 0, val.size(), reinterpret_cast<const jbyte*>(val.data()));
    env->ReleaseStringUTFChars(keyJavaString, keyCStr);
    return byteArray;
}
