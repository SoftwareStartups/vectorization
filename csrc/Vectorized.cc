#include <iostream>
#include <cassert>
#include <cstring>

#include "Vectorized.h"

VectorizedFactory::VectorizedFactory() : bestOffer(0), bestCandidate(NULL) {
#ifdef DEBUG
    std::cout << "Factory constructed" << std::endl;
#endif
}

// The enclosed singleton object ensures that its constructor is invoked for initialization,
// definitely before the constructors of the vectorized-specific objects start doing register()
VectorizedFactory& VectorizedFactory::single() {
    static VectorizedFactory me;
    return me;
}

// The implementations with auto-vectorization register (announce) themselves through this call
void VectorizedFactory::registr(unsigned int priority, Vectorized* vectorizeCandidate) {
    VectorizedFactory& vf = single();

#ifdef DEBUG
    std::cout << "register: " << priority << std::endl;
#endif
    if (priority > vf.bestOffer || !vf.bestCandidate) {
        vf.bestOffer = priority;
        vf.bestCandidate = vectorizeCandidate;
    }
}

// Get best available vectorized implementation at runtime
class Vectorized&
VectorizedFactory::get() {
    VectorizedFactory& vf = single();

    assert(vf.bestCandidate);
    return *vf.bestCandidate;
}

// When any simd-specific subclass of Vectorized is constructed, we register it in the factory
Vectorized::Vectorized(unsigned int prio, const char* simdTypeName) {
    if (haveSimdType(simdTypeName))
		VectorizedFactory::registr(prio, this);
}

// test for availability of the SIMD vector type as requested by this specific compile job
bool
Vectorized::haveSimdType(const char* simdTypeName) {
#if _MSC_FULL_VER >= 160040219 || __GNUC__ >= 4

        // MS Visual Studio 2010 SP1 or later
        // Checking for AVX requires 3 things:
        // 1) CPUID indicates that the OS uses XSAVE and XRSTORE
        //     instructions (allowing saving YMM registers on context
        //     switch)
        // 2) CPUID indicates support for AVX
        // 3) XGETBV indicates the AVX registers will be saved and
        //     restored on context switch
        //
        // Note that XGETBV is only available on 686 or later CPUs, so
        // the instruction needs to be conditionally run.

        // http://stackoverflow.com/questions/6121792/how-to-check-if-a-cpu-supports-the-sse3-instruction-set
        // http://insufficientlycomplicated.wordpress.com/2011/11/07/detecting-intel-advanced-vector-extensions-avx-in-visual-studio/
        // http://blogs.msdn.com/b/vcblog/archive/2014/02/28/avx2-support-in-visual-studio-c-compiler.aspx

        int cpuInfo[4];
        __cpuid(cpuInfo, 0);

#ifdef DEBUG
        std::cout << "haveSimdType?" << simdTypeName << std::endl;
#endif

        int nIds = cpuInfo[0];
        if (!strcmp(simdTypeName, "sse2") || nIds < 1)
            return true; // assume we build a 64-bit application, then sse2 is guaranteed

        // nIds >= 1
        __cpuid(cpuInfo, 1);
 
        if (!strcmp(simdTypeName, "sse3"))
            return (cpuInfo[2] & 1) != 0;
        if (!strcmp(simdTypeName, "ssse3"))
            return (cpuInfo[2] & (1 << 9)) != 0;
        if (!strcmp(simdTypeName, "sse41"))
            return (cpuInfo[2] & (1 << 19)) != 0;
        if (!strcmp(simdTypeName, "sse42"))
            return (cpuInfo[2] & (1 << 20)) != 0;

        bool osUsesXSAVE_XRSTORE = cpuInfo[2] & (1 << 27) || false;
        bool cpuAVXSuport = cpuInfo[2] & (1 << 28) || false;

#ifdef DEBUG
        std::cout << "check avx: osSaverestore=" << osUsesXSAVE_XRSTORE << ", cpuAVX=" << cpuAVXSuport << std::endl;
#endif
 
        if (osUsesXSAVE_XRSTORE && cpuAVXSuport)
        {
            // Check if the OS will save the YMM registers
            // Note that 'xgetbv' is an instruction that is available in avx-capable CPUs only
            unsigned long long xcrFeatureMask = _xgetbv(0);
            bool avxSupported = (xcrFeatureMask & 0x6) || false;
            
#ifdef DEBUG
            std::cout << "   check avx: _xgetbv=" << avxSupported << std::endl;
#endif

            if (avxSupported && !strcmp(simdTypeName, "avx"))
                return true;
            if (avxSupported && !strcmp(simdTypeName, "avx2") && nIds >= 7) {
                __cpuid(cpuInfo, 7);
                return (cpuInfo[1] & (1 << 5)) != 0;
            }
        }
        // probably we will not arrive here...
        return false;
#else
        // Hmm... run-time check not implemented. Default is that only 'sse2' is avail
        return !strcmp(simdTypeName, "sse2");
#endif
}

#ifdef __GNUC__
void
Vectorized::__cpuid(int CPUInfo[4],int InfoType) {
        __asm__ __volatile__ (
            "cpuid":
            "=a" (CPUInfo[0]),
            "=b" (CPUInfo[1]),
            "=c" (CPUInfo[2]),
            "=d" (CPUInfo[3]) :
            "a" (InfoType), "c" (0)
            );
}
unsigned long long
Vectorized::_xgetbv(unsigned int index) {
        unsigned int eax, edx;
        __asm__ __volatile__("xgetbv" : "=a"(eax), "=d"(edx) : "c"(index));
        return ((unsigned long long)edx << 32) | eax;
}
#endif
