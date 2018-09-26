#pragma once

#include <iostream>

class CustomBitWiseOperator
{
	const int case1 = 0x00000001; // 1
	const int case2 = 0x00000002; // 10
	const int case3 = 0x00000004; // 100
	const int case4 = 0x00000008; // 1000
	const int case5 = 0x00000010; // 10000

	int overlapCase;


	void MakeOverlapCase()
	{
		overlapCase = case1 | case3 | case5; // 10101


		std::cout << "In Case1 : " << (overlapCase & case1) << std::endl;
		std::cout << "In Case2 : " << (overlapCase & case2) << std::endl;
		std::cout << "In Case3 : " << (overlapCase & case3) << std::endl;


		// 연산자 축약형
		overlapCase ^= case1; //on이면 off, off면 on


		/*
		// 쉬프트 연산자 : <<, >>

			2 << 1 = 4
			2 << 2 = 8

			4 >> 1 = 2
			8 >> 2 = 2
 
		*/

		int highValue = 123;
		int lowValue = 456;

		int sumValue = highValue;

		sumValue <<= 16;
		sumValue |= lowValue;

		std::cout << "highValue == " << (sumValue >> 16) << "\n";
		std::cout << "lowValue == " << (sumValue & 0x0000ffff) << "\n";
	}
};