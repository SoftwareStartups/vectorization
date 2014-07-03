
// a few defines to construct names and identifiers from comopiler-argument defined values
#define IDCATENATE(a,b) a ## b
#define CLASSNAME(prefix,vectype) IDCATENATE( prefix, vectype)
#define TOSTRING(vectype) #vectype
#define VECNAME(vectype) TOSTRING(vectype)

// class that specifies the interface for (a couple of) functions that got implemented with auto-vectorization
class Vectorized {
public:
	virtual const char *versionName() const = 0;
    virtual float inproduct( unsigned int n, const float *a, const float *b) const = 0;
    virtual float average( unsigned int n, const float *a) const = 0;
	Vectorized( unsigned int prio, const char *simdTypeName);

private:
    static bool haveSimdType(const char* simdTypeName);

#if __GNUC__
private:
    static void __cpuid(int CPUInfo[4],int InfoType);
    static inline unsigned long long _xgetbv(unsigned int index);
#endif
};

// helper class that will deliver at runtime a properly selected 'Vectorized' class object.
class VectorizedFactory {
public:
    static void registr(unsigned int priority, Vectorized *vectorizedCandidate);
    static class Vectorized& get();

private:
    unsigned int bestOffer;
    class Vectorized* bestCandidate;

    VectorizedFactory();
    VectorizedFactory& operator=(const VectorizedFactory&) = delete;
    static VectorizedFactory& single();
};
