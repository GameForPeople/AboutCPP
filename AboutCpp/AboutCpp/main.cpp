#include "stdafx.h"

int main()
{
	auto startTime = high_resolution_clock::now();
	//----------------------------



	//----------------------------
	auto endTime = high_resolution_clock::now() - startTime;

	std::cout << "\n\n�Լ� �ҿ�� �ð� : " << duration_cast<milliseconds>(endTime).count();

	system("pause");
	return 0;
}
