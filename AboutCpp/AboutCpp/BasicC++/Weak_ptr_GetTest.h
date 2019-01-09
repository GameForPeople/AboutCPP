#pragma once

#include <iostream>
#include <memory>

namespace WEAK_PTR_GETTEST
{
	class TestClass
	{
		int value{ 5 };

	public:
		TestClass() = delete;
		TestClass(int InInt) : value(InInt) { std::cout << "�⺻ ������"<< "\n"; };
		~TestClass() { std::cout << "�Ҹ���" << "\n"; };
		TestClass(const TestClass& other) { std::cout << "���� ������" << "\n"; };
		TestClass& operator=(const TestClass& other) { std::cout << "���� ���� ������" << "\n"; };
		TestClass(TestClass&& other) { std::cout << "�̵� ������" << "\n"; };
		TestClass& operator=(TestClass&& other) { std::cout << "�̵� ���� ������" << "\n"; };

	public:
		void PrintValue() { std::cout << value << std::endl; }
	};

	class TestFunc
	{
	public:
		void operator()()
		{
			using namespace std;

			shared_ptr<TestClass> a = make_shared<TestClass>(10);
			//weak_ptr<TestClass> b = a;
			//b.reset();

			weak_ptr<TestClass> b;

			shared_ptr<TestClass> c = b.lock();

			if (c != nullptr)
				c->PrintValue();
		}
	};
}