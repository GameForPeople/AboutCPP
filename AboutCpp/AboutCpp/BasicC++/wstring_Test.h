#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>

#include <locale>
#include <codecvt>

#include <mbstring.h>
#include <Mbctype.h>
#include <AtlBase.h>
#include <atlconv.h>

namespace WSTRING_TEST
{
	class TestFunc
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>			converter;
	public:
		std::wstring MultiToWide(std::string InString)
		{
			if (setlocale(LC_ALL, NULL) == NULL)
				printf("setlocale failed.\n");

			WCHAR* destChar = new WCHAR[InString.size() + 1];	// nickname max size - 20

			mbstowcs(&destChar[0], InString.c_str(), InString.size());
			destChar[_mbslen((const unsigned char *)InString.data())] = '\0';
			std::wstring RetString(destChar);

			delete[] destChar;
			return RetString;
		}

		std::string WideToMulti(std::wstring InString)
		{
			if (setlocale(LC_ALL, "") == NULL)
				printf("setlocale failed.\n");

			char* destChar = new char[40];	// nickname max size - 20

			wcstombs(&destChar[0], InString.c_str(), InString.size() * 2);
			destChar[InString.size()* 2] = '\0';
			std::string RetString(destChar);
			
			delete[] destChar;
			return RetString;
		}

		void operator()()
		{
			std::string rootString{ "ABCDE" };
			std::wstring newWString{ MultiToWide(rootString) };

			std::wstring rootWString{ L"ABCDE" };
			std::string newString{ WideToMulti(rootWString) };

			std::cout << "A Root :: " << rootString << " - " << rootString.size() << std::endl;
			std::wcout << L"A New :: " << newWString << L" - " << newWString.size();
			std::cout << std::endl << std::endl;
			
			std::wcout << L"B Root :: " << rootWString << L" - " << rootWString.size();
			std::cout << std::endl 
				<< "B New :: " << newString << " - " << newString.size() << std::endl;

			//newWString = converter.from_bytes(rootString); // abort -> range_error
			//newWString = std::wstring( rootString.begin(), rootString.end() );

			std::cout << "���ڰ����� :" << _mbslen((const unsigned char*)rootString.data()) << std::endl;
			
			LPWSTR lpszW = new WCHAR[_mbslen((const unsigned char*)rootString.data())];
			//MultiByteToWideChar(CP_ACP, 0, rootString.data(), -1, lpszW, _mbslen((const unsigned char*)rootString.data()));
			
			WCHAR newWChar;
			for (int i = 0; i < rootString.size(); ++i)
			{
				switch (_mbsbtype((const unsigned char *)(rootString.data()), i)) {
				case _MBC_SINGLE:     // �̱� ����Ʈ
					printf("1 : [%c]\n", rootString[i]);
					newWString += rootString[i];
					break;
				case _MBC_LEAD:        // ��Ƽ ����Ʈ ���
					printf("2 : [%c", rootString[i]);
					break;
				case _MBC_TRAIL:        // ��Ƽ ����Ʈ ����
					printf("%c]\n", rootString[i]);

					newWChar = rootString[i-1];
					//memcpy(&(newWChar), &(rootString[i - 1]), 2);
					//newWString += newWChar;
					std::wcout << L"����� "<< newWChar <<" \n";
					break;
				case _MBC_ILLEGAL:     // �˼� ���� ����.
					break;
				default:
					break;
				}
			}
			const char* srcCharArr = "ABC�ȳ�";
			WCHAR* desChar = new WCHAR [100];
			mbstowcs(&desChar[0], srcCharArr, 7);
			std::wcout << L" :: " << rootString.size() <<" :: "<< desChar << std::endl;


			std::cout << std::endl;

			//newString = converter.to_bytes(rootWString);
			newString = std::string( rootWString.begin(), rootWString.end() );

			std::cout << " " << rootString.size() << "  " << newWString.size() << "\n";
			std::cout << " " << rootWString.size() << "  " << newString.size() << " " << newString << "\n";

			std::wstring wStringBuffer = std::wstring( newString.begin(), newString.end() );
			std::wcout << " " << wStringBuffer.size() << "  " << wStringBuffer << "\n";
			
			std::cout << "-  " ;
			



			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";



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