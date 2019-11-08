#pragma once

#include <string>
#include <vector>

using namespace std;

vector<long long> solution(int x, int n) {
	vector<long long> answer;

	int buffer = x;

	for (int i = 0; i < n; ++i)
	{
		answer.emplace_back(x);

		x += buffer;
	}

	return answer;
}
