#pragma once

#include <iostream>
#include<vector>

using namespace std;

#define MIN(a, b) a < b ? a : b

int MinFunction(int a, int b) {
	return a < b
		? a
		: b;
}


int solution(vector<vector<int>> board)
{
	int height{ (int)board.size() };
	int line{ (int)board[0].size() };

	std::cout << height << " " << line << std::endl;

	int maxCount{ 1 };

	for (int i = 1; i < height; i++) {
		for (int j = 1; j < line; j++) {
			if (board[i][j]) {
				board[i][j] = 1 + MinFunction(MinFunction(board[i - 1][j - 1], board[i - 1][j]), board[i][j - 1] );
				//std::cout << MIN(MIN(board[i - 1][j - 1], board[i - 1][j]), board[i][j - 1]) << std::endl;

				if (board[i][j] > maxCount) {
					maxCount = board[i][j];
				}
			}
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < line; j++) {
			std::cout << " " << board[i][j];
		}
		std::cout << std::endl;
	}

	return maxCount * maxCount;
};