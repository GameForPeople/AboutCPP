#pragma once

#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	
	vector<int> buf(n, 1);

	for (const int& iter : lost)
	{
		buf[iter - 1] = 0;
	}
	
	for (const int& iter : reserve)
	{
		if (iter - 2 >= 0 && iter < n)
		{
			if (buf[iter - 1] == 0)
			{
				buf[iter - 1] = 1;
			}
			else if (buf[iter - 2] == 0)
			{
				buf[iter - 2] = 1;
			}
			else if (buf[iter] == 0)
			{
				buf[iter] = 1;
			}
		}
		else if (iter - 2 >= 0)
		{
			if (buf[iter - 1] == 0)
			{
				buf[iter - 1] = 1;
			}
			else if (buf[iter - 2] == 0)
			{
				buf[iter - 2] = 1;
			}
		}
		else if (iter < n)
		{
			if (buf[iter - 1] == 0)
			{
				buf[iter - 1] = 1;
			}
			else if (buf[iter] == 0)
			{
				buf[iter] = 1;
			}
		}
		else
		{
			if (buf[iter - 1] == 0)
			{
				buf[iter - 1] = 1;
			}
		}
	}

	int answer = 0;

	for (const int& iter : buf)
	{
		if (iter == 1)
			++answer;
	}

	return answer;
}