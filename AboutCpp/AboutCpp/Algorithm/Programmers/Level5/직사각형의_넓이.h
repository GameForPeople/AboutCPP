#pragma once

// 할당받기도 어려워.... 너무나도 어려워... 실패야실패  Plane Sweeping 알고리즘 써도 안될꺼같은데...
//#define DO_LONGLONG
#define DO_BOOL

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#define MAX_NUMBER 1000000000
#define MAX_HALF_NUMBER 500000000
#define MAX_NUMBER_INT 31250000
#define MAX_NUMBER_LONGLONG 15625000
#define SIZE_OF_LONGLONG 64

void __cdecl MyNewHandler()
{
	std::cout << "으악으악으악" << std::endl;
	//동적 할당 실패
	return;
}

long long solution(vector<vector<int>> r)
{
	set_new_handler(MyNewHandler);
	
	long long answer{};
	
	vector<vector<int>> myRects;
	myRects.emplace_back(r[0]);
	bool isOnEmplaceBack{true};

	// create new RectArr 
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
		
		if(isOnEmplaceBack)
			myRects.emplace_back(r[i]);
		else isOnEmplaceBack = true;
	}
	
	// make MaxMin Point pos
	unsigned long long startX = MAX_NUMBER, startY = MAX_NUMBER, endX = 0, endY = 0;
	for (int i = 0; i < myRects.size() ; ++i ) {
		if (myRects[i][0] < startX) startX = myRects[i][0];
		if (myRects[i][1] < startY) startY = myRects[i][1];
		if (myRects[i][2] > endX) endX = myRects[i][2];
		if (myRects[i][3] > endY) endY = myRects[i][3];

		std::cout << i <<"번 째 사각형은  " << myRects[i][0] << " " << myRects[i][1] << " " << myRects[i][2] << " " << myRects[i][3] << std::endl;
	}

	std::cout << std::endl << " 안녕 멘탈님! :) startX : " << startX << " startY :" << startY << " endX : " << endX << " endY : " << endY << std::endl;

#ifdef DO_LONGLONG
	startX /= SIZE_OF_LONGLONG;
	startY /= SIZE_OF_LONGLONG;
	endX /= SIZE_OF_LONGLONG;
	endY /= SIZE_OF_LONGLONG;
#else DO_BOOL

#endif
	//unsigned long long* board = new unsigned long long[endX - startX]; // new unsigned long long[MAX_NUMBER_LONGLONG]; //height
	
	// make Bit Area!
#ifdef DO_LONGLONG
	vector<long long> bitArr{};
#else DO_BOOL
	vector<bool> bitArr(endX - startX, false);
#endif
	//bitArr.reserve(endX - startX);

	//for (int i = 0; i < (endX - startX) - 1; ++i)
	//	bitArr.emplace_back(false);
	
	//bitArr.reserve(MAX_NUMBER_LONGLONG);
	//for (int i = 0; i < MAX_NUMBER_LONGLONG; ++i) //height
	//	board[i] = new unsigned long long[2]; // width

	std::cout << "잘가 멘탈님! :)  bitArr.size() : " << bitArr.size() << " bitArr.capacity() : "<< bitArr.capacity() << "  myRects.size() : " << myRects.size() << " " << std::endl  << std::endl;

#ifdef DO_LONGLONG
	for (int i = startY; i < endY; i++)
	{
		for (int j = 0; j < myRects.size(); j++) {
			if(myRects[j][1] / SIZE_OF_LONGLONG < i && i < myRects[j][3])
		}
	}
#else DO_BOOL
	for (unsigned long long i = startY; i <= endY; i++)
	{
		std::cout << std::endl << " y = " << i << "번 째 라인입니다.  "<< std::endl;

		for (unsigned long long j = 0; j < myRects.size(); j++) {
			if (myRects[j][1] <= i && i < myRects[j][3])
			{
				std::cout << "   " << myRects[j][0] << "    " << myRects[j][2] << std::endl;
				//memset(&bitArr[myRects[j][0]], true, (myRects[j][2] - myRects[j][0]));
				std::fill(bitArr.begin() + (myRects[j][0] - startX), bitArr.begin() + (myRects[j][2] - startX), true);
			}
		}
		
		for (auto j : bitArr) {
			if (j) {
				std::cout << "O";
			}
			else 
				std::cout << "X";
		}

		for (auto j : bitArr) {
			if (j) {
				++answer;
			}
		}
		
		std::fill(bitArr.begin(), bitArr.end(), false);
	}
#endif
	return answer;
}