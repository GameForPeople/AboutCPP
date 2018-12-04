#pragma once

/*
	REFERENCE_WRAPPER

	���۷��� ������ ��üó�� ����ϰ� ���� ��, �����.


	��� �Ϲ����� ��Ȳ������ �׳� ���۷����� ����ϴ°� �� �̵���
	(public�� �����ϱ� ����) get�Լ��� ����ؾ��ϰ�, opeartor ���ο��� get���� ó���Ǿ� ����.

	������ ���۷��� ��ü�� ��ü�� Ȱ���Ͽ� ���ư��� ģ���鿡�Դ� �� ���� ������ ���δٰ� �˷���...
	�����̳ʿ� ������ �����ϰ�, bind�� ���� ������ ���� ��ü ���� �����ϴٰ� ��.

	https://docs.microsoft.com/ko-kr/cpp/standard-library/reference-wrapper-class?view=vs-2017
	

	Consider the algorithms in the STL which copy functors: You can avoid that copy by simply passing a reference wrapper referring to the functor instead of the functor itself:

	std::for_each(begin, end, std::ref(fun));

	std::vector<std::reference_wrapper<T>> vec; // OK - does what you want
	std::vector<T&> vec2; // Nope! Will not compile

	// old code   pre c++11
	vector<int*> a;                    // the int values might or might not be owned
	vector<unique_ptr<int>> b;         // the int values are definitely owned
	vector<reference_wrapper<int>> c;  // the int values are definitely not owned
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace REFERENCE_WRAPPER
{
	class TestClass
	{
		int iBuffer;
		std::string sBuffer;
		float fBuffer;

	public:
		TestClass() 
			: iBuffer(10), sBuffer("HELLO"), fBuffer(10.0f)
		{};
		~TestClass() = default;

		void PrintAll()
		{
			printf("iBuffer�� ���� : %d, ������ �ּҴ� : %p \n", iBuffer ,&iBuffer);
		}

		void AddInt()
		{
			++iBuffer;
		}
	};

	class TestChildClass
	{
	public:
		//std::reference_wrapper<TestClass> rc;
		TestClass& rc;

		TestChildClass(TestClass* InUniquePointer)
			: rc(*InUniquePointer)
		{};

		void operator()()
		{
			rc.AddInt();
		}
	};

	class TestRefWrapper
	{
		std::unique_ptr<TestClass> tc;
		//TestClass* tc;
		std::vector<TestChildClass> childArr;

	public:
		TestRefWrapper() : tc
		(std::make_unique<TestClass>())
		//(new TestClass())
		{
			childArr.emplace_back(tc);
			childArr.emplace_back(tc);
			childArr.emplace_back(tc);
			childArr.emplace_back(tc);
			childArr.emplace_back(tc);
		}

		void operator()()
		{
			//TestClass testClass;
			//std::reference_wrapper<TestClass> refClass (testClass);
			//TestClass& refVar(testClass);
			//
			//std::cout << "testClass �� ������� : " << sizeof(testClass) << "\n";
			//std::cout << "RefClass �� ������� : " << sizeof(refClass) << "\n";
			//std::cout << "RefVar �� ������� : " << sizeof(&refVar) << "\n";
			//
			//testClass.PrintAll();
			//refClass.get().PrintAll();
			//refVar.PrintAll();

			std::cout << "----- \n\n";

			tc->PrintAll();
		}
	};
}