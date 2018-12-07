#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

namespace WSTRING_TEST
{
	class TestFunc
	{
	public:
		void operator()()
		{
			std::wstring testString((WCHAR*)"�ȳ��ϼ���");

			int size = testString.size();

			std::cout << "�ش� ��Ʈ���� ������� " << size << " �Դϴ�. \n";

			char buffer[100]{ 0 };
			WCHAR wbuffer[100]{ 0 };

			memcpy(buffer, testString.data(), size * 2);
			memcpy(wbuffer, testString.data(), size * 2);

			std::cout << "�ش� buffer�� ��Ʈ���� " << buffer << " �Դϴ�. \n";

			std::wcout.imbue(std::locale("kor"));
			std::wcout << L"�ش� wbuffer�� ��Ʈ���� " << wbuffer << L" �Դϴ�. \n";
		};
	};
};