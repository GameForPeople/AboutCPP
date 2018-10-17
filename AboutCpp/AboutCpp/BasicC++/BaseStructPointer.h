#pragma once

/*

	2018.10.17 TestStructPoint

 1. TestStruct의 dataBuffer의 크기값은, BaseStruct이다! 당연한거였나...
 2. 소멸자는 Virtual로 모두 변경할 필요성이 있음!! (Effective C++)
 3. 동적인 클래스 내부에 정적으로 선언된 것은, 소멸자에서 따로 신경쓰지 않아도 됌!

*/

#include <iostream>

namespace TestStructPoint
{
	struct DeleteStruct
	{
		DeleteStruct() { std::cout << "DeleteStruct 생성자 \n"; }
		~DeleteStruct() { std::cout << "DeleteStruct 소멸자 \n"; }
	};

	struct BaseStruct
	{
		BaseStruct() { std::cout << "BaseStruct 생성자 \n"; };
		virtual ~BaseStruct() { std::cout << "BaseStruct 소멸자 \n"; };
	};

	struct ChildStruct : public BaseStruct
	{
		int iBuf[10];
		DeleteStruct cBuf;

		ChildStruct() { std::cout << "ChildStruct 생성자 호출 \n"; };
		virtual ~ChildStruct() override { std::cout << "ChildStruct 소멸자 호출 \n"; }
	};

	struct TestStruct
	{
		BaseStruct* dataBuffer;

		TestStruct() { dataBuffer = new ChildStruct; }
		~TestStruct() { delete dataBuffer; }
	};
}