#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(int n) {
	string hashTable{ "412" };
	string answer{};
	int downNumber;

	while (n > 0) {
		downNumber = n % 3;
		n = n / 3;

		if (!downNumber) {
			n--;
		}

		answer = hashTable[downNumber] + answer;

		std::cout << n << std::endl;
	}
	return answer;
}

