// This source file will be compiled into multiple object files,
// each time compiled for auto-vectorization with different target architectures.
// The build system shall create different names for these objects, to be linked later.
// The build environment is supposed to provided two #defines to specialize these objects:
//   1. The vector type as identifier, mainly intended as argument to GCCs __builtin_cpu_supports()
//   2. A numeric measure (unsigned int) to compare its desirability, now chosen as 'year*100+month'
//      describing the Intel introduction date, assuming we always prefer the more recent versions
//

// generic class interfacing all vector-specific versions
#include <iostream>
#include "Vectorized.h"

// Specific version compiled once for each vectorization type
class CLASSNAME(VectorizedImpl,VECTORIZE_TYPE) : public Vectorized {
public:
    // constructor should register this compiled version if supported by the CPU (at program startup time)
    CLASSNAME(VectorizedImpl,VECTORIZE_TYPE)() : Vectorized(VECTORIZE_PRIO, VECNAME(VECTORIZE_TYPE)) {}
 
	// support to query which vectorized version is used
	virtual const char *versionName() const {
		return VECNAME(VECTORIZE_TYPE);
	}
	
    // Implementation of the compute kernel functions that need auto-vectorization
    virtual float inproduct( unsigned int n, const float *a, const float *b) const {
        float sum = 0.0f;
        for (unsigned int i=0; i<n; i++)
            sum += a[i] * b[i];

        return sum;
    }

    virtual float average( unsigned int n, const float *a) const {
        if (n == 0)
            return 0.0f;

        float sum = 0.0f;
        for (unsigned int i=0; i<n; i++)
            sum += a[i];

        return sum / n;
    }
};
static CLASSNAME(VectorizedImpl,VECTORIZE_TYPE) vectorizeImplSpecific;
// This instance forces execution of my constructor at program initialization time to do registration
// Note that we have different object files with this same name, all declared static
