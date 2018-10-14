#pragma once

/*
18/10/14
	- Called By Test.. : 레퍼런스로 넘겼을 때, nullptr를 참고하지 않는가.

	엥... 아닌가봐 고냥 무조건 레퍼런스로 넘겨도 되는거 같은데?? 

	1. 일단 int는 레퍼런스로 넘기고, 원래있던애 죽여도 괜찮아! (이거 생각해보니 당연하네 ㄴㄷ)

	포인터를 한번 해볼까?

	뭐 포인터도 되네... 클래스 안해도 되것지 뭐.

	lValue, RValue에 대한 공부가 필요해 보인다.....
*/

namespace CALLED_BY
{
	class Test
	{
		int buffer;

	public:
		void SetValue(const int& InBuffer)
		{
			buffer = InBuffer;
		}

		void SetValue(const int* InBuffer)
		{
			buffer = *InBuffer;
		}

		int GetValue()
		{
			return buffer;
		}
	};

	void TestFunc(Test& retTest)
	{
		int a = 10;

		retTest.SetValue(&a);
	}
}