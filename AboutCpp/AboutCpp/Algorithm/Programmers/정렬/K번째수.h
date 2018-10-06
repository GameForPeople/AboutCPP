#pragma once

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;

	for (auto iter = 0; iter < commands.size(); ++iter)
	{
		vector<int> buffer;

		for (int subIter = commands[iter][0] - 1; subIter <= commands[iter][1] - 1; ++subIter)
		{
			buffer.emplace_back(array[subIter]);
		}

		sort(buffer.begin(), buffer.end());

		for (auto i : buffer)
		{
			std::cout << "   " << i << "  ";
		}

		std::cout << "  : " << buffer[commands[iter][2] - 1] << "\n\n";

		answer.emplace_back(buffer[commands[iter][2] - 1]);
	}
	
	return answer;
}

vector<int> bsetSolution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;

	for (const auto& command : commands) {
		vector<int> sorted;
		for (int i = command[0] - 1; i < command[1]; ++i) {
			const auto iter = upper_bound(sorted.cbegin(), sorted.cend(), array[i]);
			sorted.insert(iter, array[i]);
		}
		answer.push_back(sorted[command[2] - 1]);
	}

	return answer;
}