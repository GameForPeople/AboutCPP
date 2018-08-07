#pragma once

#include <string>
#include <vector>

using namespace std;

string solution(int a, int b) {
	int sumBuffer{};

	if (a == 1) sumBuffer = 0;
	else if (a == 2) sumBuffer = 31; //31
	else if (a == 3) sumBuffer = 60; //29
	else if (a == 4) sumBuffer = 91; //31
	else if (a == 5) sumBuffer = 121; //30
	else if (a == 6) sumBuffer = 152; // 31
	else if (a == 7) sumBuffer = 182;   // 30
	else if (a == 8) sumBuffer = 213; // 31
	else if (a == 9) sumBuffer = 244; // 31
	else if (a == 10) sumBuffer = 274; // 30
	else if (a == 11) sumBuffer = 305; //31   
	else if (a == 12) sumBuffer = 335; // 30

	sumBuffer += b;

	string answer{};
	
	switch (sumBuffer % 7)
	{

	case 0:
		answer.append("FRI");
		break;
	case 1:
		answer.append("SAT");
		break;
	case 2:
		answer.append("SUN");
		break;
	case 3:
		answer.append("MON");
		break;
	case 4:
		answer.append("TUE");
		break;
	case 5:
		answer.append("WED");
		break;
	case 6:
		answer.append("THU");
		break;
	}

	return answer;
}

string bestSolution(int a, int b)
{
	int month[12] = { 0,31,29,31,30,31,30,31,31,30,31,30 };
	string date[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };

	for (int i = 0; i < a; i++)
	{
		b += month[i];
	}

	string answer = date[(b + 4) % 7];

	return answer;
}