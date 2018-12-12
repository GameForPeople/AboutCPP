#pragma once

#include <iostream>

namespace MOVE_CONSTRUCTOR
{
	class TestClass
	{
		size_t dataSize;
		int* data;

	public:
		void operator()()
		{
			std::cout << " Data�� nullRef�Դϱ�? " << [](int* InPtr) throw() ->bool { return (InPtr == nullptr ? true : false); }(data) << std::endl;
		}

	public:
		// ������
		TestClass(const size_t InSize) 
			: dataSize(InSize) 
			, data(new int[InSize])
		{
			std::cout << "Simple Constructor \n";
		}

		// �Ҹ���
		~TestClass()
		{
			if (data != nullptr)
			{
				std::cout << "--- Delete Resource \n";
				delete[] data;
			}
			std::cout << "Simple Destructor \n";
		}

		// ���� ������
		TestClass(const TestClass& other)
			: dataSize(other.dataSize)
			, data(new int[other.dataSize])
		{
			std::cout << "Copy Constructor \n";
		
			std::copy(other.data, other.data + other.dataSize, data);
		}
		
		// ���� �Ҵ���
		TestClass& operator=(const TestClass& other)
		{
			std::cout << "Copy assignment Operator \n";
		
			if (this != &other)
			{
				delete[] data;
				dataSize = other.dataSize;
				data = new int[dataSize];
		
				std::copy(other.data, other.data + other.dataSize, data);
			}
			return *this;
		}

		// �̵� ������
		TestClass(TestClass&& other)
			: data(nullptr)
			, dataSize(0)
		{
			std::cout << "Move Constructor \n";

			data = other.data;
			dataSize = other.dataSize;

			other.data = nullptr;
			other.dataSize = 0;

			// == *this = std::move(other);  
		}

		// �̵� �Ҵ� ������
		TestClass& operator=(TestClass&& other)
		{
			std::cout << "Move assignment Operator \n";

			if (this != &other)
			{
				delete data;

				data = other.data;
				dataSize = other.dataSize;

				other.data = nullptr;
				other.dataSize = 0;
			}
			return *this;
		}
	};

	void TestFunc()
	{
		std::cout << "0 \n";
		TestClass a = TestClass(10);
		std::cout << "1 \n";
		TestClass b = std::move(a);
		std::cout << "2 \n";
		b();
		a();
		std::cout << "3 \n";
		a = std::move(b);
		std::cout << "4 \n";
		b();
		a();
	}
}