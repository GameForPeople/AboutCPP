#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr) {

	if (arr.size() <= 1) 
	{
		arr[0] = -1;
		return arr;
	}

	std::vector<int>::iterator iterBuffer;
	int valueBuffer = arr[0];

	for (auto i = arr.begin(); i != arr.end(); ++i) {
		if (*i < valueBuffer) {
			valueBuffer = *i;
			iterBuffer = i;
		}
	}

	arr.erase(iterBuffer);

	return arr;
}