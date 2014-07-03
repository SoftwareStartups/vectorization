CC     = gcc -std=c99
CXX    = g++ -std=c++11
CXXFLAGS = -g -funsafe-math-optimizations -Wall

LIBSRCS = VectorizedCWrapper.h Vectorized.h VectorizedCWrapper.cc Vectorized.cc VectorizedImpl.cc
LIBOBJS = VectorizedCWrapper.o Vectorized.o Vectorized_sse2.o Vectorized_ssse3.o Vectorized_avx.o Vectorized_avx2.o

.PHONY: clean
.SUFFIXES: .o .c .cc .h

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

Vectorized.dll : $(LIBOBJS)
	$(CXX) -shared -o $@ $+ -Wl,--out-implib,Vectorized_dll.a
	
${LIBOBJS}: Vectorized.h

clean:
	rm -f inproduct inproduct.exe Vectorized.dll Vectorized_dll.a main.o ${LIBOBJS}

vectorized.tar: Makefile main.c $(LIBSRCS)
	tar -cf $@ $^
