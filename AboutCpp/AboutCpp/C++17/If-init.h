#pragma once

#include <iostream>

// C++17 If-int

/*
	������ �ȵǴ�, If �������� �Ҵ� �� ����ó���� ��������.

*/

class ExampleA
{
	bool isInit{ false };

public:
	ExampleA() : isInit(true) {}

	bool IsVaild()
	{
		return isInit;
	}
};

class IfInitClass
{
public:
	void IfInitBasicTest() 
	{
		if (int a = 10; a == 10)
		{
			printf("a == 10");
		}
		else
		{
			printf("a == 11");
		}
	}

	void IfInitClassTest()
	{
		if (ExampleA eA; eA.IsVaild())
		{
			printf("true");
		}
		else
		{
			printf("false");
		}
	}
};