
#include "stdafx.h"
#include "BigInteger.h"
#include <vector>

void find(vector<BigInteger> &result, BigInteger n)
{
	BigInteger null = 0;
	BigInteger temp;
	for (BigInteger i = 1; i < n; i++)
	{
		temp = Xor(i, n);
		temp = temp | n;
		if (temp == n)
		{
			result.push_back(i);
		}
	}
}

int stabilizersOfSubspace(vector<BigInteger> &result, char* charN)
{
	BigInteger *alpha = new BigInteger(charN);

	find(result, *alpha);

	return result.size();
}

#pragma warning(disable:4996)
extern "C" __declspec(dllexport) int findStabilizers(char** & result, char* charN)
{
	vector<BigInteger> answer;

	stabilizersOfSubspace(answer, charN);
	
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