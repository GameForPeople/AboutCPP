#pragma once

#include <iostream>

namespace CLASS_OPERATOR
{
	class ExampleClass
	{
	public:
		int buffer{ 0 };
		void operator++()
		{
			buffer = 11;
			std::cout << 11 << std::endl;
		}

		int& operator*()
		{
			return buffer;
		}
	};
}