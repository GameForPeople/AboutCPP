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
			std::wcout << L"�ȳ��ϼ���!" << std::endl;
		}
	};

	void TestFunc()
	{
		_wsetlocale(LC_ALL, L"Korean");

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
	}
}