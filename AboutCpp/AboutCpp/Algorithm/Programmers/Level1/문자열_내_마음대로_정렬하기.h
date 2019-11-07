#pragma once

/*
	문자열 내 마음대로 정렬하기 [연습문제] (https://programmers.co.kr/learn/courses/30/lessons/12915)
		- 문자열로 구성된 리스트 strings와, 정수 n이 주어졌을 때, 각 문자열의 인덱스 n번째 글자를 기준으로 오름차순 정렬하려 합니다

		#0. ex) strings = [sun, bed, car] , n = 1 , return = [car, bed, sun]
		#1. 인덱스 1의 문자가 같은 문자열이 여럿 일 경우, 사전순으로 앞선 문자열이 앞쪽에 위치합니다.
		#2. 모든 strings의 원소의 길이는 n보다 큽니다.

		#3. Sort의 3번째 인자에 따라, 두가지의 솔루션을 제공합니다.
			- 1. 함수 객체를 활용한 방식.
			- 2. 람다 함수를 활용한 방식.

		!0. 전역 함수를 활용하는 방식은, n에 대한 접근을 위해 전역 변수가 필요할 듯 보여 제외했습니다.
			(가능할 수도 있지만 제 실력이 부족해서..)
*/

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

// 1. 함수 객체를 활용한 방식.

class Comp
{
	int compIndex;
public:
	Comp(const int& InCompIndex) noexcept : compIndex(InCompIndex) {}
	~Comp() = default;

	[[nodiscard]] constexpr inline bool operator()(const string& a, const string& b) noexcept
	{
		return a[compIndex] == b[compIndex] ? a < b : a[compIndex] < b[compIndex];
	}
};

vector<string> solution_1(vector<string> strings, int n) 
{
	Comp compFunc(n);
	sort(strings.begin(), strings.end(), compFunc);
	
	return strings;
}


// 2. 람다 함수를 활용한 방식.

vector<string> solution_2(vector<string> strings, int n) 
{
	sort(strings.begin(), strings.end(), [&n](const string& a, const string& b) noexcept(true) -> bool
	{
		return a[n] == b[n] ? a < b : a[n] < b[n];
	} );
	
	return strings;
}


