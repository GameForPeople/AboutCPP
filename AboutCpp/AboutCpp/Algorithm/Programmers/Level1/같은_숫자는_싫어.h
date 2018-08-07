#pragma once

#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr)
{
	int nowValue{ -1 };

	vector<int> answer;
	
	for (auto i : arr) {
		if (nowValue != i) {
			answer.emplace_back(i);
			nowValue = i;
		}
	}
	
	return answer;
}