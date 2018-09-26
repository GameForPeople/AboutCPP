#pragma once

#include <iostream>

#include <string>
#include <string_view>

/*
	String_view�� ���Ͽ� ���� �˰Ե� ��. C++17 string_view

		1. string�� C++�� ���ǵ� ���̱� ������.. �ظ��ϸ� std::cout<< �� �������. (printf %s�� ����ϴ���, ���������� ���� ��µɶ��� ����)
		2. string���� operator=(std::string)  ( ex: string a; string b = a ; �� ���� ����� �̷������. )
		3. const std::string_view&�� ���� ��Ʈ�� ��� ���� �ʱ�ȭ����, ���� ����� �̷������. (�����ڿ��� string_view�� ����ص� ����! )
		4. String_View�� ���� ����, �޸𸮴� ���ٰ�(�����δ� �ְ�����...) �����ϴ� ���� �ǰ� ����� �� ���� ��. (���� ����� �� ����� �� ������)

	String�� ���Ͽ� ���� �˰Ե� ��.
		
		1. 
*/

class TestStringView
{
	std::string myString;

public:
	TestStringView(const std::string_view& InString) : myString(InString)
	{
		printf("����� �����ڴ� const std::string_view& �Դϴ�.\n");

		std::cout << "InString�� ������ " << InString << " �Դϴ�." << "\n";
		printf("InString�� �������� ���� %p �Դϴ�.\n", InString);
	
		//myString = InString;

		std::cout << "myString�� ������ " << myString << " �Դϴ�." << "\n";
		printf("myString�� �������� ���� %p �Դϴ�.\n", myString);
	}

	//TestStringView(const std::string& InString) : myString(InString)
	//{
	//	printf("����� �����ڴ� const std::string& �Դϴ�.\n");
	//
	//	std::cout << "InString�� ������ " << InString << " �Դϴ�."<< "\n";
	//	printf("InString�� �������� ���� %p �Դϴ�.\n", InString);
	//
	//	myString = InString;
	//
	//	std::cout << "myString�� ������ " << myString << " �Դϴ�." << "\n";
	//	printf("myString�� �������� ���� %p �Դϴ�.\n", myString);
	//}

};

namespace GLOBAL_STRING_VIEW_TEST
{
	//Fail! �����Ҽ� ���� �ް��Դϴ�.
	//void TestChangeStringView(std::string_view ReturnString)
	//{
	//	ReturnString[0] = 'a';
	//}

	//Fail! ���۷����� ���� ��, const�� �ٿ����� ������(std::string_view&)�� string���� �ʱ�ȭ�� �Ұ����ϵ��� ��.
	//void TestChangeStringView(std::string_view& ReturnString)
	//{
	//	std::string a("hello");
	//	ReturnString = a;
	//}

	//Fail, ���ϰ����� ���Ѱ�...!
	//std::string_view ReturnNewString()
	//{
	//	std::string returnStringBuffer("helloChicken");
	//
	//	return returnStringBuffer;
	//}

	// �Լ� ������, ��Ʈ���� ������ ��, ��ȯ�ϴ� �Լ��Դϴ�.
	std::string* ReturnNewString()
	{
		// in cpp
		//string* stringBuffer = GLOBAL_STRING_VIEW_TEST::ReturnNewString();
		//std::cout << "stringBuffer ����, " << *stringBuffer << " �Դϴ�. " << "\n";
		//printf("stringBuffer�� �ּҰ���, %p �Դϴ�.", stringBuffer);

		std::string* returnStringBuffer = new std::string("helloChicken");

		//printf("returnStringBuffer�� �ּҴ�, %p �Դϴ�.\n", returnStringBuffer);

		return returnStringBuffer;
	}

	void StringMain()
	{
		std::string hello = "Hello";
		TestStringView testStringView("HI");

		std::cout << "\n\n\n";

		
		
		
		std::string stringBuffer("");
		std::cout << " 1. stringBuffer�� ������ " << stringBuffer << " ������� " << sizeof(stringBuffer) << " �Դϴ�. " << "\n";
		
		stringBuffer = "Hello!";
		std::cout << " 2. stringBuffer�� ������ " << stringBuffer << " ������� " << sizeof(stringBuffer) << " �Դϴ�. " << "\n";
		
		
		
		
		std::string* stringPointer = nullptr;
		//std::cout << " 3. stringPointer�� ������ " << stringPointer << " ������� " << sizeof(stringPointer) << " �Դϴ�. " << "\n";
		//std::cout << " 4. *stringPointer�� ������ " << *stringPointer << " ������� " << sizeof(*stringPointer) << " �Դϴ�. " << "\n";

		stringPointer = ReturnNewString();
		std::cout << " 5. stringPointer�� ������ " << stringPointer << " ������� " << sizeof(stringPointer) << " �Դϴ�. " << "\n";
		std::cout << " 6. *stringPointer�� ������ " << *stringPointer << " ������� " << sizeof(*stringPointer) << " �Դϴ�. " << "\n";


		std::string_view stringView = "HELLO";
		std::cout << " 7. stringView�� ������ " << stringView << " ������� " << sizeof(stringView) << " �Դϴ�. " << "\n";

		//std::string_view *stringViewPointer = new string_view;
		//std::cout << " 8. stringViewPointer�� ������ " << stringViewPointer << " ������� " << sizeof(stringViewPointer) << " �Դϴ�. " << "\n";

		//string* stringBuffer = GLOBAL_STRING_VIEW_TEST::ReturnNewString();
		//std::cout << "stringBuffer ����, " << *stringBuffer << " �Դϴ�. "<< "\n";
		//printf("stringBuffer�� �ּҰ���, %p �Դϴ�.", stringBuffer);
	}

}