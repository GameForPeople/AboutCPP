#include "stdafx.h"

int main()
{
	auto startTime = high_resolution_clock::now();
	//----------------------------



	//----------------------------
	auto endTime = high_resolution_clock::now() - startTime;

	std::cout << "\n\n함수 소요된 시간 : " << duration_cast<milliseconds>(endTime).count();

	system("pause");
	return 0;
}
