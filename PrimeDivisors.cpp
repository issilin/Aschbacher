// ConsoleApplication5.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <mpir.h>

#include <gmp.h>
#include "BigInteger.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

BigInteger factor(BigInteger n) {
	BigInteger r, t, u, v, e;

	t = 0;

	if (n % 2 == 0) return 2;
	r = sqrt(n);
	if (issquare(n)) {
		if (isprime(r)) return r;
		else return factor(r);
	}
	r++;
	u = 2 * r + 1;
	v = 1;        // start with possible candidates
	e = r * r - n;
	while (e != 0) {        // minimize the error term a la Gauss
		while (e < 0) {
			e += u;
			u += 2;
		}
		while (e > 0) {
			e -= v;
			v += 2;
		}
	}
	//    return (u+v-2)/2;		// either one will work
	return (u - v) / 2;
}


void factorization(vector<BigInteger> &result, BigInteger n) {
	BigInteger t;
	int i = 0;
	for (i = 0; !isprime(n); i++) {
		t = factor(n);
		if (t == 0) break;
		result.push_back(t);
		n /= t;
	}
	result.push_back(n);
}

int primeDivisors(vector<BigInteger> &result, char* charAlpha)
{
	BigInteger *alpha = new BigInteger(charAlpha);

	factorization(result, *alpha);

	return result.size();
}

#pragma warning(disable:4996)
extern "C" __declspec(dllexport) int slnq(char** & result, char* charAlpha)
{
	vector<BigInteger> answers;

	primeDivisors(answers, charAlpha);
	
	sort(answers.begin(), answers.end());

	int resultSize = answers.size();
	result = new char*[resultSize];
	string answer;
	for (int i = 0; i < resultSize; i++)
	{
		answer = getStringValue(answers[i]);
		result[i] = new char[answer.length()];
		strcpy(result[i], answer.c_str());
	}
	
	return resultSize;
}

extern "C" __declspec(dllexport) int test()
{
	return 1;
}