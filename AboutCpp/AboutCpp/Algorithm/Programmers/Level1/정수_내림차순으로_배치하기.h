#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(long long n) {
	long long buffer = n;
	vector<int> a;

	while (7) {
		if (buffer / 10 < 1) {
			a.emplace_back(buffer % 10);
			break;
		}

		a.emplace_back(buffer % 10);
		buffer /= 10;
	}
	
	sort(a.begin(), a.end(), [](int a1, int b1) ->bool {
		return a1 < b1;
	});

	long long answer = 0;

	for (int i = 0; i < a.size(); ++i) {
		answer += a[i] * pow(10, i);
	}
	
	return answer;
}