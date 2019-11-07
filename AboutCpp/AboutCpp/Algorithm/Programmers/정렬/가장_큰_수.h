#pragma once

// not work

#include <iostream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

void returnValue( const int& InValue ,int& retArr_0, int& retArr_1, int& retArr_2)
{
	if (InValue == 0)
	{
		retArr_0 = 0;
		retArr_1 = 0;
		retArr_2 = 0;
	}
	if (InValue < 10)
	{
		retArr_0 = InValue % 10;
		retArr_1 = 0;
		retArr_2 = 0;
	}
	else if (InValue < 100)
	{
		retArr_0 = (InValue / 10) % 10;
		retArr_1 = InValue % 10;
		retArr_2 = 0;
	}
	else if (InValue < 1000)
	{
		retArr_0 = (InValue / 100) % 10;
		retArr_1 = (InValue / 10) % 10;
		retArr_2 = InValue % 10;
	}
	else
	{
		retArr_0 = 1;
		retArr_1 = 0;
		retArr_2 = 0;
	}
}

string solution(vector<int> numbers) {

	vector<int> firstArr(3);
	vector<int> secondArr(3);

	sort(numbers.begin(), numbers.end(), [ & ](const int& first, const int& second) -> const bool
	{
		//return first < second; // 오름 차순
		//return first > second; // 내림 차순
		returnValue(first, firstArr[0], firstArr[1], firstArr[2]);
		returnValue(second, secondArr[0], secondArr[1], secondArr[2]);

		for (int i = 0; i < 3; ++i)
		{
			if (firstArr[i] == secondArr[i])
				continue;
			else if (firstArr[i] < secondArr[i])
				return false;
			else if (firstArr[i] > secondArr[i])
				return true;
		}

		return first < second ;
	});

	string answer = "";

	if (numbers[0] == 0) return "0";

	for (auto& iter : numbers)
	{
		answer += std::to_string(iter);
	}

	std::cout << answer;

	return answer;
}
