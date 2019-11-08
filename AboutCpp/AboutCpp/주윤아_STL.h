#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

namespace BAEKJOON_1026
{
	int Solution()
	{
		int num;
		std::cin >> num;

		if (num < 1)
		{
			return 0;
		}

		std::vector<int> a(num, 0);	// int라는 자료형을 가지는 Vector A, B를 만드는 데, 
		std::vector<int> b(num, 0); // 0을 원소로 가지는 num개의 요소(?)들도 같이 만들어 주세요.

		// 범위 기반 for문 C++11
		for (auto& i : a)
		{
			std::cin >> i;
		}

		// STL 이터레이터를 활용한 For문
		for (auto iter = b.begin(); iter != b.end(); ++iter)
		{
			std::cin >> *iter;
		}

		// Sort 기본
		std::sort(a.begin(), a.end());

		// Lambda함수를 활용한 Sort (내림차순)
		std::sort(b.begin(), b.end(), 
			[/* void */](int b1, int b2) noexcept -> bool 
		{
			return b1 > b2;
		});

		// 배열처럼 index값을 활용해 for문 돌리는 것도 가능
		// 다만, vector만 가능(랜덤 엑세스가 가능해야함), List, Map, Deque등 불가능
		int sum{ 0 };
		for (int i = 0; i < num; ++i)
		{
			sum += a[i] * b[i];
		}

		std::cout << sum << std::endl;
		return 0;
	}
}