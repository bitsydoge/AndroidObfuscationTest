# keep invoke for lambdaCaller and lambdaCaller2
-keepclassmembers class * implements kotlin.jvm.functions.Function1 {
    public java.lang.Object invoke(java.lang.Object);
}

-dontwarn com.google.errorprone.annotations.MustBeClosed