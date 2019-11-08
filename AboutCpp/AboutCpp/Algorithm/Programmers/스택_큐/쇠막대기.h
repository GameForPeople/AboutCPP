#pragma once

#include <string>
#include <vector>

using namespace std;

int solution(string arrangement) {
	int answer{0};
	int leftCount{0};

	for (int i = 0; i < arrangement.size(); ++i)
	{
		if (arrangement[i] == '(')
		{
			if (arrangement[i + 1] == ')')
			{
				answer += leftCount;
				++i;
			}
			else
			{
				++leftCount;
			}
		}
		else
		{
			--leftCount;
			++answer;
		}
	}
	
	return answer;
}