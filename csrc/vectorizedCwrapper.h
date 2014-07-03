// For creating dll's that allow interlanguage linking, see:
// http://www.mingw.org/wiki/sampleDLL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_DLL
// annotate the functions for exporting into the dll
#define SPEC_DLL __declspec(dllexport)
#else
// annotate the functions for importing from a dll
#define SPEC_DLL __declspec(dllimport)
#endif

const char * __stdcall  SPEC_DLL vectorizedVersionName();
float __stdcall SPEC_DLL vectorizedInproduct( unsigned int n, const float *a, const float *b);
float __stdcall SPEC_DLL vectorizedAverage( unsigned int n, const float *a);

#ifdef __cplusplus
}
#endif
