#pragma once

/*
	모의고사 [완전탐색] (https://programmers.co.kr/learn/courses/30/lessons/42840)
		- 수포자 3명과, 찍는 패턴, 정답 배열이 주어질 때, 가장 많이 맟춘 수포자의 인덱스를 리턴하라.

		#0. 시험은 최대 10,000 문제로 구성되어있습니다.
		#1. 가장 높은 점수를 받은 사람이 여럿일 경우, return하는 값을 오름차순 정렬해주세요.
		
		!0. 이 알고리즘의 분류인 "해싱"으로 솔루션을 제작하지 않았기 때문에,
		해싱으로된 솔루션(==BestSolution)을 하단에 추가하였습니다.
*/

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {

	vector<vector<int>> studentCont	{ 
		{ 1, 2, 3, 4, 5}
	,	{ 2, 1, 2, 3, 2, 4, 2, 5 }
	,	{ 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 } 
	};
	
	std::vector<int> scoreCont(3, 0);

	for (int i = 0; i < answers.size(); ++i)
	{
		if (answers[i] == studentCont[0][i % studentCont[0].size()]) scoreCont[0]++;
		if (answers[i] == studentCont[1][i % studentCont[1].size()]) scoreCont[1]++;
		if (answers[i] == studentCont[2][i % studentCont[2].size()]) scoreCont[2]++;
	}

	int maxScore{ *max_element(scoreCont.begin(), scoreCont.end()) };

	std::vector<int> answer{};
	for (int i = 0; i < 3; ++i)
	{
		if (scoreCont[i] == maxScore) answer.emplace_back(i + 1);
	}

	return answer;
}