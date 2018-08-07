#pragma once

#include <string>
#include <vector>
#include <functional>

using namespace std;

long long sumIntermediateValues(int inBeginValue, int inEndValue)
{
	long long retSumValue{};
	for (int i = inBeginValue; i <= inEndValue; ++i) retSumValue += i;
	return retSumValue;
}

long long solution(int inIntFirst, int inIntSecond) {
	return (inIntFirst < inIntSecond) 
		? sumIntermediateValues(inIntFirst, inIntSecond)
		: sumIntermediateValues(inIntSecond, inIntFirst);
}

long long bestSolution(int a, int b) {
	long long answer = 0;
	if (a > b) a ^= b ^= a ^= b;
	answer = (long long)b * -~b / 2 - (long long)a * ~- a / 2;
	return answer;
}