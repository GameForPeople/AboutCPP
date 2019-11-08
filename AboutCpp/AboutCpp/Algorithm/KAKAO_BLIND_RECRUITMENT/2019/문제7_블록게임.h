#pragma once

// ¹ÌÇØ°á

#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

using namespace std;

class BoardManager
{
	vector<vector<int>>		board;
	

public:
	__inline BoardManager(vector<vector<int>> InBoard) : board(InBoard)
	{
		//int sizeBuffer = InBoard.size();

		//lockLine.reserve(sizeBuffer);
		//
		//while(sizeBuffer--)
		//	lockLine.emplace_back(true);
	}

public:
	void CalculateResult()
	{
		vector<bool> lockBlock(201, false);
		vector<bool> lockLine(board.size(), false);

		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board.size(); ++j)
			{
				if (board[i][j] != 0)
				{
					if (!lockBlock[board[i][j]]) 
					{
						if (j != board.size() - 1) {

						}
					}
				}
			}
		}
	}
};

void Solution(vector<vector<int>> InBoard)
{
	BoardManager boardManager(InBoard);

	boardManager.CalculateResult();
}