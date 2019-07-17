#pragma once

#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

namespace 탑
{
	vector<int> solution(vector<int> heights)
	{
		stack<pair<int, int>> myStack;
		//myQueue.push(0);
		{
			int tempIndex = 0; // heights.size();
			for (auto heightIter = heights.begin(); heightIter != heights.end(); ++heightIter)
			{
				myStack.emplace(++tempIndex, *heightIter);
			}
		}

		vector<int> answer;
		vector<pair<int, int>> readyCont;
		answer.resize(heights.size(), 0);
		readyCont.reserve(heights.size());
		for (int i = 0, heightSize = heights.size(); i < heightSize; ++i)
		{
			auto compNode = myStack.top();

			for (auto iter = readyCont.begin(); iter != readyCont.end();)
			{
				if (iter->second < compNode.second)
				{
					// 받았어!
					answer[iter->first - 1] = compNode.first;
					iter = readyCont.erase(iter);
				}
				else ++iter;
			}
			readyCont.emplace_back(compNode);
			myStack.pop();
		}

		for (auto readyNode : readyCont)
		{
			answer[readyNode.first - 1] = 0;
		}

		return answer;
	}
}