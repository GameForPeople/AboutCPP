#pragma once

#include <string>
#include <vector>
#include <functional>

using namespace std;

long long sumBetweenValues(int inLowValue, int inHighValue) 
{
	long long retSumValue{};
	for (int i = inLowValue; i <= inHighValue; ++i) retSumValue += i;
	return retSumValue;
}

long long solution(int inIntFirst, int inIntSecond) {
	return (inIntFirst < inIntSecond) 
		? sumBetweenValues(inIntFirst, inIntSecond)
		: sumBetweenValues(inIntSecond, inIntFirst);
}