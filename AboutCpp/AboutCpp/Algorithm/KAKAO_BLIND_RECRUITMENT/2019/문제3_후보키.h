#pragma once

// 미해결

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataBaseTable
{
	vector<vector<string>>		table;

	int							columnSize; // 세로 1 줄이 몇 개의 가로줄로 인가
	int							rowSize; // 가로 1 줄이 몇 개의 세로로 이루어져 있는가

	vector<int>					candidateKeyIndex;
	int							candidateKeyNum;

public:
	__inline DataBaseTable(vector<vector<string>> InRelation) : table (InRelation)
	{
		columnSize = InRelation.size(); 
		rowSize = InRelation[0].size(); 

		std::cout << "  rowSize는 :: " << rowSize << "  Column는 :: " << columnSize << "\n";
	}

	__inline ~DataBaseTable() = default;

public:
	void FindKey()
	{
		FindCandidateKey();
		DeleteCandidateColumnInTable();

		FindSuperKey();
	}

private:
	void FindCandidateKey()
	{
		for (int i = 0; i < rowSize; ++i)
		{
			std::cout << "   " << i << " 번째 컬럼의 평가를 시작합니다." << "\n";

			for (int j = 0; j < columnSize - 1; ++j)
			{
				for (int k = j + 1; k < columnSize; ++k)
				{
					std::cout << " " << j << ": "  << table[j][i] << "      " << k << ":  " << table[k][i] << "\n";

					if (table[j][i].compare(table[k][i]) == 0)
					{
						std::cout << " 이 Column "<< i << "은 CandidateKey가 아닙니다. " << "\n";
						goto OUT_LOOP;
					}
				}
			}

			std::cout << " candidateKey : " << i << " 를 추가했습니다." << "\n";
			candidateKeyIndex.emplace_back(i);

		OUT_LOOP:
			continue;
		}

		candidateKeyNum = candidateKeyIndex.size();
	}

	void DeleteCandidateColumnInTable()
	{
		for (int i = 0; i < columnSize; ++i)
		{
			for (int j = candidateKeyNum - 1; j >= 0; --j)
			{
				table[i].erase(table[i].begin() + candidateKeyIndex[j]);
			}
		}
		rowSize -= candidateKeyNum;
	}

	void FindSuperKey()
	{
		for (int i = 2; i < rowSize; ++i)
		{

		}
	}

	/*
	bool IsSameCandidateKey(const int InIndex)
	{
		for (auto iter : candidateKeyIndex)
		{
			if (iter == InIndex)
				return true;
			else if (iter > InIndex)
				return false;
		}

		return false;
	}
	*/
};

void Solution(vector<vector<string>> InRelation)
{
	DataBaseTable myDB(InRelation);

	myDB.FindKey();

}