#pragma once

#include <string>
#include <vector>

using namespace std;

bool solution(int x) {
	bool answer = true;
	int buffer = x;

	int sumValue{ 0 };

	while (buffer > 0)
	{
		sumValue += buffer % 10;
		buffer /= 10;
	}

	if (x % sumValue == 0)
		return true;
	else
		return false;
}

bool bsetSolution(int x) {
	bool answer = true;
	int nTemp = x;
	int nSum = 0;
	while (nTemp > 0)
	{
		nSum += nTemp % 10;
		nTemp /= 10;
	}

	return x % nSum == 0 ? true : false;
}
