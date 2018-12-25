#pragma once

#include <iostream>
#include <map>

#include <string>

using namespace std;

namespace EXAMPLE_MAP
{
	class TestClass
	{
	public:
		string stringBuffer;
		int value;

		TestClass(const string& InString, const int& InValue) : stringBuffer(InString), value(InValue) { std::cout << stringBuffer << "의 기본 생성자 \n"; };
		TestClass(const TestClass& other) : stringBuffer(move(other.stringBuffer)), value(move(other.value)) { std::cout << stringBuffer << "의 복사 생성자 \n"; };
		TestClass(TestClass&& other) noexcept : stringBuffer(move(other.stringBuffer)), value(move(other.value)) { std::cout << stringBuffer << "의 이동 생성자 \n"; };
		~TestClass() { std::cout << stringBuffer << "의 소멸자 \n"; };

		void Print()
		{
			std::cout << "String : " << stringBuffer << "  value : " << value << "\n";
		}

		void Change(const string& InString, const int& InValue)
		{
			stringBuffer = InString;
			value = InValue;
		}

	public:
		inline bool operator <(const TestClass& rhs) const {
			return stringBuffer < rhs.stringBuffer;
		}
	};

	void TestFunc()
	{
		std::cout << "[0] \n";

		map<string, TestClass*> testMap;

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

		testMap.insert(pair<string, TestClass*>("ID_A", &a));
		testMap.insert(pair<string, TestClass*>("ID_B", &b));
		testMap.insert(pair<string, TestClass*>("ID_C", &c));

		std::cout << "[2] \n";

		TestClass* buf = testMap.find("ID_A")->second;
		buf->Print();
		buf->Change("ID_A2", 11);
		buf->Print();
		a.Print();

		std::cout << "[E] \n";
	}
	
	void func()
	{
		typedef pair<string, TestClass> userNode;
		map<string, TestClass> testSet;
		
		TestClass a("A", 1);
		TestClass b("C", 2);
		TestClass c("Cb", 3);
		TestClass d("B", 4);
		TestClass e("Caa", 5);
		TestClass f("d", 6);
		TestClass g("E", 7);
		TestClass h("g", 8);
		TestClass i("H", 9);
		TestClass j("i", 10);

		testSet.insert(make_pair(a.stringBuffer, a));
		testSet.insert(make_pair(b.stringBuffer, b));
		testSet.insert(make_pair(c.stringBuffer, c));
		testSet.insert(make_pair(d.stringBuffer, d));
		testSet.insert(make_pair(e.stringBuffer, e));
		testSet.insert(make_pair(f.stringBuffer, f));
		testSet.insert(make_pair(g.stringBuffer, g));
		testSet.insert(make_pair(h.stringBuffer, h));
		testSet.insert(make_pair(i.stringBuffer, i));
		testSet.insert(make_pair(j.stringBuffer, j));

		map<string, TestClass>::iterator pBuffer = testSet.emplace("CaB", TestClass("CaAAAAAAAAAAAAAAAAAAAAAB", 11)).first;

		map<string, TestClass>::iterator* pIter = &pBuffer;
		//testSet.emplace("CaB", TestClass("CaAAAAAAAAAAAAAAAAAAAAAB", 11)).first;
		
		//map<string, TestClass>::iterator* pBuffer = &testSet.find("CaB");
		std::cout << "사이즈는 : " << sizeof(pIter) << "\n";

		for (auto iter : testSet)
		{
			iter.second.Print();
		}

		//g.value = 777;
		//// testSet.find() ? 여기서 파인드가 힘듬.
		//testSet.find("E")->second = g;

		(*pIter)->second.Print();
		testSet.erase(*pIter);

		for (auto iter : testSet)
		{
			iter.second.Print();
		}

		std::cout << testSet.max_size() << "\n";
	}
}