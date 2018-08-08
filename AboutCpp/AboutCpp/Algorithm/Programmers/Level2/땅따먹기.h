#pragma once

#include <iostream>
#include <vector>

#include <algorithm>
using namespace std;

int Max(int a, int b, int c) {
	return
		a > (b > c ? b : c)
		? a
		: (b > c ? b : c);
}

int solution(vector<vector<int>> land)
{
	int answer = 0;
	int n = land.size();

	for (int i = 0; i<n - 1; i++)
	{
		land[i + 1][0] += Max( land[i][1], land[i][2], land[i][3] );
		land[i + 1][1] += Max( land[i][0], land[i][2], land[i][3] );
		land[i + 1][2] += Max( land[i][0], land[i][1], land[i][3] );
		land[i + 1][3] += Max( land[i][0], land[i][1], land[i][2] );
	}

	sort(land[n - 1].begin(), land[n - 1].end());

	return land[n - 1][3];
}