#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UserData
{
	std::string			userId;
	std::string			nickName;

	//std::vector<bool> userLog;
public:
	__inline UserData(const string InUserId, const string InNickName) : userId(InUserId), nickName(InNickName)
	{}

	__inline ~UserData() = default;

public:
	// same = true
	__inline bool CompareUserID(const string InUserId) const 
	{
		return !(userId.compare(InUserId));
	}

	__inline bool CompareNickName(const string InNickName) const
	{
		return !(nickName.compare(InNickName));
	}

	__inline void ChangeNickName(const string InNickName)
	{
		nickName = InNickName;
	}

	__inline string GetNickName() { return nickName; }
	__inline string GetUserId() { return userId; }
};

class UserDataCont
{
	vector<UserData> userData;

public:
	__inline UserDataCont(const int InSize)
	{
		userData.reserve(InSize / 2);
	}

	UserData* EnterUserData(const string InUserId, const string InNickName)
	{
		for (UserData& iter : userData)
		{
			if (iter.CompareUserID(InUserId))
			{
				if (!iter.CompareNickName(InNickName))
				{
					iter.ChangeNickName(InNickName);
				}
				return &iter;
			}
		}

		userData.emplace_back(InUserId, InNickName);
		return &(userData[userData.size() - 1]);
	}

	UserData* LeaveUserData(const string InUserId)
	{
		for (UserData& iter : userData)
		{
			if (iter.CompareUserID(InUserId))
			{
				return &iter;
			}
		}

		std::cout << "Error :: LeaveUserData에서 확인되지 않은 유저가 방을 떠났습니다." << "\n";
	}

	void ChangeNickName(const string InUserId, const string InNickName)
	{
		for (UserData& iter : userData)
		{
			if (iter.CompareUserID(InUserId))
			{
				iter.ChangeNickName(InNickName);
			}
		}
	}

};

class UserLog
{
private:
	UserData*			userData; //
	bool				isEnter;  //

	UserLog() = default;
public:
	__inline UserLog(UserData* InUserData, const bool InIsEnter) : userData(InUserData), isEnter(InIsEnter)
	{};

	__inline ~UserLog() = default;

public:
	void PrintLog()
	{
		if (isEnter)
		{
			std::cout << "유저의 닉네임은 : " << userData->GetNickName() << " 이며, 방에 입장했습니다. // "<< userData->GetUserId() <<"\n";
		}
		else
		{
			std::cout << "유저의 닉네임은 : " << userData->GetNickName() << " 이며, 방에서 퇴장했습니다." << userData->GetUserId() << "\n";
		}
	}
};

class UserLogCont
{
	vector<UserLog> userLog;

public:
	UserLogCont(const int InSize)
	{
		userLog.reserve(2 * InSize / 3);
	}

public:
	void AddLog(UserData* InUserData, const bool InIsEnter)
	{
		userLog.emplace_back(InUserData, InIsEnter);
	}

	void PrintAllLog()
	{
		for (auto iter : userLog)
		{
			iter.PrintLog();
		}
	}
};

string ReturnIDString(string InString, const int StartIndex)
{
	string idStringBuffer;
	int indexBuffer{ 0 };

	while (InString[StartIndex + indexBuffer] != ' ')
	{
		idStringBuffer.push_back(InString[StartIndex + indexBuffer++]);
		//++indexBuffer;
	}

	return idStringBuffer;
}

string ReturnIDString(const string InString, const int StartIndex, const int EndIndex)
{
	string idStringBuffer;
	int indexBuffer{ 0 };

	while (StartIndex + indexBuffer != EndIndex)
	{
		idStringBuffer.push_back(InString[StartIndex + indexBuffer++]);
		//++indexBuffer;
	}

	return idStringBuffer;
}

string ReturnNickNameString(const string InString, const int StartIndex, const int EndIndex)
{
	string nickNameStringBuffer;
	int indexBuffer{ 0 };

	while (StartIndex + indexBuffer != EndIndex)
	{
		nickNameStringBuffer.push_back(InString[StartIndex + indexBuffer++]);
		//++indexBuffer;
	}

	return nickNameStringBuffer;
}

void HandleRecordString(const string InString, UserDataCont* UserDataCont, UserLogCont* UserLogCont)
{
	if (InString[0] == 'E')
	{
		string idStringBuffer = ReturnIDString(InString, 6);
		UserLogCont->AddLog(UserDataCont->EnterUserData(idStringBuffer, ReturnNickNameString(InString, idStringBuffer.size() + 6, InString.size())), true);
	}
	else if (InString[0] == 'L')
	{
		UserLogCont->AddLog(UserDataCont->LeaveUserData(ReturnIDString(InString, 6, InString.size())), false);
	}
	else // change nickName!
	{
		string idStringBuffer = ReturnIDString(InString, 7);
		UserDataCont->ChangeNickName(idStringBuffer, ReturnNickNameString(InString, idStringBuffer.size() + 7, InString.size()));
	}
}

void Solution(vector<string> InString)
{
	UserDataCont userDataCont(InString.size());
	UserLogCont userLogCont(InString.size());

	for(std::string iter:InString)
	{
		HandleRecordString(iter, &userDataCont, &userLogCont);
	}

	//스트링 벡터만들기 구찮아서 고냥 출력했습니다.
	userLogCont.PrintAllLog();
}


