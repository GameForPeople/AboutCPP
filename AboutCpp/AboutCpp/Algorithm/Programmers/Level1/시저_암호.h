#pragma once

// �z�� ���� ���� �ľ��� �Ұ�����....����??

#include <string>
#include <vector>

using namespace std;

string solution(string s, int n) {
	int distance = 'Z' - 'A' + 1;

	for (auto &i : s) {

		if (i == ' ')
		{
			continue;
		}
		else if (i >= 'A' && i <= 'Z') {
			i += n;
			if (i > 'Z') {
				i -= distance;
			}
		}
		else if (i >= 'a' && i <= 'z') {
			i += n;
			if (i > 'z') {
				i -= distance;
			}
		}

	}
	return s;
}
