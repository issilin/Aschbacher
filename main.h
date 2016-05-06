
#include <vector>
#include "BigInteger.h"

int primeDivisors(vector<BigInteger> &result, char* charAlpha);
int stabilizersOfSubspace(vector<BigInteger> &result, char* charAlpha);
int stabilizerOfDecomposition(vector<BigInteger> &result, char* charN);

extern "C" __declspec(dllexport) int slnq(char** & result, char* charAlpha);
extern "C" __declspec(dllexport) int findStabilizers(char** & result, char* n);
extern "C" __declspec(dllexport) int findStabilizerOfDecomposition(char** & result, char* n);
extern "C" __declspec(dllexport) int getSlnq(char** & result, char* charAlpha, char* charN, char* q);

extern "C" __declspec(dllexport) int test();

