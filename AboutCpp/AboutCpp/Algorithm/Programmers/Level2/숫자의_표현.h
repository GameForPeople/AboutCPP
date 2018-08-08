#pragma once

#include <string>
#include <vector>

#include<iostream>
#include<cmath>

using namespace std;

int solution(int n) {
	int answer = 1;
	int sum{};
	int i{};
	int k{};

	for (i = 1; i <= (n / 2 + 1); i++)
	{
		sum = 0;
		for (k = i; k <= (n / 2 + 1); k++)
		{
			sum += k;

			if (sum > n)
				break;
			else if (sum == n)
			{
				answer++; 
				break;
			}
		}
	}
	return answer;
}


int bestSolution(int testCase)
{
	int answer = 0;
	int to = ceil((-1 + sqrt(1 + 8 * testCase)) / 2);
	for (int i = 1; i <= to; i++)
	{
		if (i % 2 == 1 && testCase%i == 0)
		{
			answer++;
		}
		else if (i % 2 == 0 && (testCase%i) == (i / 2))
		{
			answer++;
		}
	}

	return answer;
}