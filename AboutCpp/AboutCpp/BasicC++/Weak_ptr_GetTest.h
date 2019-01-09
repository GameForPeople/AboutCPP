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
		TestClass(int InInt) : value(InInt) { std::cout << "기본 생성자"<< "\n"; };
		~TestClass() { std::cout << "소멸자" << "\n"; };
		TestClass(const TestClass& other) { std::cout << "복사 생성자" << "\n"; };
		TestClass& operator=(const TestClass& other) { std::cout << "복사 대입 연산자" << "\n"; };
		TestClass(TestClass&& other) { std::cout << "이동 생성자" << "\n"; };
		TestClass& operator=(TestClass&& other) { std::cout << "이동 대입 연산자" << "\n"; };

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