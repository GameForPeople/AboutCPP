#pragma once

// not work!

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

int solution(vector<int> citations) {

	if (citations.size() == 1)
	{
		if (citations[0] == 1)
			return 1;
		else return 0;
	}

	sort(citations.begin(), citations.end(), greater<int>());

	for (const auto& i : citations)
	{
		std::cout << i << "  ";
	}

	int answer = 0;

	for (int i = 0; i < citations.size() - 1; ++i)
	{
		if (citations[i] >= i + 1 && citations[i + 1] <= i + 1)
		{
				answer = i + 1;
				break;
		}
	}

	if (answer == 0)
	{
		if (citations[citations.size() -1 ] == 0)
			return 0;
		else if (citations[citations.size() - 1] == 1)
			return 1;
	}
	else 
		return answer;
}