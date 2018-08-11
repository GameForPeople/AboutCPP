#pragma once

#include <string>
#include <vector>

using namespace std;

int solution(int n) {

	if (n == 2)
		return 1;
	else if (n == 3)
		return 2;

	int answer{ 2 };
	bool isPrimeNumber{ true };

	for (int i = 5; i <= n; i += 2 ) {
		for (int j = 3; j*j <= i; j+= 2) {
			if ((i % j) == 0) {
				isPrimeNumber = false;
				break;
			}
		}

		if (isPrimeNumber)
			answer++;
		else isPrimeNumber = true;
	}

	return answer;
}