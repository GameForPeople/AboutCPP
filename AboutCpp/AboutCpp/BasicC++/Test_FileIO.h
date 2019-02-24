#pragma once

#include <iostream>
#include <string>

#include <fstream>
#include <iostream>

namespace TEST_FILE_IO
{
	class TestClass
	{
		//std::string fileName;
		std::ofstream outFile;

	public:
		TestClass()
			: outFile(std::ofstream("hello.txt", std::ios::app))
		{
		}

		void SaveLine()
		{
			std::string strBuf;
			std::cout << "저장할 내용 입력 : ";
			std::rewind(stdin);
			std::cin >> strBuf;

			outFile << " " << strBuf << std::endl;
		}
	};
	
	void TestFunc()
	{
		TestClass testClass;
		
		for (int i = 0; i < 10; ++i)
		{
			testClass.SaveLine();
		}
	}
}