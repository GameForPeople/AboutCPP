#pragma once

#include <vector>

class MyClass;


class MyClass
{
	int iBuffer;

public:
	MyClass(int InIBuffer) : iBuffer(InIBuffer)
	{
		std::cout << " �⺻(��������) ������ ȣ�� \n ";
	}

	MyClass() : iBuffer()
	{
		std::cout << " �⺻(���ڹ�����) ������ ȣ�� \n ";
	}

	~MyClass()
	{
		std::cout << "�⺻ �Ҹ��� ȣ�� \n ";
	}

	MyClass(const MyClass& InMyClass) : iBuffer(InMyClass.iBuffer)
	{
		std::cout << "���� ������ ȣ�� \n ";
	}

	MyClass& operator=(const MyClass&)
	{
		std::cout << "���� �Ҵ� ������ ȣ�� \n ";
		return *this;
	}

	MyClass (MyClass&& InMyClass) noexcept
		: iBuffer(InMyClass.iBuffer) 
	{
		std::cout << "�̵� ������ ȣ�� \n ";
	}

	MyClass& operator=(MyClass&& InMyClass)
	{
		std::cout << "�̵� �Ҵ� ������ ȣ�� \n ";
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