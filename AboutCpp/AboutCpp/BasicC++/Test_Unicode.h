#pragma once

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <windows.h>

namespace TEST_Unicode
{
	class TestUnicode
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
		using namespace std;

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

		// string to wstirng 테스트
		string testStr("ABC안녕");

		int stringSizeBuffer = MultiByteToWideChar(CP_ACP, 0, &testStr[0], testStr.size(), NULL, NULL);
		std::wstring uniStrBuffer(stringSizeBuffer, 0);
		MultiByteToWideChar(CP_ACP, 0, &testStr[0], testStr.size(), &uniStrBuffer[0], stringSizeBuffer);

		std::wcout << uniStrBuffer << L", 사이즈는 :" << uniStrBuffer.size() << std::endl;

		BYTE* testByte;
		BYTE* testByte1;
		testByte = new BYTE[100];
		testByte1 = new BYTE[100];

		memcpy(testByte, &uniStrBuffer[0], testStr.size());
		memcpy(testByte1, uniStrBuffer.data(), testStr.size());

		//testByte[testStr.size()] = '\0';
		//testByte[testStr.size() + 1] = '\0';

		for (int i = 0; i < testStr.size(); ++i)
		{
			testByte[i] == testByte1[i]
				? std::cout << "True\n"
				: std::cout << "False\n";
		}
	}
}