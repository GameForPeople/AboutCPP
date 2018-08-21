#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_INPUT_RECTANGLE_COUNT 100000
#define x1 [0]
#define y1 [1]
#define x2 [2]
#define y2 [3]

class CRect {
public:

	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;

	__inline CRect() = default;
	__inline ~CRect() = default;

	__inline CRect(const int inX1, const int inY1, const int inX2, const int inY2) : m_x1(inX1), m_y1(inY1), m_x2(inX2), m_y2(inY2)
	{}

	__inline CRect(vector<int>& a) : m_x1(a[0]), m_x2(a[2]), m_y1(a[1]), m_y2(a[3])
	{}
		//printf("%d, %d %d  \n ", sizeof(a), sizeof(this), a[3]);
	__inline long long GetSize() const
	{
		return (m_x2 - m_x1) * (m_y2 - m_y1);
	}
};

long long solution(vector<vector<int>> r)
{
	printf("Sort Start ----- \n");
	
	// Size Sort
	//sort(r.begin(), r.end(), [](vector<int> a, vector<int> b)->bool
	//	{
	//		return ( (a[2] - a[0]) * (a[3] - a[1]) > (b[2] - b[0]) * (b[3] - b[1]));
	//	}
	//);

	// x1 Sort로 왼쪽으로 땡김
	sort(r.begin(), r.end(), [](vector<int> a, vector<int> b)->bool
		{
			return ( a[0] < b[0]);
		}
	);

	printf("Sort End ----- \n");

	int inRectContSize = r.size();
	//int oldRectContSize = r.size();
	vector<CRect> childRectCont;
	childRectCont.reserve(inRectContSize / 2);

	vector<int> insertVectorBuffer(4, 0);

	bool isTrueEmplaceBack{ true };
	
	long long answer{};

	//printf("A의 좌표는 %d, %d, %d, %d \n", r[93947]x1, r[93947]y1, r[93947]x2, r[93947]y2);

	for (int i = 0; i < inRectContSize - 1; i++) 
	{
		if (r[i]x1 > -1) 
		{
			//if (i == 93947) {
			//	printf("A의 좌표는 %d, %d, %d, %d \n", r[i]x1, r[i]y1, r[i]x2, r[i]y2);
			//	printf(" ");
			//}

			for (int j = i + 1; j < inRectContSize; j++)
			{
				//if (i == 93947) {
				//	if (r[i]x1 > r[i]x2 || r[i]y1 > r[i]y2) {
				//		printf("네놈이 죄인이다!!! 의 인덱스 %d 는 %d, %d, %d, %d \n", j-1 , r[j - 1]x1, r[j - 1]y1, r[j - 1]x2, r[j - 1]y2);
				//		printf("너의 좌표는 %d, %d, %d, %d \n", r[i]x1, r[i]y1, r[i]x2, r[i]y2);
				//	}
				//}
				if (r[j]x1 == -1) // 이미 제외된 친구일 때
				{
					isTrueEmplaceBack = false; // 잘가!
				}
				else if (r[i]x1 >= r[j]x2 || r[i]x2 <= r[j]x1 || r[i]y1 >= r[j]y2 || r[i]y2 <= r[j]y1) // 겹치지 않았다.
				{
					continue;
				}
				else // 겹쳤을 때
				{
					if (r[i]x1 >= r[j]x1 && r[i]x2 <= r[j]x2) // x 축으로 A가 B에 포함될 때 (A)
					{
						if (r[i]y1 >= r[j]y1 && r[i]y2 <= r[j]y2) // y축으로 A가 B에 포함될 때 (A)1
						{
							isTrueEmplaceBack = false;
							break; // 현재의 i는 고냥 버린다. -> 필요없는 놈!!
						}
						else if (r[i]y1 < r[j]y1 && r[i]y2 > r[j]y2) // y축으로 A가 B보다 넓을 때 (A)2
						{
							if (r[i]x1 == r[j]x1 && r[i]x2 == r[j]x2) // B를 날려버려!
							{
								r[j]x1 = -1;
								r[j]y1 = -1; //꼭 애네까지 해야해?
								r[j]x2 = -1;
								r[j]y2 = -1;
							}
							else {
								insertVectorBuffer[0] = r[i]x1;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[j]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// 아랫 부분 사각형을 vector r에 추가
								r[i]y1 = r[j]y2; // 윗 부분 A를 변환
							}
						}
						else if (r[i]y1 < r[j]y1) // y축으로 A가 B보다 아래에 있을 때 (A)4
						{
							r[i]y2 = r[j]y1; // 윗 부분 A를 변환
						}
						else if (r[i]y2 > r[j]y2) // y축으로 A가 B보다 위에 있을 때 (A)3
						{
							r[i]y1 = r[j]y2; // 윗 부분 A를 변환
						}
						else printf("Error out of A -> E\n");
					}
					else if (r[i]x1 <= r[j]x1 && r[i]x2 >= r[j]x2) // x 축으로 B가 A에 포함되는 것 (A')
					{
						if (r[i]y1 <= r[j]y1 && r[i]y2 >= r[j]y2) // y축으로 B가 A에 포함될 때 A'1
						{
							r[j]x1 = -1;
							r[j]y1 = -1; //꼭 애네까지 해야해?
							r[j]x2 = -1;
							r[j]y2 = -1;
							//isTrueEmplaceBack = false;
							//break; // 현재의 i는 고냥 버린다. -> 필요없는 놈!!
						}
						else if (r[i]y1 > r[j]y1 && r[i]y2 < r[j]y2) // y축으로 B가 A보다 넓을 때 A'2
						{
							if (r[i]x1 == r[j]x1 && r[i]x2 == r[j]x2) // B를 날려버려! 안나옴 이런상황
							{
								printf("A'2 Pass Error");
								isTrueEmplaceBack = false;
								break; // 현재의 i는 고냥 버린다. -> 필요없는 놈!!

							}
							else {
								insertVectorBuffer[0] = r[j]x1;
								insertVectorBuffer[1] = r[j]y1;
								insertVectorBuffer[2] = r[j]x2;
								insertVectorBuffer[3] = r[i]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// 아랫 부분 사각형을 vector r에 추가
								r[j]y1 = r[i]y2; // 윗 부분 B를 변환
							}
						}
						else if (r[i]y1 > r[j]y1) // y축으로 A가 B보다 아래에 있을 때 A'4
						{
							r[j]y2 = r[i]y1; // 윗 부분 A를 변환
						}
						else if (r[i]y2 < r[j]y2) // y축으로 A가 B보다 위에 있을 때 (A)3
						{
							r[j]y1 = r[i]y2; // 윗 부분 A를 변환
						}
						else printf("Error out of A' -> E\n");
					}
					else if (r[i]y1 >= r[j]y1 && r[i]y2 <= r[j]y2) // y 축으로 A가 B에 포함될 때 (B)
					{
						if (r[i]x1 >= r[j]x1 && r[i]x2 <= r[j]x2) // x축으로 A가 B에 포함될 때 (B)1
						{
							isTrueEmplaceBack = false;
							break; // 현재의 i는 고냥 버린다. -> 필요없는 놈!!
						}
						else if (r[i]x1 < r[j]x1 && r[i]x2 > r[j]x2) // x축으로 A가 B보다 넓을 때 (B2
						{
							if (r[i]y1 == r[j]y1 && r[i]y2 == r[j]y2) // B를 날려버려!
							{
								r[j]x1 = -1;
								r[j]y1 = -1; //꼭 애네까지 해야해?
								r[j]x2 = -1;
								r[j]y2 = -1;
							}
							else
							{
								insertVectorBuffer[0] = r[j]x2;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[i]y2;

								childRectCont.emplace_back(insertVectorBuffer);		// 오른쪽 부분 사각형을 vector r에 추가
								r[i]x2 = r[j]x1; // 왼쪽 부분 A를 변환
							}
						}
						else if (r[i]x1 < r[j]x1) // x축으로 A가 B보다 왼쪽에 있을 때 (B)3
						{
							r[i]x2 = r[j]x1; // 왼쪽 부분 A를 변경
						}
						else if (r[i]x2 > r[j]x2) // x축으로 A가 B보다 오른쪽에 있을 때 (B)4
						{
							r[i]x1 = r[j]x2; // 오른쪽 부분 A를 변환
						}
						else printf("Error out of B -> E\n");
					}
					else if (r[i]y1 <= r[j]y1 && r[i]y2 >= r[j]y2) // y 축으로 B가 A에 포함될 때 (B')
					{
						if (r[i]x1 <= r[j]x1 && r[i]x2 >= r[j]x2) // x축으로 B가 A에 포함될 때 (B'1)
						{
							r[j]x1 = -1;
							r[j]y1 = -1; //꼭 애네까지 해야해?
							r[j]x2 = -1;
							r[j]y2 = -1;
							//isTrueEmplaceBack = false;
							//break; // 현재의 i는 고냥 버린다. -> 필요없는 놈!!
						}
						else if (r[i]x1 > r[j]x1 && r[i]x2 < r[j]x2) // x축으로 A가 B보다 넓을 때 (B'2
						{
							if (r[i]y1 == r[j]y1 && r[i]y2 == r[j]y2) // A를 날려버려!
							{
								printf("b'2 Error");
								isTrueEmplaceBack = false;
								break; // 현재의 i는 고냥 버린다. -> 필요없는 놈!!
								//r[j]x1 = -j;
								//r[j]y1 = -j;
								//r[j]x2 = -j + 1;
								//r[j]y2 = -j + 1;
							}
							else
							{
								insertVectorBuffer[0] = r[i]x2;
								insertVectorBuffer[1] = r[j]y1;
								insertVectorBuffer[2] = r[j]x2;
								insertVectorBuffer[3] = r[j]y2;

								childRectCont.emplace_back(insertVectorBuffer);		// 오른쪽 부분 사각형을 vector r에 추가
								r[j]x2 = r[i]x1; // 왼쪽 부분 B를 변환
							}
						}
						else if (r[i]x1 > r[j]x1) // x축으로 B가 A보다 왼쪽에 있을 때 (B'3
						{
							r[j]x2 = r[i]x1; // 왼쪽 부분 A를 변경
						}
						else if (r[i]x2 < r[j]x2) // x축으로 B가 A보다 오른쪽에 있을 때 (B'4
						{
							r[j]x1 = r[i]x2; // 오른쪽 부분 A를 변환
						}
						else printf("Error out of B' -> E\n");
					}
					else if (r[i]x1 <= r[j]x1 && r[i]x2 >= r[j]x2 && r[i]y1 <= r[j]y1 && r[i]y2 >= r[j]y2)  // C 야 안녕히가세요!
					{
						printf("C is the Error \n");
						r[j]x1 = -1;
						r[j]y1 = -1; //꼭 애네까지 해야해?
						r[j]x2 = -1;
						r[j]y2 = -1;
					}
					else // D유형... 
					{
						if (r[i]x2 > r[j]x1 && r[i]x1 < r[j]x1) 
						{
							if (r[i]y2 > r[j]y2)	// D1
							{
								insertVectorBuffer[0] = r[j]x1;
								insertVectorBuffer[1] = r[j]y2;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[i]y2;

								childRectCont.emplace_back(insertVectorBuffer);		// 사각형 추가
								
								r[i]x2 = r[j]x1;
							}
							else if (r[i]y2 < r[j]y2) //D2
							{
								insertVectorBuffer[0] = r[j]x1;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[j]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// 사각형 추가
								r[i]x2 = r[j]x1;
							}
							else printf("Error D2 out\n");
						}
						else if (r[i]x1 < r[j]x2 && r[i]x1 > r[j]x1)
						{
							if (r[i]y2 > r[j]y2)	// D3
							{
								insertVectorBuffer[0] = r[i]x1;
								insertVectorBuffer[1] = r[j]y2;
								insertVectorBuffer[2] = r[j]x2;
								insertVectorBuffer[3] = r[i]y2;

								childRectCont.emplace_back(insertVectorBuffer);		// 사각형 추가
								r[i]x1 = r[j]x2;
							}
							else if (r[i]y2 < r[j]y2) //D4
							{
								insertVectorBuffer[0] = r[i]x1;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[j]x2;
								insertVectorBuffer[3] = r[j]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// 사각형 추가
								r[i]x1 = r[j]x2;
							}
							else printf("Error D4 out\n");
						}
						else printf("Error out of D -> E\n");
					}
				}

			}

			if (isTrueEmplaceBack) {
				answer += (r[i]x2 - r[i]x1) * (r[i]y2 - r[i]y1);
				printf("index : %d   -   %d \n", i, (r[i]x2 - r[i]x1) * (r[i]y2 - r[i]y1));
				//myRectCont.emplace_back(r[i]); // 짤리고 짤린 A는 드디어 추가됩니다.
				if ((r[i]x2 - r[i]x1) * (r[i]y2 - r[i]y1) <= 0) {
					printf("\n 0 혹은 음수가 나왔습니다. 잘못 구한 넓이가 존재합니다. ");
				}
			}
			else {
				isTrueEmplaceBack = true;
			}
		}
	}

	answer += r[inRectContSize - 1]x1 >= 0
		? (r[inRectContSize - 1]x2 - r[inRectContSize - 1]x1) * (r[inRectContSize - 1]y2 - r[inRectContSize - 1]y1)
		: 0;

	printf("\n 최종적으로 벡터의 크기는, %d 였습니다.", inRectContSize);

	//long long answer = r[inRectContSize - 1]x1 >= 0
	//	? (r[inRectContSize - 1]x2 - r[inRectContSize - 1]x1) * (r[inRectContSize - 1]y2 - r[inRectContSize - 1]y1)
	//	: 0;
	//printf("\n");
	//for (auto iter : myRectCont) {
	//	answer += iter.GetSize();
	//	printf("%d  ", iter.GetSize());
	//}

	return answer;
}