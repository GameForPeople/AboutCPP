#pragma once

#include <string>
#include <vector>

#include <algorithm>

using namespace std;


class NodeManager
{
	vector<string> idCont;

public:
	bool AddId(const string& InString)
	{
		int syncBuffer;

		for (auto iter : idCont)
		{
			syncBuffer = 0;

			// 나중에는 substr! 쓰어야 될듯!
			for (int i = 0; i < iter.size(); ++i)
			{
				if (iter[i] == InString[i])
				{
					++syncBuffer;

					if (syncBuffer == iter.size())
					{
						return false;
					}
				}
				else {
					break;
				}
			}
		}

		idCont.emplace_back(InString);
		return true;
	}
};


bool solution(vector<string> phone_book) {
	NodeManager nodeManager;

	sort(phone_book.begin(), phone_book.end(), [](const string& a, const string& b) -> bool
	{
		if (a.compare(b) < 0) return true;
		else return false;
	});

	bool answer = true;

	for (auto iter : phone_book)
	{
		if (nodeManager.AddId(iter))
		{
			continue;
		}
		else
		{
			answer = false;
			break;
		}
	}
	
	return answer;
}

bool otherSolution(vector<string> phone_book) {
	bool answer = true;

	sort(phone_book.begin(), phone_book.end());

	for (int i = 0, LOOP_COUNT = phone_book.size() - 1; i < LOOP_COUNT; ++i)
	{
		if (phone_book[i] == phone_book[(__int64)i + 1].substr(0, phone_book[i].size()))
		{
			answer = false;
		}
	}
	return answer;
}