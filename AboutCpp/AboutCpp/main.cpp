#include <string>
#include <time.h>
#include <iostream>

#include <algorithm>

#include "BasicC++/BaseStructPointer.h"

using namespace std;

int main()
{
	clock_t startTime, endTime;

	startTime = clock();
	//---------------------------

	TestStructPoint::TestStruct *testStruct;
	testStruct = new TestStructPoint::TestStruct;

	//std::cout << "������� : " << sizeof(testStruct.dataBuffer) << std::endl;

	delete testStruct;

	//----------------------------
	endTime = clock();

	printf("�Լ� �ҿ�� �ð� : %.3f \n", (float)(endTime - startTime) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}



//#include "Algorithm\Programmers\Level1\�Ҽ� ã��.h"
//#include "Algorithm\KAKAO_BLIND_RECRUITMENT\2019\����1_����ä�ù�.h"

//vector<string> stringBuffer;
//stringBuffer.emplace_back("Enter uid1234 Muzzi");
//stringBuffer.emplace_back("Enter uid4567 Prodo");
//stringBuffer.emplace_back("Leave uid1234");
//stringBuffer.emplace_back("Enter uid1234 Prodo");
//stringBuffer.emplace_back("Change uid4567 Ryan");
//
//Solution(stringBuffer);

//#include "Algorithm\KAKAO_BLIND_RECRUITMENT\2019\����2_������.h"

//	Solution(5, { 2,1,2,6,2,4,3,3 } );

//#include "Algorithm\KAKAO_BLIND_RECRUITMENT\2019\����3_�ĺ�Ű.h"

// 
//Solution({
//	{ "100", "ryan", "music", "2" },
//	{ "200", "apeach", "math", "2" },
//	{ "300", "tube", "computer", "3" },
//	{ "400", "con", "computer", "4" },
//	{ "500", "muzi", "music", "3" },
//	{ "600", "apeach", "music", "2" }
//	});
//

//#include "Algorithm\KAKAO_BLIND_RECRUITMENT\2019\����4_������_�Թ�_���̺�.h"

//Solution({ 3, 1, 2 }, 5);
////Solution({ 1000, 1000, 1000, 10000 }, 5000);


//#include "Algorithm\KAKAO_BLIND_RECRUITMENT\2019\����5_��_ã��_����.h"
//	Solution({ {5,3}, {11,5}, {13,3}, {3,5}, {6,1}, {1,3}, {8,6}, {7,2}, {2,2} });


//#include "Algorithm\KAKAO_BLIND_RECRUITMENT\2019\����7_��ϰ���.h"