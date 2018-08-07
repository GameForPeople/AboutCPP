#pragma once

#include <string>
#include <vector>

using namespace std;

string solution(string s) {
	string answer = "";

	if ( s.size() % 2 == 1) {
		answer = s[s.size() / 2];
	}
	else {
		answer = s[s.size() / 2 - 1];
		answer += s[(s.size() / 2)];
	}
	
	return answer;
}

string bestSolution(string s) {

	int len = s.length();
	if (len % 2 == 0) {
		return s.substr(len / 2 - 1, 2);
	}
	else {
		return s.substr(len / 2, 1);
	}

}