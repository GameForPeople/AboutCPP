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

		TestClass(const string& InString, const int& InValue) : stringBuffer(InString), value(InValue) {};

		void Print()
		{
			std::cout << "String : " << stringBuffer << "  value : " << value << "\n";
		}

	public:
		bool operator <(const TestClass &rhs) const {

			return stringBuffer < rhs.stringBuffer;
		}
	};

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

		for (auto iter : testSet)
		{
			iter.second.Print();
		}

		g.value = 777;
		// testSet.find() ? ¿©±â¼­ ÆÄÀÎµå°¡ Èûµë.
		testSet.find("E")->second = g;

		for (auto iter : testSet)
		{
			iter.second.Print();
		}

		std::cout << testSet.max_size() << "\n";
	}
}