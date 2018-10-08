#pragma once

#include <string>
#include <vector>

using namespace std;

string solution(string phone_number) {

	for (auto iter = phone_number.begin(); iter != phone_number.end() - 4; ++iter)
	{
		*iter = '*';
	}

	return phone_number;
}