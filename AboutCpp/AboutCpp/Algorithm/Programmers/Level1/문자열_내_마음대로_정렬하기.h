#pragma once

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<string> solution(vector<string> strings, int n) {

	sort(strings.begin(), strings.end(), [n](string a, string b) -> bool {
		if(a[n] != b[n])
			return a[n] < b[n];
		else {
			int loopSize{ a.size() < b.size() ? (int)a.size() : (int)b.size() };

			for (int i = 0; i < loopSize; i++) {
				if (a[i] != b[i])
					return a[i] < b[i];
			}
		}
	} );
	
	return strings;
}

int i;

bool compare(string a, string b) {
	return a[i] == b[i] ? a < b : a[i] < b[i];
}

vector<string> bestSolution(vector<string> strings, int n) {
	i = n;
	sort(strings.begin(), strings.end(), compare);
	return strings;
}