// 이거 지금 프로그램이 이상해서 안돼...

#pragma once

#include <string>
#include <vector>

#include <algorithm>
using namespace std;

string solution(vector<string> seoul) {
	int index{};
	for (int i = 0; i < seoul.size(); ++i) {
		if (seoul[i] == "Kim") {
			index = i;
		}
	}
	
	string answer = "김서방은 ";
	answer += index;
	answer += "에 있다";
	return answer;
}