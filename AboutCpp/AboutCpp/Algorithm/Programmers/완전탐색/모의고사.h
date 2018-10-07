#pragma once

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) {

	std::vector<int> studentA = { 1, 2, 3, 4, 5};
	std::vector<int> studentB = { 2, 1, 2, 3, 2, 4, 2, 5 };
	std::vector<int> studentC = { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 };

	int iterA = 0, iterB = 0, iterC = 0;
	int scoreA = 0, scoreB = 0, scoreC = 0;

	for (const auto& iter : answers)
	{
		if (iter == studentA[iterA])
		{
			scoreA++;
		}

		if (iter == studentB[iterB])
		{
			scoreB++;
		}

		if (iter == studentC[iterC])
		{
			scoreC++;
		}

		++iterA;
		if (iterA == studentA.size())
			iterA = 0;

		++iterB;
		if (iterB == studentB.size())
			iterB = 0;

		++iterC;
		if (iterC == studentC.size())
			iterC = 0;
	}

	vector<int> answer;

	if (scoreA == scoreB && scoreB == scoreC)
	{
		answer.emplace_back(1);
		answer.emplace_back(2);
		answer.emplace_back(3);
	}
	else if (scoreA > scoreB && scoreA > scoreC)
	{
		answer.emplace_back(1);
	}
	else if (scoreB > scoreC && scoreB > scoreA)
	{
		answer.emplace_back(2);
	}
	else if (scoreC > scoreA && scoreC > scoreB)
	{
		answer.emplace_back(3);
	}
	else if (scoreA == scoreB && scoreA > scoreC)
	{
		answer.emplace_back(1);
		answer.emplace_back(2);
	}
	else if (scoreA == scoreC && scoreA > scoreB)
	{
		answer.emplace_back(1);
		answer.emplace_back(3);
	}
	else if (scoreB == scoreC && scoreB > scoreA)
	{
		answer.emplace_back(2);
		answer.emplace_back(3);
	}

	return answer;
}