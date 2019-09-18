#pragma once

#include <iostream>
#include <random>
#include <functional>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std::chrono;
/*
	릴리즈 일떄!
	
	25000000

	If의 성능은? 200 msecs
	Switch의 성능은? 195 msecs
	Function Pointer의 성능은? 221 msecs

	큰 의미가없다...
*/
namespace IFvsSWITCHvsFUNCTION
{
	class TestClass
	{
		static constexpr int MAX_NUMBER = 25000000;
		std::vector<int> commands;
		std::function<void(TestClass&)> funcs[10];

		int buffer{0};
	public:
		TestClass() 
		{
			for (int i = 0; i < MAX_NUMBER; ++i)
			{
				commands.emplace_back(rand() % 10);
				//commands[i] = rand() % 10;
			}

			funcs[0] = &TestClass::Func0;
			funcs[1] = &TestClass::Func1;
			funcs[2] = &TestClass::Func2;
			funcs[3] = &TestClass::Func3;
			funcs[4] = &TestClass::Func4;
			funcs[5] = &TestClass::Func5;
			funcs[6] = &TestClass::Func6;
			funcs[7] = &TestClass::Func7;
			funcs[8] = &TestClass::Func8;
			funcs[9] = &TestClass::Func9;
		}
	public:
		void operator()()
		{
			{
				auto startTime = high_resolution_clock::now();
				IfFunc();
				auto endTime = high_resolution_clock::now() - startTime;
				std::cout << "If의 성능은? " << duration_cast<milliseconds>(endTime).count() << " msecs\n";
			}

			{
				auto startTime = high_resolution_clock::now();
				SwitchFunc();
				auto endTime = high_resolution_clock::now() - startTime;
				std::cout << "Switch의 성능은? " << duration_cast<milliseconds>(endTime).count() << " msecs\n";
			}

			{
				auto startTime = high_resolution_clock::now();
				FunctionPtrFunc();
				auto endTime = high_resolution_clock::now() - startTime;
				std::cout << "Function Pointer의 성능은? " << duration_cast<milliseconds>(endTime).count() << " msecs\n";
			}
		}

		void IfFunc()
		{
			for (int i = 0; i < MAX_NUMBER; ++i)
			{
				if (commands[i] == 0) { Func0(); }
				else if (commands[i] == 1) { Func1(); }
				else if (commands[i] == 2) { Func2(); }
				else if (commands[i] == 3) { Func3(); }
				else if (commands[i] == 4) { Func4(); }
				else if (commands[i] == 5) { Func5(); }
				else if (commands[i] == 6) { Func6(); }
				else if (commands[i] == 7) { Func7(); }
				else if (commands[i] == 8) { Func8(); }
				else if (commands[i] == 9) { Func9(); }
			}
		}

		void SwitchFunc()
		{
			for (int i = 0; i < MAX_NUMBER; ++i)
			{
				switch (commands[i])
				{
				case 0:
					Func0(); break;
				case 1:
					Func1(); break;
				case 2:
					Func2(); break;
				case 3:
					Func3(); break;
				case 4:
					Func4(); break;
				case 5:
					Func5(); break;
				case 6:
					Func6(); break;
				case 7:
					Func7(); break;
				case 8:
					Func8(); break;
				case 9:
					Func9(); break;
				default: break;
				}
			}
		}

		void FunctionPtrFunc()
		{
			for (int i = 0; i < MAX_NUMBER; ++i)
			{
				funcs[commands[i]](*this);
			}
		}

		void Func0() { ++buffer; };
		void Func1() { buffer += 2; };
		void Func2() { buffer += 3; };
		void Func3() { buffer += 4; };
		void Func4() { buffer += 5; };
		void Func5() { buffer += 6; };
		void Func6() { buffer += 7; };
		void Func7() { buffer += 8; };
		void Func8() { buffer += 9; };
		void Func9() { buffer += 10; };
	};
}