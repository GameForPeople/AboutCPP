#pragma once

#include <string>
#include <vector>
#include <queue>

#include <algorithm>
#include <functional>

#include <iostream>

using namespace std;

void GetHeapValue(priority_queue<int, vector<int>, greater<int>>& InMinHeap, int& ReturnSmallValue)
{
	ReturnSmallValue = InMinHeap.top();
	InMinHeap.pop();
	return;
}

int solution(vector<int> scoville, int K) {

	//sort(scoville.begin(), scoville.end());	// n log n
	priority_queue<int, vector<int>, greater<int> > min_heap;

	for (auto iter = scoville.begin(); iter != scoville.end(); ++iter)
	{
		min_heap.push(*iter);
	}

	int		answer		{ 0 };
	int		smallValue	{ 0 };
	int		intBuffer	{ 0 };

	while (7)
	{
		GetHeapValue(min_heap, smallValue);

		if (smallValue > K)
		{
			break;
		}
		else
		{
			if (min_heap.empty())
			{
				answer = -1;
				break;
			}

			GetHeapValue(min_heap, intBuffer);

			intBuffer = smallValue + intBuffer * 2;

			++answer;
			min_heap.push(intBuffer);
		}
	}

	return answer;
}