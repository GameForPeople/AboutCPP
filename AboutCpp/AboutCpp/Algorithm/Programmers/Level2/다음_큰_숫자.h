#pragma once

#include <string>
#include <vector>

using namespace std;

int oneCount(int n) {
	int i, j = 7;
	for (i = 0; n != 0; i++) {
		n &= (n - 1);

		for (j; j >= 0; --j)
		{
			printf("%d", (n >> j) & 1);
		}
			std::cout << std::endl;
	}
	return i;
}

int solution(int n) {
	int saveCount = oneCount(n);

	int i = 0;
	//while (7) {
	//	if (saveCount == oneCount(n + ++i))
	//		break;
	//}

	return n + i;
}