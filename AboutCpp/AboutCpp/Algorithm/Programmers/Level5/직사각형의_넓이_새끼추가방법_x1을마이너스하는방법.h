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

	// x1 Sort�� �������� ����
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

	//printf("A�� ��ǥ�� %d, %d, %d, %d \n", r[93947]x1, r[93947]y1, r[93947]x2, r[93947]y2);

	for (int i = 0; i < inRectContSize - 1; i++) 
	{
		if (r[i]x1 > -1) 
		{
			//if (i == 93947) {
			//	printf("A�� ��ǥ�� %d, %d, %d, %d \n", r[i]x1, r[i]y1, r[i]x2, r[i]y2);
			//	printf(" ");
			//}

			for (int j = i + 1; j < inRectContSize; j++)
			{
				//if (i == 93947) {
				//	if (r[i]x1 > r[i]x2 || r[i]y1 > r[i]y2) {
				//		printf("�׳��� �����̴�!!! �� �ε��� %d �� %d, %d, %d, %d \n", j-1 , r[j - 1]x1, r[j - 1]y1, r[j - 1]x2, r[j - 1]y2);
				//		printf("���� ��ǥ�� %d, %d, %d, %d \n", r[i]x1, r[i]y1, r[i]x2, r[i]y2);
				//	}
				//}
				if (r[j]x1 == -1) // �̹� ���ܵ� ģ���� ��
				{
					isTrueEmplaceBack = false; // �߰�!
				}
				else if (r[i]x1 >= r[j]x2 || r[i]x2 <= r[j]x1 || r[i]y1 >= r[j]y2 || r[i]y2 <= r[j]y1) // ��ġ�� �ʾҴ�.
				{
					continue;
				}
				else // ������ ��
				{
					if (r[i]x1 >= r[j]x1 && r[i]x2 <= r[j]x2) // x ������ A�� B�� ���Ե� �� (A)
					{
						if (r[i]y1 >= r[j]y1 && r[i]y2 <= r[j]y2) // y������ A�� B�� ���Ե� �� (A)1
						{
							isTrueEmplaceBack = false;
							break; // ������ i�� ��� ������. -> �ʿ���� ��!!
						}
						else if (r[i]y1 < r[j]y1 && r[i]y2 > r[j]y2) // y������ A�� B���� ���� �� (A)2
						{
							if (r[i]x1 == r[j]x1 && r[i]x2 == r[j]x2) // B�� ��������!
							{
								r[j]x1 = -1;
								r[j]y1 = -1; //�� �ֳױ��� �ؾ���?
								r[j]x2 = -1;
								r[j]y2 = -1;
							}
							else {
								insertVectorBuffer[0] = r[i]x1;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[j]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// �Ʒ� �κ� �簢���� vector r�� �߰�
								r[i]y1 = r[j]y2; // �� �κ� A�� ��ȯ
							}
						}
						else if (r[i]y1 < r[j]y1) // y������ A�� B���� �Ʒ��� ���� �� (A)4
						{
							r[i]y2 = r[j]y1; // �� �κ� A�� ��ȯ
						}
						else if (r[i]y2 > r[j]y2) // y������ A�� B���� ���� ���� �� (A)3
						{
							r[i]y1 = r[j]y2; // �� �κ� A�� ��ȯ
						}
						else printf("Error out of A -> E\n");
					}
					else if (r[i]x1 <= r[j]x1 && r[i]x2 >= r[j]x2) // x ������ B�� A�� ���ԵǴ� �� (A')
					{
						if (r[i]y1 <= r[j]y1 && r[i]y2 >= r[j]y2) // y������ B�� A�� ���Ե� �� A'1
						{
							r[j]x1 = -1;
							r[j]y1 = -1; //�� �ֳױ��� �ؾ���?
							r[j]x2 = -1;
							r[j]y2 = -1;
							//isTrueEmplaceBack = false;
							//break; // ������ i�� ��� ������. -> �ʿ���� ��!!
						}
						else if (r[i]y1 > r[j]y1 && r[i]y2 < r[j]y2) // y������ B�� A���� ���� �� A'2
						{
							if (r[i]x1 == r[j]x1 && r[i]x2 == r[j]x2) // B�� ��������! �ȳ��� �̷���Ȳ
							{
								printf("A'2 Pass Error");
								isTrueEmplaceBack = false;
								break; // ������ i�� ��� ������. -> �ʿ���� ��!!

							}
							else {
								insertVectorBuffer[0] = r[j]x1;
								insertVectorBuffer[1] = r[j]y1;
								insertVectorBuffer[2] = r[j]x2;
								insertVectorBuffer[3] = r[i]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// �Ʒ� �κ� �簢���� vector r�� �߰�
								r[j]y1 = r[i]y2; // �� �κ� B�� ��ȯ
							}
						}
						else if (r[i]y1 > r[j]y1) // y������ A�� B���� �Ʒ��� ���� �� A'4
						{
							r[j]y2 = r[i]y1; // �� �κ� A�� ��ȯ
						}
						else if (r[i]y2 < r[j]y2) // y������ A�� B���� ���� ���� �� (A)3
						{
							r[j]y1 = r[i]y2; // �� �κ� A�� ��ȯ
						}
						else printf("Error out of A' -> E\n");
					}
					else if (r[i]y1 >= r[j]y1 && r[i]y2 <= r[j]y2) // y ������ A�� B�� ���Ե� �� (B)
					{
						if (r[i]x1 >= r[j]x1 && r[i]x2 <= r[j]x2) // x������ A�� B�� ���Ե� �� (B)1
						{
							isTrueEmplaceBack = false;
							break; // ������ i�� ��� ������. -> �ʿ���� ��!!
						}
						else if (r[i]x1 < r[j]x1 && r[i]x2 > r[j]x2) // x������ A�� B���� ���� �� (B2
						{
							if (r[i]y1 == r[j]y1 && r[i]y2 == r[j]y2) // B�� ��������!
							{
								r[j]x1 = -1;
								r[j]y1 = -1; //�� �ֳױ��� �ؾ���?
								r[j]x2 = -1;
								r[j]y2 = -1;
							}
							else
							{
								insertVectorBuffer[0] = r[j]x2;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[i]y2;

								childRectCont.emplace_back(insertVectorBuffer);		// ������ �κ� �簢���� vector r�� �߰�
								r[i]x2 = r[j]x1; // ���� �κ� A�� ��ȯ
							}
						}
						else if (r[i]x1 < r[j]x1) // x������ A�� B���� ���ʿ� ���� �� (B)3
						{
							r[i]x2 = r[j]x1; // ���� �κ� A�� ����
						}
						else if (r[i]x2 > r[j]x2) // x������ A�� B���� �����ʿ� ���� �� (B)4
						{
							r[i]x1 = r[j]x2; // ������ �κ� A�� ��ȯ
						}
						else printf("Error out of B -> E\n");
					}
					else if (r[i]y1 <= r[j]y1 && r[i]y2 >= r[j]y2) // y ������ B�� A�� ���Ե� �� (B')
					{
						if (r[i]x1 <= r[j]x1 && r[i]x2 >= r[j]x2) // x������ B�� A�� ���Ե� �� (B'1)
						{
							r[j]x1 = -1;
							r[j]y1 = -1; //�� �ֳױ��� �ؾ���?
							r[j]x2 = -1;
							r[j]y2 = -1;
							//isTrueEmplaceBack = false;
							//break; // ������ i�� ��� ������. -> �ʿ���� ��!!
						}
						else if (r[i]x1 > r[j]x1 && r[i]x2 < r[j]x2) // x������ A�� B���� ���� �� (B'2
						{
							if (r[i]y1 == r[j]y1 && r[i]y2 == r[j]y2) // A�� ��������!
							{
								printf("b'2 Error");
								isTrueEmplaceBack = false;
								break; // ������ i�� ��� ������. -> �ʿ���� ��!!
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

								childRectCont.emplace_back(insertVectorBuffer);		// ������ �κ� �簢���� vector r�� �߰�
								r[j]x2 = r[i]x1; // ���� �κ� B�� ��ȯ
							}
						}
						else if (r[i]x1 > r[j]x1) // x������ B�� A���� ���ʿ� ���� �� (B'3
						{
							r[j]x2 = r[i]x1; // ���� �κ� A�� ����
						}
						else if (r[i]x2 < r[j]x2) // x������ B�� A���� �����ʿ� ���� �� (B'4
						{
							r[j]x1 = r[i]x2; // ������ �κ� A�� ��ȯ
						}
						else printf("Error out of B' -> E\n");
					}
					else if (r[i]x1 <= r[j]x1 && r[i]x2 >= r[j]x2 && r[i]y1 <= r[j]y1 && r[i]y2 >= r[j]y2)  // C �� �ȳ���������!
					{
						printf("C is the Error \n");
						r[j]x1 = -1;
						r[j]y1 = -1; //�� �ֳױ��� �ؾ���?
						r[j]x2 = -1;
						r[j]y2 = -1;
					}
					else // D����... 
					{
						if (r[i]x2 > r[j]x1 && r[i]x1 < r[j]x1) 
						{
							if (r[i]y2 > r[j]y2)	// D1
							{
								insertVectorBuffer[0] = r[j]x1;
								insertVectorBuffer[1] = r[j]y2;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[i]y2;

								childRectCont.emplace_back(insertVectorBuffer);		// �簢�� �߰�
								
								r[i]x2 = r[j]x1;
							}
							else if (r[i]y2 < r[j]y2) //D2
							{
								insertVectorBuffer[0] = r[j]x1;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[i]x2;
								insertVectorBuffer[3] = r[j]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// �簢�� �߰�
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

								childRectCont.emplace_back(insertVectorBuffer);		// �簢�� �߰�
								r[i]x1 = r[j]x2;
							}
							else if (r[i]y2 < r[j]y2) //D4
							{
								insertVectorBuffer[0] = r[i]x1;
								insertVectorBuffer[1] = r[i]y1;
								insertVectorBuffer[2] = r[j]x2;
								insertVectorBuffer[3] = r[j]y1;

								childRectCont.emplace_back(insertVectorBuffer);		// �簢�� �߰�
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
				//myRectCont.emplace_back(r[i]); // ©���� ©�� A�� ���� �߰��˴ϴ�.
				if ((r[i]x2 - r[i]x1) * (r[i]y2 - r[i]y1) <= 0) {
					printf("\n 0 Ȥ�� ������ ���Խ��ϴ�. �߸� ���� ���̰� �����մϴ�. ");
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

	printf("\n ���������� ������ ũ���, %d �����ϴ�.", inRectContSize);

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