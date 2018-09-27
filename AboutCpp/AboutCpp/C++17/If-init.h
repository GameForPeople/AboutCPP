#pragma once

#include <iostream>

// C++17 If-int

/*
	기존에 안되던, If 내에서의 할당 및 조건처리가 가능해짐.

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