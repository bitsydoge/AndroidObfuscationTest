@file:Suppress("SpellCheckingInspection", "FunctionName")

package com.example.obfuscationtest.kafka

object KafLoader {
    // Strings Test
    external fun getUrl(): String
    external fun getUrls(): ArrayList<String>

    // Encoder / Decoder Base64
    external fun encode64(inString: String): String
    external fun decode64(inString: String): String
    external fun encode64ArrayListNoRet(list: ArrayList<String>)
    external fun decode64ArrayList(list: ArrayList<String>): ArrayList<String>

    // Lambda Test
    external fun lambdaCaller(repeat: Int, lambda: (random: Int) -> Int)
    external fun lambdaCaller2(repeat: Int, lambda: (random: Int) -> Unit)

    // Hashmap getter
    private external fun nessunDorma(key: String): String
    fun KAFKA(key : KafKey) : String {
        return nessunDorma(key.value)
    }
}