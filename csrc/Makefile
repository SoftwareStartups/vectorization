JDK    = '/c/Program Files/Java/jdk1.8.0_05'
CC     = gcc -std=c99
CXX    = g++ -std=c++11
CXXFLAGS = -g -funsafe-math-optimizations -Wall

LIBHDRS = Vectorized.h VectorizedCWrapper.h com_vectorfabrics_vectorizeLib.h
LIBSRCS = VectorizedJNIWrapper.cc VectorizedCWrapper.cc Vectorized.cc VectorizedImpl.cc
LIBOBJS = Vectorized.o Vectorized_sse2.o Vectorized_ssse3.o Vectorized_avx.o Vectorized_avx2.o

.PHONY: clean all
.SUFFIXES: .o .c .cc .h

all: inproduct VectorizedJNI.dll
	
inproduct: main.o Vectorized.dll
	$(CXX) -o $@ $+

main.o: main.c VectorizedCWrapper.h
	$(CC) $(CXXFLAGS) -c -o $@ $<
	
VectorizedCWrapper.o: VectorizedCWrapper.cc VectorizedCWrapper.h
	$(CXX) $(CXXFLAGS) -DBUILDING_DLL -c -o $@ $<
	
Vectorized.o: Vectorized.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Vectorized_sse2.o : VectorizedImpl.cc
	$(CXX) $(CXXFLAGS) -msse2 -DVECTORIZE_TYPE=sse2 -DVECTORIZE_PRIO=200401 -c -o $@ $<

Vectorized_ssse3.o : VectorizedImpl.cc
	$(CXX) $(CXXFLAGS) -mssse3 -DVECTORIZE_TYPE=ssse3 -DVECTORIZE_PRIO=200606 -c -o $@ $<

Vectorized_avx.o : VectorizedImpl.cc
	$(CXX) $(CXXFLAGS) -mavx -DVECTORIZE_TYPE=avx -DVECTORIZE_PRIO=201101  -c -o $@ $<

Vectorized_avx2.o : VectorizedImpl.cc
	$(CXX) $(CXXFLAGS) -mavx2 -DVECTORIZE_TYPE=avx2 -DVECTORIZE_PRIO=201304  -c -o $@ $<

Vectorized.dll : VectorizedCWrapper.o $(LIBOBJS)
	$(CXX) -shared -o $@ $+ -Wl,--out-implib,Vectorized_dll.a

com_vectorfabrics_vectorizeLib.h: ../jsrc/JavaNativeVector/src/com/vectorfabrics/vectorizeLib.java
	$(JDK)/bin/javah -verbose -classpath ../jsrc/JavaNativeVector/src com.vectorfabrics.vectorizeLib

VectorizedJNIWrapper.o: VectorizedJNIWrapper.cc com_vectorfabrics_vectorizeLib.h
	$(CXX) $(CXXFLAGS) -I $(JDK)/include -I $(JDK)/include/win32 -DBUILDING_DLL -c -o $@ $<
		
VectorizedJNI.dll : VectorizedJNIWrapper.o $(LIBOBJS)
	$(CXX) -shared -o $@ $+ -Wl,--out-implib,VectorizedJNI_dll.a -static
	
${LIBOBJS}: Vectorized.h

clean:
	rm -f inproduct inproduct.exe Vectorized*.dll Vectorized*dll.a main.o Vectorized*.o com_vectorfabrics_vectorizeLib.h

vectorized.tar: Makefile main.c $(LIBSRCS) $(LIBHDRS)
	tar -cf $@ $^
