@file:Suppress("SpellCheckingInspection", "FunctionName")

package com.example.obfuscationtest.kafka

object KafLoader {
    external fun getUrl(): String
    external fun encode(inString: String): String
    external fun decode(inString: String): String
    external fun getServerUrls(): ArrayList<String>
    external fun encodeArrayListWithoutReturn(list: ArrayList<String>)
    external fun decodeArrayList(list: ArrayList<String>): ArrayList<String>
    external fun lambdaCaller(repeat: Int, lambda: (random: Int) -> Int)
    external fun lambdaCaller2(repeat: Int, lambda: (random: Int) -> Unit)
    private external fun nessunDorma(key: String): String
    fun KAFKA(key : KafKey) : String {
        return nessunDorma(key.value)
    }
}