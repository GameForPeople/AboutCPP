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

		std::vector<int> a(num, 0);	// int��� �ڷ����� ������ Vector A, B�� ����� ��, 
		std::vector<int> b(num, 0); // 0�� ���ҷ� ������ num���� ���(?)�鵵 ���� ����� �ּ���.

		// ���� ��� for�� C++11
		for (auto& i : a)
		{
			std::cin >> i;
		}

		// STL ���ͷ����͸� Ȱ���� For��
		for (auto iter = b.begin(); iter != b.end(); ++iter)
		{
			std::cin >> *iter;
		}

		// Sort �⺻
		std::sort(a.begin(), a.end());

		// Lambda�Լ��� Ȱ���� Sort (��������)
		std::sort(b.begin(), b.end(), 
			[/* void */](int b1, int b2) noexcept -> bool 
		{
			return b1 > b2;
		});

		// �迭ó�� index���� Ȱ���� for�� ������ �͵� ����
		// �ٸ�, vector�� ����(���� �������� �����ؾ���), List, Map, Deque�� �Ұ���
		int sum{ 0 };
		for (int i = 0; i < num; ++i)
		{
			sum += a[i] * b[i];
		}

		std::cout << sum << std::endl;
		return 0;
	}
}