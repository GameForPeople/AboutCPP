#pragma once

/*

	2018.10.17 TestStructPoint

 1. TestStruct�� dataBuffer�� ũ�Ⱚ��, BaseStruct�̴�! �翬�Ѱſ���...
 2. �Ҹ��ڴ� Virtual�� ��� ������ �ʿ伺�� ����!! (Effective C++)
 3. ������ Ŭ���� ���ο� �������� ����� ����, �Ҹ��ڿ��� ���� �Ű澲�� �ʾƵ� ��!

*/

#include <iostream>

namespace TestStructPoint
{
	struct DeleteStruct
	{
		DeleteStruct() { std::cout << "DeleteStruct ������ \n"; }
		~DeleteStruct() { std::cout << "DeleteStruct �Ҹ��� \n"; }
	};

	struct BaseStruct
	{
		BaseStruct() { std::cout << "BaseStruct ������ \n"; };
		virtual ~BaseStruct() { std::cout << "BaseStruct �Ҹ��� \n"; };
	};

	struct ChildStruct : public BaseStruct
	{
		int iBuf[10];
		DeleteStruct cBuf;

		ChildStruct() { std::cout << "ChildStruct ������ ȣ�� \n"; };
		virtual ~ChildStruct() override { std::cout << "ChildStruct �Ҹ��� ȣ�� \n"; }
	};

	struct TestStruct
	{
		BaseStruct* dataBuffer;

		TestStruct() { dataBuffer = new ChildStruct; }
		~TestStruct() { delete dataBuffer; }
	};
}