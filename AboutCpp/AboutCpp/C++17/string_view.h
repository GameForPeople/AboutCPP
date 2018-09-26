#pragma once

#include <iostream>

#include <string>
#include <string_view>

/*
	String_view에 대하여 새로 알게된 점. C++17 string_view

		1. string은 C++에 정의된 놈이기 때문에.. 왠만하면 std::cout<< 로 출력하자. (printf %s를 사용하더라도, 비정상적인 값이 출력될때가 있음)
		2. string에서 operator=(std::string)  ( ex: string a; string b = a ; 는 깊은 복사로 이루어진다. )
		3. const std::string_view&를 통한 스트링 멤버 변수 초기화또한, 깊은 복사로 이루어진다. (생성자에서 string_view를 사용해도 좋다! )
		4. String_View는 값만 갖고, 메모리는 없다고(실제로는 있겠지만...) 생각하는 것이 옳게 사용할 수 있을 듯. (값만 사용할 때 사용할 수 있을듯)

	String에 대하여 새로 알게된 점.
		
		1. 
*/

class TestStringView
{
	std::string myString;

public:
	TestStringView(const std::string_view& InString) : myString(InString)
	{
		printf("실행된 생성자는 const std::string_view& 입니다.\n");

		std::cout << "InString의 내용은 " << InString << " 입니다." << "\n";
		printf("InString의 포인터의 값은 %p 입니다.\n", InString);
	
		//myString = InString;

		std::cout << "myString의 내용은 " << myString << " 입니다." << "\n";
		printf("myString의 포인터의 값은 %p 입니다.\n", myString);
	}

	//TestStringView(const std::string& InString) : myString(InString)
	//{
	//	printf("실행된 생성자는 const std::string& 입니다.\n");
	//
	//	std::cout << "InString의 내용은 " << InString << " 입니다."<< "\n";
	//	printf("InString의 포인터의 값은 %p 입니다.\n", InString);
	//
	//	myString = InString;
	//
	//	std::cout << "myString의 내용은 " << myString << " 입니다." << "\n";
	//	printf("myString의 포인터의 값은 %p 입니다.\n", myString);
	//}

};

namespace GLOBAL_STRING_VIEW_TEST
{
	//Fail! 수정할수 없는 왼값입니다.
	//void TestChangeStringView(std::string_view ReturnString)
	//{
	//	ReturnString[0] = 'a';
	//}

	//Fail! 레퍼런스로 전달 시, const를 붙여주지 않으면(std::string_view&)는 string으로 초기화가 불가능하도록 됨.
	//void TestChangeStringView(std::string_view& ReturnString)
	//{
	//	std::string a("hello");
	//	ReturnString = a;
	//}

	//Fail, 리턴값으로 못넘겨...!
	//std::string_view ReturnNewString()
	//{
	//	std::string returnStringBuffer("helloChicken");
	//
	//	return returnStringBuffer;
	//}

	// 함수 내에서, 스트링을 선언한 후, 반환하는 함수입니다.
	std::string* ReturnNewString()
	{
		// in cpp
		//string* stringBuffer = GLOBAL_STRING_VIEW_TEST::ReturnNewString();
		//std::cout << "stringBuffer 값은, " << *stringBuffer << " 입니다. " << "\n";
		//printf("stringBuffer의 주소값은, %p 입니다.", stringBuffer);

		std::string* returnStringBuffer = new std::string("helloChicken");

		//printf("returnStringBuffer의 주소는, %p 입니다.\n", returnStringBuffer);

		return returnStringBuffer;
	}

	void StringMain()
	{
		std::string hello = "Hello";
		TestStringView testStringView("HI");

		std::cout << "\n\n\n";

		
		
		
		std::string stringBuffer("");
		std::cout << " 1. stringBuffer의 내용은 " << stringBuffer << " 사이즈는 " << sizeof(stringBuffer) << " 입니다. " << "\n";
		
		stringBuffer = "Hello!";
		std::cout << " 2. stringBuffer의 내용은 " << stringBuffer << " 사이즈는 " << sizeof(stringBuffer) << " 입니다. " << "\n";
		
		
		
		
		std::string* stringPointer = nullptr;
		//std::cout << " 3. stringPointer의 내용은 " << stringPointer << " 사이즈는 " << sizeof(stringPointer) << " 입니다. " << "\n";
		//std::cout << " 4. *stringPointer의 내용은 " << *stringPointer << " 사이즈는 " << sizeof(*stringPointer) << " 입니다. " << "\n";

		stringPointer = ReturnNewString();
		std::cout << " 5. stringPointer의 내용은 " << stringPointer << " 사이즈는 " << sizeof(stringPointer) << " 입니다. " << "\n";
		std::cout << " 6. *stringPointer의 내용은 " << *stringPointer << " 사이즈는 " << sizeof(*stringPointer) << " 입니다. " << "\n";


		std::string_view stringView = "HELLO";
		std::cout << " 7. stringView의 내용은 " << stringView << " 사이즈는 " << sizeof(stringView) << " 입니다. " << "\n";

		//std::string_view *stringViewPointer = new string_view;
		//std::cout << " 8. stringViewPointer의 내용은 " << stringViewPointer << " 사이즈는 " << sizeof(stringViewPointer) << " 입니다. " << "\n";

		//string* stringBuffer = GLOBAL_STRING_VIEW_TEST::ReturnNewString();
		//std::cout << "stringBuffer 값은, " << *stringBuffer << " 입니다. "<< "\n";
		//printf("stringBuffer의 주소값은, %p 입니다.", stringBuffer);
	}

}