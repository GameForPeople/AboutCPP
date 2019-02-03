#pragma once

/*
	2019 카카오 신입 공채 1차 코딩 테스트 2번 문제

	실패율 [정렬] (https://programmers.co.kr/learn/courses/30/lessons/42889#)
		- 전체 스테이지의 개수 N, 게임을 이용하는 사용자가 현재 멈춰있는 스테이지의 번호가 담긴 배열 stages가 매개변수로 주어질 때, 
		실패율이 높은 스테이지부터 내림차순으로 스테이지의 번호가 담겨있는 배열을 return 하도록 solution 함수를 완성하라.

		#0. ex) N = 5, stages = [2, 1, 2, 6, 2, 4, 3, 3], result = [3,4,2,1,5]
		#1. N + 1 은 마지막 스테이지(N 번째 스테이지) 까지 클리어 한 사용자를 나타낸다.
		#2. 만약 실패율이 같은 스테이지가 있다면 작은 번호의 스테이지가 먼저 오도록 하면 된다.
		#3. 스테이지에 도달한 유저가 없는 경우 해당 스테이지의 실패율은 0 으로 정의한다.
*/

#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

using namespace std;

class GameLog
{
	friend class GameLogManager;

	int			stageIndex;
	int			failCount;
	int			allCount;
	double		failRate;

public:
	GameLog(const int InStageIndex) noexcept
		: stageIndex(InStageIndex)
		, failCount(0)
		, allCount(0)
		, failRate(0.0f)
	{}
	~GameLog() = default;

public:
	inline bool operator>(const GameLog& other) const noexcept
	{
		return failRate == other.failRate 
			? !(stageIndex > other.stageIndex)
			: failRate > other.failRate;
	}
};

class GameLogManager
{
	vector<GameLog> logCont;

	const int stageNumber;
	const int playerNumber;

public:
	GameLogManager(const int InStageNumber, const int InPlayerNumber)
		: stageNumber(InStageNumber), playerNumber(InPlayerNumber)
		/*, logCont(InStageNumber, { 0, 0, 0.0f })*/
	{
		logCont.reserve(stageNumber + 2);	// 0 -> for Index Hash, stageNumber + 1 -> for All clear UserCount

		for (int i = 0; i < stageNumber + 2; ++i)
		{
			logCont.emplace_back(i);
		}
	}

	~GameLogManager() = default;

public:
	void CountFailCount(const vector<int>& InPlayerScores)
	{
		for (auto i : InPlayerScores)
		{
			++logCont[i].failCount;
		}
	}

	void ProcessCountAndRate()
	{
		logCont[stageNumber + 1].allCount = logCont[stageNumber + 1].failCount;

		for (int i = stageNumber + 1; i > 0; --i)
		{
			logCont[i - 1].allCount = logCont[i].allCount + logCont[i - 1].failCount;

			if (logCont[i - 1].allCount == 0)
				logCont[i - 1].failRate = 0;
			else 
			logCont[i - 1].failRate = static_cast<double>(logCont[i - 1].failCount) / logCont[i - 1].allCount;
		}
	}

	void SortResult()
	{
		// 0번 인덱스 제거.
		logCont.erase(logCont.begin());

		// 모든 스테이지를 클리어한 결과는 정렬할 필요없음.
		logCont.erase(logCont.end() - 1);

		sort(logCont.begin(), logCont.end(), [](const GameLog& a, const GameLog& b)->bool
		{
			return a > b;
		});
	}

	vector<int> GetAnswer()
	{
		vector<int> answer(logCont.size(), 0);

		for (int i = 0; i < logCont.size(); ++i)
		{
			answer[i] = logCont[i].stageIndex;
		}

		return answer;
	}
};

vector<int> solution(int n, vector<int> InPlayerScores)
{
	GameLogManager logManager(n, InPlayerScores.size());

	logManager.CountFailCount(InPlayerScores);
	logManager.ProcessCountAndRate();
	logManager.SortResult();

	return logManager.GetAnswer();
}
