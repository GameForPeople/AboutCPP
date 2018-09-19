#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <utility> // for pair

#include <algorithm>

using namespace std;

class GameLog
{
	vector<int> stagePlayerScores;
	vector<int> stageEnterCounts;
	vector<pair<int,double>> resultCont;

	int stageNumber;
	int playerNumber;

public:
	__inline GameLog(const int InStageNumber, const int InPlayNumber) : stageNumber(InStageNumber), playerNumber(InPlayNumber)
	{
		stagePlayerScores.reserve(InStageNumber);
		stageEnterCounts.reserve(InStageNumber);
		resultCont.reserve(InStageNumber);

		int intBuffer = InStageNumber;

		while (intBuffer--)
		{
			stagePlayerScores.emplace_back(0);
			stageEnterCounts.emplace_back(0);
		}
	}

	__inline ~GameLog() = default;

public:
	void ProcessPlayerScore(vector<int> InPlayerScores)
	{
		for (int i : InPlayerScores)
		{
			if (i - 1 == stageNumber)
			{
				CountEnterStage(stageNumber - 1);
			}
			else 
			{
				CountPlayerScore(i - 1);
				CountEnterStage(i - 1);
			}
		}
	}

private:
	void CountPlayerScore(const int InPlayerScore)
	{
		++(stagePlayerScores[InPlayerScore]);
	}

	void CountEnterStage(const int InPlayerScore)
	{
		for (int i = 0; i <= InPlayerScore; ++i)
		{
			++(stageEnterCounts[i]);
		}
	}

public:
	void CalculateResult()
	{
		for (int i = 0; i < stageNumber; ++i)
		{
			resultCont.emplace_back( i + 1, (double)stagePlayerScores[i] / stageEnterCounts[i]);
		}
	}

	void SortResult()
	{
		sort(resultCont.begin(), resultCont.end(), [](pair<int, float> a, pair<int, float> b)->bool
		{
			return a.second > b.second;
		});
	}

	void PrintAll()
	{
		for (auto i : resultCont)
		{
			std::cout << "   " << i.first << ":" << i.second << "  ";
		}
	}

	void DebugPrint()
	{
		for (int i = 0; i < stageNumber; ++i)
		{
			std::cout << i << " 번째, 점수 : " << stagePlayerScores[i] << " 접속  : " << stageEnterCounts[i] << std::endl;
		}
	}
};

//vector<int>
void Solution(int n, vector<int> InPlayerScores)
{
	GameLog logData(n, InPlayerScores.size());

	logData.ProcessPlayerScore(InPlayerScores);
	logData.CalculateResult();
	logData.SortResult();
	logData.PrintAll();
	//myData.DebugPrint();
}
