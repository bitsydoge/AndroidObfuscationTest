package com.example.obfuscationtest

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.style.TextDecoration
import androidx.compose.ui.unit.dp
import com.example.obfuscationtest.kafka.KafKeys
import com.example.obfuscationtest.kafka.KafLoader.decode
import com.example.obfuscationtest.kafka.KafLoader.decodeArrayList
import com.example.obfuscationtest.kafka.KafLoader.encode
import com.example.obfuscationtest.kafka.KafLoader.encodeArrayListWithoutReturn
import com.example.obfuscationtest.kafka.KafLoader.KAFKA
import com.example.obfuscationtest.kafka.KafLoader.getServerUrls
import com.example.obfuscationtest.kafka.KafLoader.getUrl
import com.example.obfuscationtest.ui.theme.ObfuscationTestTheme

class MainActivity : ComponentActivity() {
    init {
        System.loadLibrary("kafka")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            ObfuscationTestTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Column(modifier = Modifier.verticalScroll(rememberScrollState())) {
                        NewExample("encode()", false)
                        Text(encode(getUrl()))
                        NewExample("decode()")
                        Text(decode(encode(getUrl())))
                        NewExample("getServerUrls()")
                        for (url in getServerUrls()){
                            Text(url)
                        }
                        NewExample("encodeArrayListWithoutReturn()")
                        val myRef = getServerUrls()
                        encodeArrayListWithoutReturn(myRef)
                        for (string in myRef) {
                            Text(string)
                        }
                        NewExample("decodeArrayList()")
                        val newArray = decodeArrayList(myRef)
                        for (string in newArray)
                            Text(string)
                        NewExample("lambdaCaller()")
//                        val list = ArrayList<Int>()
//                        lambdaCaller(5) { random ->
//                            list.add(random)
//                            random
//                        }
//                        lambdaCaller2(20) { random -> list.add(random) }
//                        list.forEach{ Text(it.toString()) }
                        NewExample("get()")
                        Text(KAFKA(KafKeys.GOOGLE))
                        Text(KAFKA(KafKeys.GMAIL))
                        Text(KAFKA(KafKeys.OUTLOOK))
                        Text(KAFKA(KafKeys.PROTON))
                    }
                }
            }
        }
    }

    @Composable
    private fun NewExample(text: String, separator: Boolean = true) {
        if(separator) Spacer(modifier = Modifier.size(8.dp))
        Text(text, style = TextStyle(textDecoration = TextDecoration.Underline))
    }
}