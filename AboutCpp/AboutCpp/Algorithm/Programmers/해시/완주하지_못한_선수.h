#pragma once

#include <string>
#include <vector>

#include <algorithm>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {

	string overlapStringBuffer{};
	bool	isOverlapTrue = false;

	sort(participant.begin(), participant.end(), [&isOverlapTrue, &overlapStringBuffer](string& a, string& b) -> bool
	{
		if (a.compare(b) < 0)
			return true;
		else //if (a.compare(b) > 0)
			return false;
		//else if (a.compare(b) == 0)
		//{
		//	isOverlapTrue = true;
		//	overlapStringBuffer = a;
		//
		//	return false;
		//}
	});

	//if (isOverlapTrue)
	//{
	//	return overlapStringBuffer;
	//}

	sort(completion.begin(), completion.end(), [](string& a, string& b) -> bool
	{
		if (a.compare(b) < 0)
			return true;
		else if (a.compare(b) > 0)
			return false;
	});

	for (int i = 0; i < completion.size(); ++i)
	{
		if (completion[i].compare(participant[i]) != 0)
		{
			isOverlapTrue = true;
			overlapStringBuffer = participant[i];
			break;
		}
	}

	if (isOverlapTrue)
		return overlapStringBuffer;
	else
		return participant[participant.size() - 1];

}


// Best Solution

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
