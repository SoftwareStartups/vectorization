This project contains a small example program to demonstrate two things:
 a) A C++ class implementation of a two sample compute kernels that are compiled for auto-vectorization.
    The auto-vectorization is made for a range of different target processors.
The class implementation provides a run-time check for the actual processor capabilities, to
offer the correct implementation through the virtual class API.
 b) A Java JNI wrapper, allowing these functions to be called from a Java application
The project was built with the Netbeans IDE. It contains two separated Netbeans projects:
 C++ Makefile project for the vectorized library, and a Java project for the JNI wrapping and a Java main.

== Still ToDo ==
Netbeans as IDE should be capable of packaging the native dll inside the java .jar file. That way, the Java program becomes portable, without the hassle of seperately installing the dll somewhere and setting execution environments so that the java program can find this dll.

== setup and tool installation on Windows (-8) ==
Installed MinGW-w64 with win-builds as described on: http://win-builds.org/1.4.0/msys-cygwin.html
(Note: indeed install just the base MSYS first, since installing all from mingw-get gives a W32-bit enviroment only.)

Install Oracle Java SE 8u5 from http://www.oracle.com/technetwork/java/javase/downloads/index.html
Installed netbeans Java SE version: https://netbeans.org/downloads/index.html

Installed the netbeans C/C++ plugin with MinGW support: https://netbeans.org/community/releases/80/cpp-setup-instructions.html
Setup the PATH environment to point to MinGW according to: http://www.itechtics.com/customize-windows-environment-variables/

== JNI performance tuning considerations ==
Depending on the native functionas and type of arguments, passing arrays might create significant overhead:
the JNI interface will easily revert to making copies of ther arrays.
See http://elliotth.blogspot.nl/2007/03/optimizing-jni-array-access.html for considerations to choose between
GetByteArrayRegion (copying sub-ranges) versus GetByteArrayElements (maybe avoid copying).
However, for compute kernels, we typically would prefer GetPrimitiveArrayCritical,
see: http://docs.oracle.com/javase/6/docs/technotes/guides/jni/spec/functions.html#GetPrimitiveArrayCritical

Written by Jos van Eijndhoven
