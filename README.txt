This project contains a small example program to demonstrate two things:
 a) A C++ class implementation of a two sample compute kernels that are compiled for auto-vectorization.
    The auto-vectorization is made for a range of different target processors.
	The class implementation provides a run-time check for the actual processor capabilities, to
	offer the correct implementation through the virtual class API.
 b) A Java JNI wrapper, allowing these functions to be called from a Java application
The project was built with the Netbeans IDE. It contains two separated Netbeans projects:
A C++ Makefile project for the vectorized library, and a Java project for the JNI wrapping and a Java main.
