// �̰� ���� ���α׷��� �̻��ؼ� �ȵ�...

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
	
	string answer = "�輭���� ";
	answer += index;
	answer += "�� �ִ�";
	return answer;
}