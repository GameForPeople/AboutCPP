#pragma once
#include <iostream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr, int divisor) {

	vector<int> answer{};

	for (auto iter : arr) {

		if (!(iter % divisor)) {

			if (!answer.size()) {
				answer.emplace_back(iter);
			}
			else {
				bool boolBuffer{ false };

				for (auto subIter = answer.begin(); subIter != answer.end(); subIter++) {
					if (*subIter > iter) {
						answer.insert(subIter, iter);
						boolBuffer = true;
						break;
					}
				}

				if(!boolBuffer)
					answer.emplace_back(iter);
			}
		}
	}

	if (!answer.size())
		answer.emplace_back(-1);

	return answer;
}


vector<int> bestSolution(vector<int> arr, int divisor) {
	vector<int> answer;
	std::vector<int>::iterator iter = arr.begin();
	for (iter = arr.begin(); iter != arr.end(); iter++) {
		if (*iter%divisor == 0) {
			int num = *iter;
			answer.push_back(num);
		}
	}
	if (answer.empty()) {
		answer.push_back(-1);
	}
	else {
		sort(answer.begin(), answer.end());
	}
	return answer;
}