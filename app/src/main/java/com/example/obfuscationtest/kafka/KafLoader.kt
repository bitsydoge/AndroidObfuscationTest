@file:Suppress("SpellCheckingInspection", "FunctionName", "NOTHING_TO_INLINE")

package com.example.obfuscationtest.kafka

import android.util.Base64
import kotlin.experimental.xor

object KafLoader {
//    // Strings Test
//    external fun getUrl(): String
//    external fun getUrls(): ArrayList<String>
//
//    // Encoder / Decoder Base64
//    external fun encode64(inString: String): String
//    external fun decode64(inString: String): String
//    external fun encode64ArrayListNoRet(list: ArrayList<String>)
//    external fun decode64ArrayList(list: ArrayList<String>): ArrayList<String>
//
//    // Lambda Test
//    external fun lambdaCaller(repeat: Int, lambda: (random: Int) -> Int)
//    external fun lambdaCaller2(repeat: Int, lambda: (random: Int) -> Unit)

    // Hashmap getter
    external fun nessunDorma(key: String): ByteArray
    inline fun KAFKA(key : KafKey) : String {
        val string = Base64.decode(String(nessunDorma(key.value)), Base64.DEFAULT)
        for (i in string.indices) {
            string[i] = string[i] xor (0xca9d9716774333 shr ((i % 8) * 8) and 0xFF).toByte()
        }
        return String(string)
    }
}