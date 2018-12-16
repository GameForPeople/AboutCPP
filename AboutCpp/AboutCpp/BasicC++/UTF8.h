#pragma once

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>

namespace TEST_UTF8
{
	class TestUTF8
	{
	public:
		void operator()()
		{
			std::wcout << L"안녕하세요!" << std::endl;
		}
	};

	void TestFunc()
	{
		_wsetlocale(LC_ALL, L"Korean");

		std::wstring testNickname = L"abc안녕";
		std::wcout << testNickname << std::endl;

		// 파일명 제작
		std::string fileNameBuffer = "TestUTF8.txt";
		
		// 파일 쓰기 모드로 오픈
		std::wofstream outFile(fileNameBuffer, std::ios::out);
		outFile << testNickname << std::endl;

		std::wifstream inFile(fileNameBuffer, std::ios::in);
		inFile >> testNickname;

		std::wcout << testNickname << std::endl;
	}
}