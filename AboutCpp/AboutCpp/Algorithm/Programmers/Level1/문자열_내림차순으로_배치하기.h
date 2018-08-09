#pragma once

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

string solution(string s) {
	sort(s.begin(), s.end(), [](char a, char b)->bool { return a > b; });

	return s;
}