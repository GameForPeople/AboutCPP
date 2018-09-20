#pragma once


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MuziLive
{
	int					remainTime;
	vector<int>			foods;


public:
	__inline MuziLive(vector<int> InFoods, int InErrorTime)
		: remainTime(InErrorTime), foods(InFoods) //, turnStartFoodIndex(0) //, remainFoodNum(InFoods.size()),
	{}

	__inline ~MuziLive() = default;

public:
	int CalculateResult()
	{
		int	smallRemainFoodTime;
		int	remainFoodNum;

		while (7)
		{
			CalculateRemainFoodInfo(smallRemainFoodTime, remainFoodNum);

			if (remainTime > remainFoodNum * smallRemainFoodTime)
			{
				remainTime -= remainFoodNum * smallRemainFoodTime;

				for (int& i : foods)
				{
					i -= smallRemainFoodTime;
				}
			}
			else
			{
				break;
			}
		}

		remainTime = remainTime % remainFoodNum;

		for (int i = 0; i < foods.size(); ++i)
		{
			if (foods[i] > 0)
			{
				if (remainTime == 0)
				{
					return (i + 1);
				}

				--remainTime;
			}
		}
	}

private:
	void CalculateRemainFoodInfo(int& InRemainFoodTime, int& InRemainFoodNum)
	{
		InRemainFoodTime = 1000; // max_time
		InRemainFoodNum = 0;

		for (int i : foods)
		{
			if (i > 0)
			{
				if (i < InRemainFoodTime)
				{
					InRemainFoodTime = i;
				}

				++InRemainFoodNum;
			}
		}
	}
};

//int
void Solution( vector<int> InFoodTimes, int n)
{
	MuziLive muziLive(InFoodTimes, n);

	std::cout << "결과 인덱스는 " << muziLive.CalculateResult() << " 입니다." << "\n";
}