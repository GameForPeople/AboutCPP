#pragma once

/*
	REFERENCE_WRAPPER

	레퍼런스 변수를 객체처럼 사용하고 싶을 때, 사용함.


	사실 일반적인 상황에서는 그냥 레퍼런스를 사용하는게 더 이득임
	(public에 접근하기 위해) get함수를 사용해야하고, opeartor 내부에도 get으로 처리되어 있음.

	하지만 레퍼런스 자체를 객체로 활용하여 돌아가는 친구들에게는 더 좋은 성능을 보인다고 알려짐...
	컨테이너에 참조를 저장하고, bind에 대한 참조를 통해 게체 전달 가능하다고 함.

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
			printf("iBuffer의 값은 : %d, 포인터 주소는 : %p \n", iBuffer ,&iBuffer);
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
			//std::cout << "testClass 의 사이즈는 : " << sizeof(testClass) << "\n";
			//std::cout << "RefClass 의 사이즈는 : " << sizeof(refClass) << "\n";
			//std::cout << "RefVar 의 사이즈는 : " << sizeof(&refVar) << "\n";
			//
			//testClass.PrintAll();
			//refClass.get().PrintAll();
			//refVar.PrintAll();

			std::cout << "----- \n\n";

			tc->PrintAll();
		}
	};
}