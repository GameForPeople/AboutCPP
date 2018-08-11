#pragma once

#include <string>
#include <vector>

using namespace std;

int solution(string s) {

	if ('0' <= s[0] && s[0] <= '9') {
		return atoi(s.c_str());
	}
	else {
		if (s[0] == '-') {
			s.erase(s.begin());
			return -1 * atoi(s.c_str());
		}
		else {
			s.erase(s.begin());
			return atoi(s.c_str());
		}
	}
}