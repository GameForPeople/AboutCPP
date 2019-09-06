#pragma once

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

namespace «¡∏∞≈Õ 
{
	int solution(std::vector<int> priorities, int location) {
		int answer = 0;
		int count = 0;

		std::queue<std::pair<int, int>> myQueue;
		std::priority_queue <int> myPriorityQueue;

		for (int i = 0; i < priorities.size(); i++) 
		{
			myQueue.emplace(std::make_pair(i, priorities[i]));
			myPriorityQueue.push(priorities[i]);
		}

		while (!myQueue.empty()) 
		{
			const auto[index, value] = myQueue.front();
			myQueue.pop();

			if (myPriorityQueue.top() == value)
			{
				myPriorityQueue.pop();
				count++;
				if (index == location) {
					answer = count;
					break;
				}
			}
			else 
			{
				myQueue.emplace(std::make_pair(index, value));
			}
		}
		return answer;
	}
}
