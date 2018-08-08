#pragma once

#include <string>
#include <iostream>
using namespace std;

bool solution(string s)
{
	int pCount{0};
	int yCount{0};

	for (auto c : s) {
		if (c == 'p' || c == 'P')
			pCount++;
		else if (c == 'y' || c == 'Y')
			yCount++;
	}
	if (pCount == yCount)
		return true;
	else
		return false;
}