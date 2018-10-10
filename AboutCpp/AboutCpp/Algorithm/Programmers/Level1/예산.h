#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> d, int budget) {
	sort(d.begin(), d.end());
	
	int answer = 0;

	for (auto i : d)
	{
		if (budget >= i)
		{
			budget -= i;
			++answer;
		}
		else
		{
			break;
		}
	}

	return answer;
}
