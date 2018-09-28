#pragma once

// Structured Bindings

/*
	1. Pair, Tuple은 const를 붙여서 사용이 가능하나, structure는 불가능한 것으로 보임.
	2. structure의 private멤버에는 사용이 불가능함.
	3. 동일하게 Class에도 사용은 가능하나, private멤버 변수가 있으면 사용하기 힘듬.
*/


#include <iostream>
#include <string>
#include <tuple>

#include <algorithm> // include pair

struct StructuredBindingsExample
{
	int			intBuffer			=		12345;
	float		floatBuffer			=		67.89f;
	std::string stringBuffer		=		"Hello";
};

class sbClass
{
public:
	int			intBuffer{};
	float		floatBuffer{};
private:
	//int			privateIntBuffer;
};

using namespace std;

class RunExample_StructuredBindings
{
public:
	void RunExample()
	{
		typedef tuple <int, float, string > sbTuple;
		sbTuple tupleExample = make_tuple(123, 45.6f, "hello");

		const auto& [retTupleA, retTupleB, retTupleC] = tupleExample;
		//retTupleA -= 123; // error
		std::cout << "tupleExample  : " << "int - " << retTupleA << "  float - " << retTupleB << "  String - " << retTupleC << "\n\n";



		pair <int, string> sbPair;
		const auto& [retPairA, retPairB] = sbPair;
		std::cout << "pairExample  : " << "int - " << retPairA << "  String - " << retPairB << "\n\n";



		StructuredBindingsExample sbSampleA;
		StructuredBindingsExample sbSampleB;
		StructuredBindingsExample sbSampleC;
		StructuredBindingsExample sbSampleD;
		//called by Value
		auto[returnIntA, returnFloatA, returnStringA] = sbSampleA;
		std::cout << "returnA  : " << "int - " << returnIntA << "  float - "<< returnFloatA << "  String - "<< returnStringA << "\n\n";

		////called by Value with const - ERROR
		//auto [returnIntB, returnFloatB, returnStringB] = sbSampleB;
		//std::cout << "returnB  : " << "int - " << returnIntB << "  float - " << returnFloatB << "  String - " << returnStringB << "\n";

		//called by Reference
		auto& [returnIntC, returnFloatC, returnStringC] = sbSampleC;
		std::cout << "returnC  : " << "int - " << returnIntC << "  float - " << returnFloatC << "  String - " << returnStringC << "\n";
		returnIntC -= 12345;
		std::cout << "sbSample  : " << "int - " << sbSampleC.intBuffer << "  float - " << sbSampleC.floatBuffer << "  String - " << sbSampleC.stringBuffer << "\n\n";

		////called by Const Reference - ERROR
		//auto& [returnIntD, returnFloatD, returnStringD] = sbSampleD ;
		//std::cout << "returnD  : " << "int - " << returnIntD << "  float - " << returnFloatD << "  String - " << returnStringD << "\n";
		//returnIntD -= 12345;
		//std::cout << "sbSample  : " << "int - " << sbSampleD.intBuffer << "  float - " << sbSampleD.floatBuffer << "  String - " << sbSampleD.stringBuffer << "\n";



		sbClass	sbClassA;
		auto[retClassA, retClassB] = sbClassA;

		return;
	}
};



