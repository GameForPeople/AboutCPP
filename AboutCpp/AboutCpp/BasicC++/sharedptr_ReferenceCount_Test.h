#pragma once

#include <iostream>
#include <memory>

namespace SHAREDPTR_WITH_TEMPLATE_POINTER
{
	using namespace std;

	class Data {
	public: // for simple test;
		int iBuffer;
		Data() { iBuffer = 10; };
	};

	template <typename DATA>
	class TestNode {
	public: // for simple test;

		DATA data;

		TestNode<DATA>* pLeft{ nullptr };
		TestNode<DATA>* pRight{ nullptr };

		TestNode<DATA>(const DATA& InDATA, TestNode<DATA>* pInLeft = nullptr, TestNode<DATA>* pInRight = nullptr)
			: data(InDATA)
			, pLeft(pInLeft)
			, pRight(pInRight)
		{};
	};

	template <typename DATA>
	class TestCont {
	public:	// for simple test;
		TestNode<DATA>* pHead{nullptr};
	};

	void RefCountTest(const TestNode<shared_ptr<Data>>& InTestNode)
	{
		std::cout << "ㅌㅌ: testNode의 레퍼런스 카운터는 : " << InTestNode.data.use_count() << "입니다. \n";
	}

	void TestFunc()
	{
		int logIndex = 0;

		TestCont<shared_ptr<Data>> testCont;

		TestNode<shared_ptr<Data>> testNode_1(make_shared<Data>(), nullptr, nullptr);
		testCont.pHead = &testNode_1;

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 1

		TestNode<shared_ptr<Data>> testNode_2(make_shared<Data>(), &testNode_1, nullptr);

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 1
		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_2.pLeft->data.use_count() /* == testNode_1.data.use_count() */ << "입니다. \n";		// 1

		TestNode<shared_ptr<Data>> testNode_3 = testNode_1;

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 2

		testNode_3.data.reset();

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 1

		TestNode<shared_ptr<Data>>* testNode_6 = &testNode_1;
		//delete testNode_6;
		//std::cout << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// Error
		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 1

		shared_ptr<Data> testData_1 = testNode_1.data;

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 2

		weak_ptr<Data> testData_2 = testNode_1.data;

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 2

		[/*&testNode_1,*/ &testData_2, &logIndex](const TestNode<shared_ptr<Data>>& InTestNode) -> void	// 
		{
			std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << InTestNode.data.use_count() << "입니다. \n";				// 2

			auto testData_3 = testData_2.lock();

			std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << InTestNode.data.use_count() << "입니다. \n";				// 3
		}(testNode_1);

		std::cout << ++logIndex << "testNode의 레퍼런스 카운터는 : " << testNode_1.data.use_count() << "입니다. \n";				// 2

		RefCountTest(testNode_1);	//2
	}
}