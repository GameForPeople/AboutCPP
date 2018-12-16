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
			std::wcout << L"�ȳ��ϼ���!" << std::endl;
		}
	};

	void TestFunc()
	{
		_wsetlocale(LC_ALL, L"Korean");
		using namespace std;

		std::wstring testNickname = L"abc�ȳ�";
		std::wcout << testNickname << std::endl;

		// ���ϸ� ����
		std::string fileNameBuffer = "TestUTF8.txt";
		
		// ���� ���� ���� ����
		std::wofstream outFile(fileNameBuffer, std::ios::out);
		outFile << testNickname << std::endl;

		std::wifstream inFile(fileNameBuffer, std::ios::in);
		inFile >> testNickname;

		std::wcout << testNickname << std::endl;

		// string to wstirng �׽�Ʈ
		string testStr("ABC�ȳ�");

		int stringSizeBuffer = MultiByteToWideChar(CP_ACP, 0, &testStr[0], testStr.size(), NULL, NULL);
		std::wstring uniStrBuffer(stringSizeBuffer, 0);
		MultiByteToWideChar(CP_ACP, 0, &testStr[0], testStr.size(), &uniStrBuffer[0], stringSizeBuffer);

		std::wcout << uniStrBuffer << L", ������� :" << uniStrBuffer.size() << std::endl;

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