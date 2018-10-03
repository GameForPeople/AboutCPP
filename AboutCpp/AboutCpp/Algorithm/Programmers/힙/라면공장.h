#pragma once

// 이걸 왜 힙으로 할까나...? -> 근데 우선순위 큐가 멋있긴혀!

#include <string>
#include <vector>

#include <queue>
#include <list>

#include <iostream>

using namespace std;

struct MyStruct
{
	int date;
	int supply;

	MyStruct(const int& InDate, const int& InSupply) : date(InDate), supply(InSupply) {};
	MyStruct() = default;
	~MyStruct() = default;

	friend ostream& operator<< (ostream& os, const MyStruct& InMyStruct);
};

ostream& operator<<(ostream& os, const MyStruct& InMyStruct)
{
	os << "Data : " << InMyStruct.date << "   " << InMyStruct.supply << "\n";
	return os;
}

struct CompareFunction {
	bool operator() (MyStruct& InStructA, MyStruct& InStructB)
	{
		return InStructA.date > InStructB.date;
	}
};

template <typename T>
void GetHeapValue(priority_queue<MyStruct, vector<T>, CompareFunction> InMinHeap, T ReturnSmallValue)
{
	ReturnSmallValue = InMinHeap.top();
	InMinHeap.pop();
	return;
}

template <typename T>
void GetHeapValue(priority_queue<T>& InMinHeap, T& ReturnSmallValue)
{
	ReturnSmallValue = InMinHeap.top();
	InMinHeap.pop();
	return;
}


int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
	if (stock >= k - 1)
		return 0;
	
	//priority_queue<MyStruct, vector<MyStruct>, CompareFunction> min_heap;
	list<MyStruct> myList;

	//push
	for (int i = 0; i < dates.size(); ++i)
	{
		//min_heap.push(MyStruct(dates[i], supplies[i]));
		myList.emplace_back(MyStruct(dates[i], supplies[i]));
	}

	//Check
	int answer = 0;
	int stockCount = stock - 1;

	while (stockCount < k - 1)
	{
		std::list<MyStruct>::iterator maxBuffer = myList.begin();

		for (auto iter = myList.begin(); iter != myList.end(); ++iter)
		{
			if (iter->date > stockCount)
			{
				break;
			}
			else
			{
				if (maxBuffer->supply < iter->supply)
				{
					maxBuffer = iter;
				}
			}
		}

		stockCount += maxBuffer->supply;
		maxBuffer->supply = 0;
		++answer;
	}

	return answer;
}