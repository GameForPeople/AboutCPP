#pragma once

#include <iostream>
#include<vector>

using namespace std;


int MinFunction(int a, int b) {
	return a < b
		? a
		: b;
}


int solution(vector<vector<int>> board)
{
	int maxCount{ 0 };

	if (board.size() == 1 || board[0].size() == 1)
	{
		for (auto i : board) {
			for (auto j = i.cbegin(); j < i.cend(); j++)
				if (*j == 1) return 1;
		}
	}
	else {
		for (int i = 1; i < board.size(); i++) {
			for (int j = 1; j < board[0].size(); j++) {
				if (board[i][j]) {
					board[i][j] = 1 + MinFunction(MinFunction(board[i - 1][j - 1], board[i - 1][j]), board[i][j - 1]);

					if (board[i][j] > maxCount) {
						maxCount = board[i][j];
					}
				}
			}
		}
	}
	return maxCount * maxCount;
};