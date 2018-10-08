#pragma once

#include <string>
#include <vector>

using namespace std;

int solution(int num) {
	int answer = 0;
	long numBuffer = num;

	while (numBuffer != 1)
	{
		if (numBuffer % 2 == 0)
		{
			numBuffer /= 2;
		}
		else
		{
			numBuffer = numBuffer * 3 + 1;
		}

		++answer;

		if (answer >= 500)
		{
			answer = -1;
			break;
		}
	}

	return answer;
}