#pragma once

#include <iostream>
#include <set>

#include <string>

using namespace std;

namespace EXAMPLE_SET
{
	class TestClass
	{
	public:
		string stringBuffer;
		int value;

		TestClass(const string& InString, const int& InValue) : stringBuffer(InString), value(InValue) { std::cout << stringBuffer << "�� �⺻ ������ \n"; };
		TestClass(const TestClass& other) : stringBuffer(move(other.stringBuffer)), value(move(other.value)) { std::cout << stringBuffer <<"�� ���� ������ \n"; };
		TestClass(TestClass&& other) : stringBuffer(move(other.stringBuffer)), value(move(other.value)) { std::cout << stringBuffer << "�� �̵� ������ \n";  };
		~TestClass() { std::cout << stringBuffer << "�� �Ҹ��� \n"; };

		void Print()
		{
			std::cout << "String : " << stringBuffer << "  value : " << value << "\n";
		}

	public:
		inline bool operator <(const TestClass& rhs) const {
			return stringBuffer < rhs.stringBuffer;
		}
	};

	void func()
	{
		std::cout << "[0] \n";

		set<TestClass*> testSet;

		TestClass a("A", 1);
		TestClass b("B", 2);
		TestClass c("C", 3);
		//TestClass d("B", 4);
		//TestClass e("Caa", 5);
		//TestClass f("d", 6);
		//TestClass g("E", 7);
		//TestClass h("g", 8);
		//TestClass i("H", 9);
		//TestClass j("i", 10);
		std::cout << "[1] \n";

		testSet.insert(&a);
		testSet.insert(&b);
		testSet.insert(&c);

		std::cout << "[2] \n";

		std::cout << "[E] \n";
	}
}