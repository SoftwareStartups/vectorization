#include "VectorizedCWrapper.h"
#include "Vectorized.h"

extern "C" {
const char * __stdcall vectorizedVersionName() {
    Vectorized& veclib = VectorizedFactory::get();

    return veclib.versionName();
}

float __stdcall vectorizedInproduct( unsigned int n, const float *a, const float *b) {
    Vectorized& veclib = VectorizedFactory::get();

    return veclib.inproduct(n, a, a);
}

float __stdcall vectorizedAverage( unsigned int n, const float *a) {
    Vectorized& veclib = VectorizedFactory::get();

	return veclib.average(n, a);
}

}
