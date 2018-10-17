#pragma once

#include <vector>

class MyClass;


class MyClass
{
	int iBuffer;

public:
	MyClass(int InIBuffer) : iBuffer(InIBuffer)
	{
		std::cout << " 기본(인자포함) 생성자 호출 \n ";
	}

	MyClass() : iBuffer()
	{
		std::cout << " 기본(인자미포함) 생성자 호출 \n ";
	}

	~MyClass()
	{
		std::cout << "기본 소멸자 호출 \n ";
	}

	MyClass(const MyClass& InMyClass) : iBuffer(InMyClass.iBuffer)
	{
		std::cout << "복사 생성자 호출 \n ";
	}

	MyClass& operator=(const MyClass&)
	{
		std::cout << "복사 할당 생성자 호출 \n ";
		return *this;
	}

	MyClass (MyClass&& InMyClass) noexcept
		: iBuffer(InMyClass.iBuffer) 
	{
		std::cout << "이동 생성자 호출 \n ";
	}

	MyClass& operator=(MyClass&& InMyClass)
	{
		std::cout << "이동 할당 생성자 호출 \n ";
		return *this;
	}
};


void CtrTest()
{
	std::vector<MyClass> myClass;

	std::cout << " 1 emplace_back   \n";
	myClass.emplace_back(1);


	std::cout << "\n 2 push_back \n";
	myClass.push_back(1);


	std::cout << "\n 3 insert \n";
	myClass.insert(myClass.end(), 1);

	std::cout << "\n end  \n ";
}