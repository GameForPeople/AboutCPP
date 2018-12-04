#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace SHARED_PTR
{
	class TestClass
	{
		int iBuffer{};

	public:
		TestClass(const int& InIBuffer) : iBuffer(InIBuffer)
		{};

		void PrintValue() { std::cout << "값은 " << iBuffer << "입니다. \n"; }
		void AddValue() { ++iBuffer; }
	};

	class TestChildClass
	{
		std::shared_ptr<TestClass> m_tc;
	public:
		TestChildClass(std::shared_ptr<TestClass>& InTC)
			: m_tc(InTC)
		{
			std::cout << "m_tc의 Use Count는 " << m_tc.use_count() << "\n";
		};
	};

	class TestWeakChildClass
	{
		std::weak_ptr<TestClass> m_tc;

	public:
		TestWeakChildClass(std::shared_ptr<TestClass>& InTC)
			: m_tc(InTC)
		{
		};

		void operator()()
		{
			std::shared_ptr<TestClass> pLock = m_tc.lock();
			if (pLock != nullptr)
			{
				pLock->PrintValue();
			}
			else
			{
				std::cout << "이미 제거된 리소스 입니다. \n";
			}
		}
	};

	class TestFunc
	{
		std::vector<TestChildClass> childArr;

	public:
		void operator()()
		{
			std::shared_ptr<TestClass> tc_1 = std::make_shared<TestClass>(10);

			childArr.emplace_back(tc_1);
			childArr.emplace_back(tc_1);
			childArr.emplace_back(tc_1);
			childArr.emplace_back(tc_1);

			TestWeakChildClass weakChild(tc_1);
			weakChild();

			childArr.clear();
			std::cout << "tc_1의 Use Count는 " << tc_1.use_count() << "\n";
			tc_1.reset();

			weakChild();
		}
	};
}