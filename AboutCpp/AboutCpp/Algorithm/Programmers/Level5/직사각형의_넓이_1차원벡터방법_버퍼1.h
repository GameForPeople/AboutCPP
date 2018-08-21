#pragma once

//#define DO_LONGLONG // use vector<unsigned long long int> --> 64bit
#define DO_BOOL // use vector<bool>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#define MAX_NUMBER 1000000000
//#define MAX_NUMBER_HALF 500000000
//#define MAX_NUMBER_INTSIZE 31250000
//#define MAX_NUMBER_LONGLONG 15625000
//#define SIZE_OF_LONGLONG 64
void __cdecl MyNewHandler()
{
	printf("À¸¾ÇÀ¸¾ÇÀ¸¾Ç\n");
	//std::cout << "À¸¾ÇÀ¸¾ÇÀ¸¾Ç" << std::endl;
	//µ¿Àû ÇÒ´ç ½ÇÆÐ
	return;
}

void CountTrue_ThreadFunc(unsigned long long size, std::vector<bool>::iterator inIter, unsigned long long* retValue) {
	std::vector<bool>::iterator endIter = inIter + size;

	printf("%lld ", *retValue);
	for (auto i = inIter; i < endIter; ++i) {
		if (*i == true)
			++(*retValue);
	}
	printf("%lld \n ", *retValue);

	std::fill(inIter, endIter, false);
};

long long solution(vector<vector<int>> r)
{
	set_new_handler(MyNewHandler);

	long long answer{};

	vector<vector<int>> myRects;

	//vector<vector<int>> nonOverlapRects;
	vector<int> nonOverlapRectIndexs;

	r.reserve(160000);
	/*

	//Find non-overlapping rectangles.
	bool isInsertYourRects{true};
	for (int i = 0; i < r.size(); ++i) {
		for (int j = 0; j < r.size(); ++j)
		{
			if (i == j) {}
			else if (r[i][0] > r[j][2] || r[i][2] < r[j][1] || r[i][1] > r[j][3] || r[i][3] < r[j][1]) {}
			else {
				isInsertYourRects = false;
				break;
			}
		}

		if (isInsertYourRects) {
			nonOverlapRectIndexs.emplace_back(i);
			printf(" index :  %d   \n", i);
		}
		else isInsertYourRects = true;
	}

	// Exclude non-overlapping rectangles and plus answerValue
	if (nonOverlapRectIndexs.size()) {
		for (int i = nonOverlapRectIndexs.size() - 1; i >= 0; --i) {
			//nonOverlapRects.emplace_back(r[i]);
			answer += ((r[nonOverlapRectIndexs[i]][2] - r[nonOverlapRectIndexs[i]][0]) * (r[nonOverlapRectIndexs[i]][3] - r[nonOverlapRectIndexs[i]][1]));
			r.erase(r.begin() + nonOverlapRectIndexs[i]);
		}
	}

	printf(" nonOverlapRectIndexs.size() = %d  answer =  %d \n ", nonOverlapRectIndexs.size(), answer);

	// If all the squares do not overlap, return!
	if (!r.size()) 	return answer;

	*/
	myRects.emplace_back(r[0]);
	bool isOnEmplaceBack{ true };

	// create OverlapRects Cont
	for (int i = 0; i < r.size(); i++) {
		for (int j = 0; j < myRects.size(); j++) {
			if (r[i][0] >= myRects[j][0] && r[i][2] <= myRects[j][2]) {
				if (r[i][1] >= myRects[j][1] && r[i][3] <= myRects[j][3]) {
					isOnEmplaceBack = false;
					break;
				}
			}
			else if (r[i][0] < myRects[j][0] && r[i][2] > myRects[j][2]) {
				if (r[i][1] < myRects[j][1] && r[i][3] > myRects[j][3]) {
					myRects[j] = r[i];
					isOnEmplaceBack = false;
					break;
				}
			}
		}
		if (isOnEmplaceBack)
			myRects.emplace_back(r[i]);
		else isOnEmplaceBack = true;
	}

	// Find X, Y's MaxMin position 
	unsigned long long startX = MAX_NUMBER, startY = MAX_NUMBER, endX = 0, endY = 0;
	
	for (int i = 0; i < myRects.size(); ++i) {
		if (myRects[i][0] < startX) startX = myRects[i][0];
		if (myRects[i][1] < startY) startY = myRects[i][1];
		if (myRects[i][2] > endX) endX = myRects[i][2];
		if (myRects[i][3] > endY) endY = myRects[i][3];
	}

	// make Bit Area!
	unsigned long long bitArrSize = endX - startX;
	vector<bool> bitArr(bitArrSize, false);

	unsigned long long retValue1{}, retValue2{}, retValue3{}, retValue4{};

	// Find the width of rectangles In OverlapRects Cont, 
	for (unsigned long long i = startY; i <= endY; i++)
	{
		for (unsigned long long j = 0; j < myRects.size(); j++) {
			if (myRects[j][1] <= i && i < myRects[j][3])
			{
				std::fill(bitArr.begin() + (myRects[j][0] - startX), bitArr.begin() + (myRects[j][2] - startX), true);
			}
		}

		if (bitArrSize >= 1000) {
			thread th1(&CountTrue_ThreadFunc, bitArrSize / (unsigned long long)4, bitArr.begin() , &retValue1);
			thread th2(&CountTrue_ThreadFunc, bitArrSize / (unsigned long long)4, bitArr.begin() + bitArrSize / (unsigned long long)4, &retValue2);
			thread th3(&CountTrue_ThreadFunc, bitArrSize / (unsigned long long)4, bitArr.begin() + bitArrSize / (unsigned long long)4 * 2, &retValue3);
			thread th4(&CountTrue_ThreadFunc, bitArrSize / (unsigned long long)4, bitArr.begin() + bitArrSize / (unsigned long long)4 * 3, &retValue4);

			th1.join();
			th2.join();
			th3.join();
			th4.join();
		}
		else {
			thread th1(&CountTrue_ThreadFunc, bitArrSize, bitArr.begin(), &retValue1);
			th1.join();
			//for (auto j : bitArr) {
			//	if (j) {
			//		++answer;
			//	}
			//}
			//
			//std::fill(bitArr.begin(), bitArr.end(), false);
		}
	}

	if (bitArrSize >= 1000)
	{
		answer += retValue1 + retValue2 + retValue3 + retValue4;
	}
	else
		//return answer;
		return retValue1;
}
