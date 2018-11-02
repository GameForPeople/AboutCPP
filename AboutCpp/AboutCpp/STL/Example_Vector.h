#pragma once

#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;

namespace EXAMPLE_VECTOR
{
	void func()
	{
		vector<int> intCont;

		intCont.reserve(1000);

		for (int i = 0; i < 1000; ++i)
		{
			intCont.emplace_back(i);
		}

		for (auto iter = intCont.begin(); iter != intCont.end(); ++iter)
		{
		//	*iter = 1;
		}

		for (auto& iter : intCont)
		{
		//	iter = 1;
		}

		sort(intCont.begin(), intCont.end(), [](int& a, int& b)->bool
		{
			return a > b;
		});

		for (auto& iter : intCont)
		{
			//std::cout << iter << " ";
		}
	}
}