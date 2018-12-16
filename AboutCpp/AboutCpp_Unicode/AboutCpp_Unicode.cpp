// AboutCpp_Unicode.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"

#include <ctime>
#include <iostream>

int main()
{
	std::clock_t startTime, endTime;

	startTime = clock();
	//---------------------------

	//----------------------------
	endTime = clock();

	printf("함수 소요된 시간 : %.3f \n", (float)(endTime - startTime) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}
