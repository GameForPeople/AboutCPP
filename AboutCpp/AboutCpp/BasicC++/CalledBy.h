#pragma once

/*
18/10/14
	- Called By Test.. : ���۷����� �Ѱ��� ��, nullptr�� �������� �ʴ°�.

	��... �ƴѰ��� ��� ������ ���۷����� �Ѱܵ� �Ǵ°� ������?? 

	1. �ϴ� int�� ���۷����� �ѱ��, �����ִ��� �׿��� ������! (�̰� �����غ��� �翬�ϳ� ����)

	�����͸� �ѹ� �غ���?

	�� �����͵� �ǳ�... Ŭ���� ���ص� �ǰ��� ��.

	lValue, RValue�� ���� ���ΰ� �ʿ��� ���δ�.....
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