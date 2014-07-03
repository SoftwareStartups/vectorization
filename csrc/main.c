#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "VectorizedCWrapper.h"


int main(int argc, char *argv[])
{
    const unsigned int n = 512;
	printf("main is awake\n");

    // data initialization
    float *a = malloc( n * sizeof(float));
    for (unsigned int i = 0; i < n; i++)
        a[i] = 1.0f + (i & 0x0f);

	
    // do my work
	const char *version = vectorizedVersionName();
	printf("version used: %s\n", version);

    float r1 = vectorizedInproduct(n, a, a);
    float r2 = vectorizedAverage(n, a);
	printf("result = %g, %g\n", r1, r2);
	
	// done
    free(a);

    return 0;
}
