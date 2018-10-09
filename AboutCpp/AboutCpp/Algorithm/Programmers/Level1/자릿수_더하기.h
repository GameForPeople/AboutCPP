#pragma once

#include <iostream>

using namespace std;
int solution(int n)
{
	int answer{};
	int nBuffer = n;

	for (int i = 1; n / i > 0; i *= 10) {
		answer += nBuffer % 10;
		nBuffer /= 10;
	}

	return answer;
}