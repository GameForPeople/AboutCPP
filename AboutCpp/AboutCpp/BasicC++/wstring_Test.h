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
			std::wstring testString((WCHAR*)"안녕하세요");

			int size = testString.size();

			std::cout << "해당 스트링의 사이즈는 " << size << " 입니다. \n";

			char buffer[100]{ 0 };
			WCHAR wbuffer[100]{ 0 };

			memcpy(buffer, testString.data(), size * 2);
			memcpy(wbuffer, testString.data(), size * 2);

			std::cout << "해당 buffer의 스트링은 " << buffer << " 입니다. \n";

			std::wcout.imbue(std::locale("kor"));
			std::wcout << L"해당 wbuffer의 스트링은 " << wbuffer << L" 입니다. \n";
		};
	};
};