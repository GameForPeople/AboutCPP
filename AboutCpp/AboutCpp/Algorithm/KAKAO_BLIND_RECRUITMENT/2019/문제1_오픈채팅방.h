#pragma once

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
			// 기존에 없던 새로운 UserId
			return userDataCont.insert(pair<_ID, _Nickname>(InUserId, InNickName)).first;
		}
		else
		{
			// 동일하든, 안하든 굳이 검사하지 말고, 항상 해당 스트링으로 변경해라.
			iter->second = InNickName;
			return iter;
		}
	}

	_Iter LeaveUser(const string& InUserId)
	{
		_Iter iter = userDataCont.find(InUserId);
		if (/*_Iter iter = userDataCont.find(InUserId);*/ iter == userDataCont.end())
		{
			//std::cout << "Error :: LeaveUserData에서 확인되지 않은 유저가 방을 떠났습니다." << "\n";
			//exit(0 /* == ERROR */);
		}
		else
		{
			return iter;
		}
		// for Warning
		return iter;
	}

	void ChangeNickName(const string& InUserId, const string& InNickName)
	{
		_Iter iter = userDataCont.find(InUserId);
		if (/*_Iter iter = userDataCont.find(InUserId);*/ iter == userDataCont.end())
		{
			//std::cout << "Error :: ChangeNickName에서 확인되지 않은 유저가 닉네임을 변경합니다." << "\n";
			//exit(0 /* == ERROR */);
		}
		else
		{
			iter->second = InNickName;
		}
	}
};

class UserLog
{
	friend class UserLogManager;
private:
	_Iter			userIter; //
	bool			isEnter;  //

public:
	UserLog(const _Iter& InUserIter, const bool InIsEnter) noexcept :
		userIter(InUserIter),
		isEnter(InIsEnter)
	{};

	UserLog() = default;
	~UserLog() = default;
};

class UserLogManager
{
	vector<UserLog> userLogCont;
	const string CONST_ENTER_STRING;
	const string CONST_LEAVE_STRING;

public:
	UserLogManager(const int InSize) noexcept
		: CONST_ENTER_STRING("님이 들어왔습니다.")
		, CONST_LEAVE_STRING("님이 나갔습니다.")
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
	string GetLogForAnswerWithIndex(const int& InIndex)
	{
		if (userLogCont[InIndex].isEnter == true)
			return userLogCont[InIndex].userIter->second.append(CONST_ENTER_STRING);
		else /* == if (userLogCont[InIndex].isEnter == false) */
			return userLogCont[InIndex].userIter->second.append(CONST_LEAVE_STRING);
	}

public:
	inline int GetContSize() noexcept { return userLogCont.size(); }
};

string ReturnIDString(const string& InString, const int& StartIndex)
{
	string idStringBuffer;
	int indexBuffer{ 0 };

	while (InString[StartIndex + indexBuffer] != ' ')
	{
		idStringBuffer.push_back(InString[StartIndex + indexBuffer++]);
	}

	return idStringBuffer;
}

string ReturnIDString(const string& InString, const int& StartIndex, const int& EndIndex)
{
	string idStringBuffer;
	int indexBuffer{ 0 };

	while (StartIndex + indexBuffer != EndIndex)
	{
		idStringBuffer.push_back(InString[StartIndex + indexBuffer++]);
	}

	return idStringBuffer;
}

string ReturnNickNameString(const string& InString, const int StartIndex, const int EndIndex)
{
	string nickNameStringBuffer;
	int indexBuffer{ 0 };

	while (StartIndex + indexBuffer != EndIndex)
	{
		nickNameStringBuffer.push_back(InString[StartIndex + indexBuffer++]);
	}

	return nickNameStringBuffer;
}

void HandleRecordString(const vector<string>& InRecords, UserDataManager* userDataManager, UserLogManager* userLogManager)
{
	for (auto& record : InRecords)
	{
		if (record[0] == 'E') // Enter
		{
			string idStringBuffer = ReturnIDString(record, 6);
			userLogManager->AddLog(userDataManager->EnterUser(idStringBuffer, ReturnNickNameString(record, idStringBuffer.size() + 6, record.size())), true);
		}
		else if (record[0] == 'L') // Leave
		{
			userLogManager->AddLog(userDataManager->LeaveUser(ReturnIDString(record, 6, record.size())), false);
		}
		else /* else if (InString[0] == 'C') */ // change nickName!
		{
			string idStringBuffer = ReturnIDString(record, 7);
			userDataManager->ChangeNickName(idStringBuffer, ReturnNickNameString(record, idStringBuffer.size() + 7, record.size()));
		}
	}
}

vector<string> MakeAnswerFromLog(UserLogManager* userLogManager)
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

vector<string> solution(vector<string> records)
{
	UserDataManager userDataManager;
	UserLogManager userLogManager(records.size());
	
	HandleRecordString(records, &userDataManager, &userLogManager);
	
	return MakeAnswerFromLog(&userLogManager);
}

class UserData
{
	std::string			userId;
	std::string			nickName;

	//std::vector<bool> userLog;
public:
	UserData(const string& InUserId, const string& InNickName) : userId(InUserId), nickName(InNickName)
	{}

	~UserData() = default;

public:
	// same = true
	inline bool CompareUserID(const string& InUserId) const
	{
		return !(userId.compare(InUserId));
	}

	inline bool CompareNickName(const string& InNickName) const
	{
		return !(nickName.compare(InNickName));
	}

	inline void ChangeNickName(const string& InNewNickName)
	{
		nickName = InNewNickName;
	}

	__inline string GetNickName() { return nickName; }
	__inline string GetUserId() { return userId; }
};
