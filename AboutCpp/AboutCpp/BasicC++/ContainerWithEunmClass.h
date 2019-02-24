#pragma once

#include <vector>


namespace CONTAINER_WITH_ENUM_CLASS
{
	enum class TEST_ENUM : int
	{
		A = 1 ,
		B = 2 ,
		C = 3 ,
		D = 4 ,
		E = 5
	};

	enum class TEST_ENUM_2 : int
	{
		A = 1,
		B = 2,
		C = 3,
		D = 4,
		E = 5
	};

	void TestFunc()
	{
		std::vector<std::pair<TEST_ENUM, TEST_ENUM_2>> myCont;

		myCont.reserve(10);

		myCont.emplace_back(std::make_pair(TEST_ENUM::A, TEST_ENUM_2::A));
		myCont.emplace_back(std::make_pair(TEST_ENUM::B, TEST_ENUM_2::B));
		myCont.emplace_back(std::make_pair(TEST_ENUM::C, TEST_ENUM_2::C));
		myCont.emplace_back(std::make_pair(TEST_ENUM::D, TEST_ENUM_2::D));
	}
}