#pragma once

// 항목2_define을_쓰려거든_const,enum,inline을_떠올리자
// 단순한 상수를 쓸 때는, #define보다 const 객체 혹은 enum을 우선 생각합시다.
// 함수처럼 쓰이는 매크로를 만들려면, #define 매크로보다 인라인 함수를 우선 생각합시다.

#include <string>

namespace EC2 {

	// simple case 
	#define EC2_HELLO_DEFINE 100 // bad

	const int helloDefine = 100; // good


	// case 1
	const char* helloConstCharArr = "hello world!"; // bad

	const char* const helloConstCharConstArr = "hello world!"; //soso

	const std::string helloConstString("hello World!"); // good



	// case 2 - 1
	class ExampleClass_1
	{
	private:
		static const int exampleMemberConst = 5;
	};

	// case 2 - 2 
	// if case 2 Error, declare in cpp with case 2 - 1
	const int ExampleClass_1::exampleMemberConst;

	// case 2 - 3
	// if case 2 - 2 Error,
	class ExampleClass_2
	{
	private:
		static const int exampleMemberConst;
	};

	//in cpp
	const int ExampleClass_2::exampleMemberConst = 5; 

	
	// case 2 - 4 , 나열자 둔갑술 (enum hack) <- 이거 자주 쓴대요!
	// if case 2 - 3 Error
	class ExampleClass_3
	{
	private:
		enum { ARR_MAX = 5 };

	private:
	public:
	private:
	public:
	private:

		int myItemArr[ARR_MAX];
	};

	
	
	

	// case 3

#define EC2_CALL_WITH_MAX (a, b) f((a) > (b) ? (a) : (b))			// bad
	

	class ExampleClass_4
	{
	public:
		template<typename T>
		inline void CallWithMax(const T& a, const T& b)				// good
		{
			f(a > b ? a : b);
		}
	};

}
