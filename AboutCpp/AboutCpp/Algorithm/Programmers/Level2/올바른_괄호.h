#pragma once

#include<string>
#include <iostream>

using namespace std;

bool solution(string s)
{
	int boolCount{};

	for (auto i : s) 
	{
		if (i == '(') boolCount++;
		else if (i == ')') {
			boolCount--;
			if (boolCount < 0)		return false;
		}
	}

	if (!boolCount) return true;
	else return false;
}