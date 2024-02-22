#include <jni.h>
#include <string>
#include <android/log.h>
#include <unordered_map>

#include "base64.h"
#include "utilities.h"
#include "obfuscate.h"

const char *BASE_URL_PROD = AY_OBFUSCATE("https://twitter.com/");
const char *URLS_LIST[] = {AY_OBFUSCATE("https://account.proton.me/"),
                           AY_OBFUSCATE("https://mail.google.com/mail/u/0/"),
                           AY_OBFUSCATE("https://outlook.live.com/")};

// Global unordered_map initialized with key-value pairs
std::unordered_map<std::string, std::string> hashmap = {
        {std::string(AY_OBFUSCATE("d0e196a0c25d35dd0a84593cbae0f38333aa58529936444ea26453eab28dfc86")), std::string(AY_OBFUSCATE("https://www.google.com/"))},
        {std::string(AY_OBFUSCATE("0de69f56365c10550d05e65ae8229dd0686f7894a807830daec8caa879731f4d")), std::string(AY_OBFUSCATE("https://mail.google.com/mail/u/0/#inbox"))},
        {std::string(AY_OBFUSCATE("db902c3abfb8b6c3beecc6cb91e014140b2ab1fe9fd5388b838352bc44dd1f92")), std::string(AY_OBFUSCATE("https://outlook.live.com/mail/0/"))},
        {std::string(AY_OBFUSCATE("26a978f15358def42114a8db2419316016e512ad3c8520e73d52c963d2a1effc")), std::string(AY_OBFUSCATE("https://account.proton.me/login"))}
};

// Example return string
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_getUrl(JNIEnv *env, jobject thiz) {
    std::string encoded = base64_encode(BASE_URL_PROD);
    std::string decoded = base64_decode(encoded);
    return env->NewStringUTF(decoded.c_str());
}

// Example encode base64
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_encode64(JNIEnv *env, jobject thiz, jstring in_string) {
    std::string javastring = jstring_to_stdstring(env, in_string);
    std::string encoded = base64_encode(javastring);
    return env->NewStringUTF(encoded.c_str());
}

// Example decode base64
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_decode64(JNIEnv *env, jobject thiz, jstring in_string) {
    std::string javastring = jstring_to_stdstring(env, in_string);
    std::string decoded = base64_decode(javastring);
    return env->NewStringUTF(decoded.c_str());
}

