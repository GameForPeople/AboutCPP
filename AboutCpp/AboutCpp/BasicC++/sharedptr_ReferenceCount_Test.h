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

		void operator()()
		{
			std::cout << "Hello! \n";
		}

		void ABC()
		{
			std::cout << "ABC! \n";
		}
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

		DATA GetData()
		{
			return data;
		}

		DATA& GetDataRef()		// --> �̰� ����.
		{
			return data;
		}

		void VoidFunc()
		{
			data->ABC();
		}
	};

	template <typename DATA>
	class TestCont {
	public:	// for simple test;
		TestNode<DATA>* pHead{nullptr};
	};

	void RefCountTest(const TestNode<shared_ptr<Data>>& InTestNode)
	{
		std::cout << "����: testNode�� ���۷��� ī���ʹ� : " << InTestNode.data.use_count() << "�Դϴ�. \n";
	}

	void TestFunc()
	{
		TestCont<shared_ptr<Data>> testCont;

		TestNode<shared_ptr<Data>> testNode_1(make_shared<Data>(), nullptr, nullptr);
		testCont.pHead = &testNode_1;

		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 1




		TestNode<shared_ptr<Data>> testNode_2(make_shared<Data>(), &testNode_1, nullptr);

		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 1
		std::cout << testNode_2.pLeft->data.use_count() /* == testNode_1.data.use_count() */ << "�Դϴ�. \n";		// 1




		TestNode<shared_ptr<Data>> testNode_3 = testNode_1;

		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 2



		testNode_3.data.reset();

		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 1




		TestNode<shared_ptr<Data>>* testNode_6 = &testNode_1;
		//delete testNode_6;
		//std::cout << "testNode�� ���۷��� ī���ʹ� : " << testNode_1.data.use_count() << "�Դϴ�. \n";				// Error
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 1



		shared_ptr<Data> testData_1 = testNode_1.data;
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 2

		
		weak_ptr<Data> testData_2 = testNode_1.data;
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 2

		[/*&testNode_1,*/ &testData_2](const TestNode<shared_ptr<Data>>& InTestNode) -> void	// 
		{
			std::cout << InTestNode.data.use_count() << "�Դϴ�. \n";				// 2

			auto testData_3 = testData_2.lock();

			std::cout << InTestNode.data.use_count() << "�Դϴ�. \n";				// 3
		}(testNode_1);

		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 2

		RefCountTest(testNode_1);	//2


		shared_ptr<Data> retData_1 = testNode_1.GetData();				
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 3



		shared_ptr<Data> retData_2 = testNode_1.GetDataRef();
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 4


		testNode_1.GetDataRef().reset();
		testData_1.reset();
		retData_1.reset();
		retData_2.reset();
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 0

		// nullptr reset
		testData_2.reset();
		std::cout << testNode_1.data.use_count() << "�Դϴ�. \n";				// 0


		testNode_1.VoidFunc();
	}
}