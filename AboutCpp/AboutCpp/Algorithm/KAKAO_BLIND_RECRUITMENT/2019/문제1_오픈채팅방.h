#pragma once

/*
	2019 카카오 신입 공채 1차 코딩 테스트 1번 문제

	오픈채팅방 [] (https://programmers.co.kr/learn/courses/30/lessons/42888)
		- 채팅방에 들어오고 나가거나, 닉네임을 변경한 기록이 담긴 문자열 배열 record가 매개변수로 주어질 때, 
		모든 기록이 처리된 후, 최종적으로 방을 개설한 사람이 보게 되는 메시지를 문자열 배열 형태로 return 하도록 solution 함수를 완성하라.

		#0. ex) 
				input - ["Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"]
				output - ["Prodo님이 들어왔습니다.", "Ryan님이 들어왔습니다.", "Prodo님이 나갔습니다.", "Prodo님이 들어왔습니다."]
		#1. record는 다음과 같은 문자열이 담긴 배열이며, 길이는 1 이상 100,000 이하이다.
		#2. 모든 유저는 [유저 아이디]로 구분한다.
		#3. 각 단어는 공백으로 구분되어 있으며, 알파벳 대문자, 소문자, 숫자로만 이루어져있다.
		#4. 채팅방에서 나간 유저가 닉네임을 변경하는 등 잘못 된 입력은 주어지지 않는다.
		#5. 첫 단어는 Enter, Leave, Change 중 하나이다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

using _ID = basic_string<char, char_traits<char>, allocator<char>>;;
using _Nickname = basic_string<char, char_traits<char>, allocator<char>>;;
using _Iter = std::map<_ID, _Nickname>::iterator;

class UserDataManager
{
	std::map<_ID, _Nickname> userDataCont;

public:
	UserDataManager() = default;
	~UserDataManager() = default;

	_Iter EnterUser(const _ID& InUserId, const _Nickname& InNickName)
	{
		_Iter iter = userDataCont.find(InUserId);
		if (/*_Iter iter = userDataCont.find(InUserId);*/ iter == userDataCont.end())
		{
			return userDataCont.insert(pair<_ID, _Nickname>(InUserId, InNickName)).first;
		}
		iter->second = InNickName;
		return iter;
	}

	_Iter LeaveUser(const string& InUserId)
	{
		// 해당 아이디의 유저가 없을 경우의 수는 고려하지 않음.(조건)
		return userDataCont.find(InUserId);
	}

	void ChangeNickName(const string& InUserId, const string& InNickName)
	{
		// 해당 아이디의 유저가 없을 경우의 수는 고려하지 않음.(조건)
		userDataCont.find(InUserId)->second = InNickName;
	}
};

class UserLog
{
	friend class UserLogManager;
private:
	_Iter			userIter; 
	bool			isEnter;  

public:
	UserLog(const _Iter& InUserIter, const bool InIsEnter) noexcept :
		userIter(InUserIter),
		isEnter(InIsEnter)
	{};

	UserLog() = delete;
	~UserLog() = default;
};

class UserLogManager
{
	vector<UserLog> userLogCont;
	const string CONST_ENTER_STRING;
	const string CONST_LEAVE_STRING;

public:
	UserLogManager(const int InSize) noexcept : 
		CONST_ENTER_STRING("님이 들어왔습니다."), 
		CONST_LEAVE_STRING("님이 나갔습니다.")
	{
		userLogCont.reserve(InSize);
	}

	~UserLogManager() = default;

public:
	void AddLog(const _Iter& InIter, const bool InIsEnter)
	{
		userLogCont.emplace_back(InIter, InIsEnter);
	}

	// 스트링을 만들어서 보냅니다.
	string GetLogForAnswerWithIndex(const int InIndex)
	{
		if (userLogCont[InIndex].isEnter == true)
			return userLogCont[InIndex].userIter->second + CONST_ENTER_STRING;
		else /* == if (userLogCont[InIndex].isEnter == false) */
			return userLogCont[InIndex].userIter->second + CONST_LEAVE_STRING;
	}

public:
	inline int GetContSize() const noexcept { return userLogCont.size(); }
};

namespace GLOBAL_FUNCTION {
	enum class START_INDEX : int
	{
		ENTER = 6,
		LEAVE = 6,
		CHANGE = 7
	};
	
	string ReturnIDString(const string& InString, const int InStartIndex)
	{
		int indexBuffer{ 0 };

		while (InString[InStartIndex + ++indexBuffer] != ' ')
		{}
		
		return InString.substr(InStartIndex, indexBuffer);
	}

	void HandleRecordString(const vector<string>& InRecords, UserDataManager* const userDataManager, UserLogManager* const userLogManager)
	{
		for (const auto& record : InRecords)
		{
			if (record[0] == 'E') // Enter
			{
				string idStringBuffer = ReturnIDString(record, static_cast<int>(START_INDEX::ENTER));
				
				userLogManager->AddLog(userDataManager->EnterUser( idStringBuffer, 
					string(record, idStringBuffer.size() + static_cast<int>(START_INDEX::ENTER) + 1)),
					true );
			}
			else if (record[0] == 'L') // Leave
			{
				userLogManager->AddLog(userDataManager->LeaveUser(string(record, static_cast<int>(START_INDEX::LEAVE))), false);
			}
			else /* else if (InString[0] == 'C') */ // change nickName!
			{
				string idStringBuffer = ReturnIDString(record, static_cast<int>(START_INDEX::CHANGE));
				
				userDataManager->ChangeNickName(idStringBuffer, string(record, idStringBuffer.size() + static_cast<int>(START_INDEX::CHANGE) + 1));
			}
		}
	}

	vector<string> MakeAnswerFromLog(UserLogManager* const userLogManager)
	{
		vector<string> answer;

		const int contSize = userLogManager->GetContSize();
		answer.reserve(contSize);

		for (int i = 0; i < contSize; ++i)
		{
			answer.emplace_back(userLogManager->GetLogForAnswerWithIndex(i));
		}

		return answer;
	}
}

vector<string> solution(vector<string> records)
{
	UserDataManager userDataManager;
	UserLogManager userLogManager(records.size());
	
	GLOBAL_FUNCTION::HandleRecordString(records, &userDataManager, &userLogManager);
	
	return GLOBAL_FUNCTION::MakeAnswerFromLog(&userLogManager);
}

