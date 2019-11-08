#pragma once

#include <iostream>

#include <map>

#include <string>

#include <fstream>
#include <ctime>
#include <queue>

#include <bitset>

using namespace std;

namespace TEST_FUNC
{
	void func()
	{

	}
	void func2()
	{
		string InID = "abcd";
		string fileNameBuffer = "UserData/Saved/.txt";
		fileNameBuffer.insert(fileNameBuffer.begin() + 15, InID.begin(), InID.end());

		std::cout << fileNameBuffer << "\n";

		std::string ID;
		int winCount, loseCount, Money = -1;

		std::ifstream inFile(fileNameBuffer, std::ios::in);

		inFile >> winCount >> loseCount >> Money;

		if (Money == -1)
		{
			std::cout << "파일 입출력에 실패했습니다.\n";
		}
		else
		{
			std::cout << "파일 입출력에 성공했습니다.\n";
		}

		time_t timeBuffer = time(0);   // get time now
		tm* now = std::localtime(&timeBuffer);
		std::cout << (now->tm_year + 1900) << '-'
			<< (now->tm_mon + 1) << '-'
			<< now->tm_mday
			<< "\n";

	}
}