
#include "stdafx.h"
#include "BigInteger.h"
#include <vector>
#include "main.h"
#include <algorithm>

#include <stdio.h>
#include <mpir.h>

#include <gmp.h>
#include <string>

#pragma warning(disable:4996)
extern "C" __declspec(dllexport) int getSlnq(char** & result, char* charAlpha, char* charN, char* q)
{
	BigInteger n = BigInteger(charN);

	vector<BigInteger> answer;
	
	if (n < 2)
	{
		return 0;
	}

	primeDivisors(answer, charAlpha);
	stabilizersOfSubspace(answer, charN);
	stabilizerOfDecomposition(answer, charN);

	vector<BigInteger> ::iterator it;

	sort(answer.begin(), answer.end());
	it = unique(answer.begin(), answer.end());
	answer.resize(it - answer.begin());

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