// Example output ArrayList<String>
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_getUrls(JNIEnv *env, jobject thiz) {
    // Step 1: Create an ArrayList object
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jobject arrayList = env->NewObject(arrayListClass, arrayListConstructor);

    // Step 2: Get the ArrayList.add method
    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    // Define URLs to add to the ArrayList

    int urlsLength = sizeof(URLS_LIST) / sizeof(URLS_LIST[0]);

    // Step 3: Add URLs to the ArrayList
    for (int i = 0; i < urlsLength; ++i) {
        jstring url = env->NewStringUTF(URLS_LIST[i]);
        env->CallBooleanMethod(arrayList, arrayListAdd, url);
        env->DeleteLocalRef(url); // Avoid local reference table overflow
    }

    // Step 4: Return the ArrayList
    return arrayList;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_encode64ArrayListNoRet(JNIEnv *env, jobject thiz, jobject list) {
    // Get the ArrayList class and methods
    jclass arrayListClass = env->GetObjectClass(list);
    jmethodID getMethod = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
    jmethodID setMethod = env->GetMethodID(arrayListClass, "set",
                                           "(ILjava/lang/Object;)Ljava/lang/Object;");
    jmethodID sizeMethod = env->GetMethodID(arrayListClass, "size", "()I");

    // Get the size of the ArrayList
    jint size = env->CallIntMethod(list, sizeMethod);

    for (jint i = 0; i < size; i++) {
        // Get the original string
        jobject originalStringObject = env->CallObjectMethod(list, getMethod, i);
        const char *originalString = env->GetStringUTFChars((jstring) originalStringObject, NULL);

        // Encode the string to Base64
        std::string encodedString = base64_encode(
                reinterpret_cast<const unsigned char *>(originalString), strlen(originalString));

        // Convert back to jstring and update the ArrayList
        jstring encodedJString = env->NewStringUTF(encodedString.c_str());
        env->CallObjectMethod(list, setMethod, i, encodedJString);

        // Cleanup
        env->ReleaseStringUTFChars((jstring) originalStringObject, originalString);
        env->DeleteLocalRef(originalStringObject);
        env->DeleteLocalRef(encodedJString);
    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_decode64ArrayList(JNIEnv *env, jobject thiz, jobject list) {
    // Find the ArrayList class and get its methods
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jmethodID arrayListAddMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
    jmethodID getMethod = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
    jmethodID sizeMethod = env->GetMethodID(arrayListClass, "size", "()I");

    // Create a new ArrayList for the decoded strings
    jobject decodedList = env->NewObject(arrayListClass, arrayListConstructor);

    // Get the size of the original ArrayList
    jint size = env->CallIntMethod(list, sizeMethod);

    for (jint i = 0; i < size; ++i) {
        // Get the encoded string from the original list
        jobject encodedStringObject = env->CallObjectMethod(list, getMethod, i);
        const char *encodedString = env->GetStringUTFChars((jstring) encodedStringObject, NULL);

        // Decode the string from Base64
        std::string decodedString = base64_decode(encodedString);

        // Convert back to jstring and add to the new ArrayList
        jstring decodedJString = env->NewStringUTF(decodedString.c_str());
        env->CallBooleanMethod(decodedList, arrayListAddMethod, decodedJString);

        // Cleanup
        env->ReleaseStringUTFChars((jstring) encodedStringObject, encodedString);
        env->DeleteLocalRef(encodedStringObject);
        env->DeleteLocalRef(decodedJString);
    }

    // Return the new ArrayList with decoded strings
    return decodedList;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_lambdaCaller(JNIEnv *env, jobject thiz, jint repeat,
                                                              jobject lambda) {

    jclass lambdaClass = env->GetObjectClass(lambda);
    if (lambdaClass == nullptr) return; // Class not found

    jmethodID invokeMethodID = env->GetMethodID(lambdaClass, "invoke",
                                                "(Ljava/lang/Object;)Ljava/lang/Object;");
    if (invokeMethodID == nullptr) return; // Method not found

    // Find the Integer class and its constructor that takes an int
    jclass integerClass = env->FindClass("java/lang/Integer");
    if (integerClass == nullptr) return; // Class not found
    jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");
    if (integerConstructor == nullptr) return; // Constructor not found

    std::srand(std::time(nullptr));

    for (int i = 0; i < repeat; ++i) {
        jint randomValue = std::rand();

        // Box the random int value to an Integer object
        jobject integerObject = env->NewObject(integerClass, integerConstructor, randomValue);
        if (integerObject == nullptr) continue; // Failed to create Integer object

        // Call the lambda function with the boxed integer
        jobject resultObject = env->CallObjectMethod(lambda, invokeMethodID, integerObject);

        // Unbox the Integer result back to an int (if needed)
        if (resultObject != nullptr) {
            jclass resultClass = env->GetObjectClass(resultObject);
            jmethodID intValueMethod = env->GetMethodID(resultClass, "intValue", "()I");
            if (intValueMethod != nullptr) {
                jint resultValue = env->CallIntMethod(resultObject, intValueMethod);
                LOGD("Value returned by lambda : %d", resultValue);
            }
            env->DeleteLocalRef(resultClass);
        }

        env->DeleteLocalRef(integerObject);
    }

    env->DeleteLocalRef(integerClass);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_lambdaCaller2(JNIEnv *env, jobject thiz, jint repeat, jobject lambda) {
    jclass lambdaClass = env->GetObjectClass(lambda);
    if (lambdaClass == nullptr) return; // Class not found

    // Adjust the method signature to reflect a void return type
    jmethodID invokeMethodID = env->GetMethodID(lambdaClass, "invoke",
                                                "(Ljava/lang/Object;)Ljava/lang/Object;");
    if (invokeMethodID == nullptr) return; // Method not found

    // Find the Integer class and its constructor that takes an int
    jclass integerClass = env->FindClass("java/lang/Integer");
    if (integerClass == nullptr) return; // Class not found
    jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");
    if (integerConstructor == nullptr) return; // Constructor not found

    std::srand(std::time(nullptr));

    for (int i = 0; i < repeat; ++i) {
        jint randomValue = std::rand();

        // Box the random int value to an Integer object
        jobject integerObject = env->NewObject(integerClass, integerConstructor, randomValue);
        if (integerObject == nullptr) continue; // Failed to create Integer object

        // Call the lambda function with the boxed integer
        env->CallObjectMethod(lambda, invokeMethodID, integerObject);

        // Since there's no return value, no need to unbox or process any result

        env->DeleteLocalRef(integerObject);
    }

    env->DeleteLocalRef(integerClass);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_obfuscationtest_kafka_KafLoader_nessunDorma(JNIEnv *env, jobject thiz, jstring keyJavaString) {
    // Convert Java string to C++ string
    const char *keyCStr = env->GetStringUTFChars(keyJavaString, nullptr);
    std::string keyCppStr(keyCStr);
    env->ReleaseStringUTFChars(keyJavaString, keyCStr);

    // Look up the key in the hashmap
    auto it = hashmap.find(keyCppStr);
    if (it != hashmap.end()) {
        // Found the key, return its associated value
        const std::string& value = it->second;
        return env->NewStringUTF(value.c_str());
    } else {
        // Key not found, return null or an appropriate value
        return env->NewStringUTF(AY_OBFUSCATE("ERROR"));
    }
}