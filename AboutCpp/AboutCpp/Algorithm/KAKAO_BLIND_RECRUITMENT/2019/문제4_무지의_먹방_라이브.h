#pragma once

/*
	2019 카카오 신입 공채 1차 코딩 테스트 4번 문제

	무지의 먹방 라이브 (https://programmers.co.kr/learn/courses/30/lessons/42891)
		- 각 음식을 모두 먹는데 필요한 시간이 담겨있는 배열 food_times, 네트워크 장애가 발생한 시간 K 초가 매개변수로 주어질 때 
		몇 번 음식부터 다시 섭취하면 되는지 return 하도록 solution 함수를 완성하라.

		#0. ex) food_Times = [3, 1, 2], k = 5, result = 1
		#1. 만약 더 섭취해야 할 음식이 없다면 -1을 반환하면 된다.
	
		!0. 효율성 테스트
			- food_times 의 길이는 1 이상 200,000 이하이다.
			- food_times 의 원소는 1 이상 100,000,000 이하의 자연수이다.
			- k는 1 이상 2 x 10^13 이하의 자연수이다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <algorithm>

using namespace std;

class Food
{
	friend class MuziLive;

	int		index;
	int		remainCount;

public:
	Food(int InIndex, int InRemainCount)
		: index(InIndex)
		, remainCount(InRemainCount)
	{}

	~Food() = default;
public:
	inline int GetIndex() const noexcept { return index; }
	inline int GetCount() const noexcept { return remainCount; }
};

class MuziLive
{
	vector<Food>			foods;	// 실제로 food 복수형은 food래요....

public:
	MuziLive(const vector<int>& InFoods)
	{
		for (int i = 0; i < InFoods.size() ; ++i)
		{
			foods.emplace_back(i + 1, InFoods[i]);
		}

		sort(foods.begin(), foods.end(), [](const Food& a, const Food& b) -> bool {
			return a.GetCount() < b.GetCount();
		});
	}
	~MuziLive() = default;

public:
	int operator()(long long InremainTime)
	{
		long long remainTime{ InremainTime };
		long long oldTotal{};
		long long total{};

		const int orginSize = foods.size();

		for (int i = 0; i < orginSize; i++)
		{
			oldTotal = total;
			if (i == 0) 
			{
				if (orginSize * foods[0].remainCount <= remainTime)
				{
					total = (orginSize) * foods[i].remainCount;
					continue;
				}
			}
			else 
			{
				total += (foods[i].remainCount - foods[i - 1].remainCount) * (orginSize - i);
				
				if (total <= remainTime) 
					continue;
			}

			remainTime -= oldTotal;

			sort(foods.begin() + i, foods.end(), 
				[](const Food& a, const Food& b) -> bool {
				return a.GetIndex() < b.GetIndex();
			});

			int nowSize = orginSize - i;
			return foods[i + (remainTime % nowSize)].index;
		}
		return -1;
	}
};

int solution(vector<int> InFoodTimes, long long n)
{
	MuziLive muziLive(InFoodTimes);
	return muziLive(n);
}