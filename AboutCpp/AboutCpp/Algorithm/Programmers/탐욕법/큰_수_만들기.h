#pragma once

#include <string>
#include <vector>

#include <iostream>

using namespace std;

string solution(string number, int k) {

	int removeNumber = 1;

	while (k > 0)
	{
		vector<int> buffer;
		string removeString = std::to_string(removeNumber);
		int removeCount = 0;

		for (int i = 0; i < number.size() - removeString.size() + 1; ++i)
		{
			if ( removeString.compare(removeString.size() - 1, i, number) == 0)
			{
				buffer.emplace_back(i);
				i += removeString.size() - 1;
			}
		}

		if (buffer.size() > 0) {
			for (int i = 0; i < buffer.size(); ++i)
			{
				if (k > 0)
				{
					number.erase(buffer[i - removeCount], removeString.size());
					--k;
					removeCount += removeString.size();
				}
				else
					break;
			}
		}

		++removeNumber;
	}

	return number;
}