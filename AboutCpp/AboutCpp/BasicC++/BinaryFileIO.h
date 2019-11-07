#pragma once

#include <iostream>

#define NAME_SIZE 32
#define USER_MAX 10

class UserData
{
	char nickName[32];
	int	 level;
	int  attack;
	int  money;
};

namespace GLOBAL_BINARY_FILE_INPUT_OUTPUT
{
	void SaveUserData()
	{

	}
}


