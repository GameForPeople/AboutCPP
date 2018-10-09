#pragma once

#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
	vector<vector<int>> answer = arr1;

	for (int i = 0; i < arr2.size(); ++i)
	{
		for (int j = 0; j < arr2[0].size(); ++j)
		{
			answer[i][j] += arr2[i][j];
		}
	}

	return answer;
}