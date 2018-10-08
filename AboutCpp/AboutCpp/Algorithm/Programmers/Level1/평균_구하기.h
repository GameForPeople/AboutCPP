#pragma once

#include <string>
#include <vector>
#include <numeric>

using namespace std;

double solution(vector<int> arr) {	
	double answer = 0;

	for (const auto &i : arr)
	{
		answer += i;
	}

	answer /= arr.size();

	return answer;
}

double bestSolution(vector<int> arr) {
	double answer = accumulate(arr.begin(), arr.end(), 0);

	return answer / arr.size();
}