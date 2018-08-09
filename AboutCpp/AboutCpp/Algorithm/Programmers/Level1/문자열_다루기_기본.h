#pragma once

#include <string>
#include <vector>

using namespace std;

bool solution(string s) {
	if (!(s.size() == 4 || s.size() == 6))
		return false;

	for (auto i : s) {
		if (!('0' <= i && i <= '9'))
			return false;
	}

	return true;
}