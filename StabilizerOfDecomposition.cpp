
#include "stdafx.h"
#include "BigInteger.h"
#include <vector>

void findPowerOfTwo(vector<BigInteger> &result, BigInteger n)
{
	BigInteger i = BigInteger(2);
	while (i < n)
	{
		if (n % i == 0)
		{
			result.push_back(i);
		}

		i = i << 1;
	}
}

int stabilizerOfDecomposition(vector<BigInteger> &result, char* charN)
{
	BigInteger *n = new BigInteger(charN);

	findPowerOfTwo(result, *n);

	return result.size();
}

#pragma warning(disable:4996)
extern "C" __declspec(dllexport) int findStabilizerOfDecomposition(char** & result, char* charN)
{
	vector<BigInteger> answer;

	stabilizerOfDecomposition(answer, charN);

	int resultSize = answer.size();

	result = new char*[resultSize];
	string stabilizer;
	for (int i = 0; i < resultSize; i++)
	{
		stabilizer = getStringValue(answer[i]);
		result[i] = new char[stabilizer.length()];
		strcpy(result[i], stabilizer.c_str());
	}

	return resultSize;
}

