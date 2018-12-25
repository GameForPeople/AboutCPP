#pragma once

/*
	완주하지 못한 선수 [해시] (https://programmers.co.kr/learn/courses/30/lessons/42576)
		- 마라톤 참여 선수 목록과, 완주 선수 목록이 주어질 때, 완주하지 못한 선수의 이름을 리턴하라.

		#0. 선수는 1명 이상, 100, 000이하
		#1. 참가자의 이름은 1개 이상, 20개 이하의 알파벳 소문자
		#2. 동명이인이 있을 수 있음 (중복 가능)

		!0. 이 알고리즘의 분류인 "해싱"으로 솔루션을 제작하지 않았기 때문에, 
			해싱으로된 솔루션(==BestSolution)을 하단에 추가하였습니다.
*/

#include <string>
#include <vector>

#include <algorithm>
#include <map>	// for BestSolution

using namespace std;

string solution(vector<string> participant, vector<string> completion) {

	sort(participant.begin(), participant.end(),
		[/* void */](string& a, string& b) 
		noexcept(true) -> bool 
	{
		if (a.compare(b) < 0)
			return true;
		else  /* == else if (a.compare(b) > 0) */
			return false;
	});

	sort(completion.begin(), completion.end(), 
		[/* void */](string& a, string& b) 
		noexcept(true) -> bool
	{
		if (a.compare(b) < 0)
			return true;
		else /* == else if (a.compare(b) > 0) */
			return false;
	});

	for (int i = 0; i < completion.size(); ++i)
	{
		if (completion[i].compare(participant[i]) != 0)
		{
			return std::move(participant[i]);
		}
	}
	
	return std::move(participant[participant.size() - 1]);
}


/* 
	다른 사람의 풀이에 있는 Bestsolution입니다.
*/

string BestSolution(vector<string> participant, vector<string> completion) {
	string answer = "";
	map<string, int> strMap;
	for (auto elem : completion)
	{
		if (strMap.end() == strMap.find(elem))
			strMap.insert(make_pair(elem, 1));
		else
			strMap[elem]++;
	}

	for (auto elem : participant)
	{
		if (strMap.end() == strMap.find(elem))
		{
			answer = elem;
			break;
		}
		else
		{
			strMap[elem]--;
			if (strMap[elem] < 0)
			{
				answer = elem;
				break;
			}
		}
	}
	return answer;
}
