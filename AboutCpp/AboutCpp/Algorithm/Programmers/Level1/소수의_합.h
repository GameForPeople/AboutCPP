#pragma once
/*
	소수의 합 (https://programmers.co.kr/learn/courses/30/lessons/14406)
		- 2부터 N까지의 모든 소수의 합을 구하세요.

		#0. N은 2이상, 10,000,000이하
		#1. 효율성 테스트, 1초 미만으로 제한

		#2. 본 솔루션은 에라토스테네스의 체 활용.
*/
#include <vector>
#include <cmath>

using namespace std;

long long solution(int N) {
	vector<bool> bitCont(N+1, true);

	{//block for limit "newIndex" scope!
		int newIndex;

		for (int i = 3; i <= sqrt(N); i += 2)
		{
			newIndex = i + i;

			while (newIndex < N + 1)
			{
				bitCont[newIndex] = false;
				newIndex += i;
			}
		}
	}

	long long answer = 2;

	for (int i = 3; i < N + 1; i += 2)
	{
		if (bitCont[i]) answer += i;
	}

	return answer;
}