#pragma once

// �ش� ���� �ذ����� ����... ���� �����ΰž�...

#include <string>
#include <vector>

using namespace std;

static int INDEX_BUFFER{ 0 };

class Core {
public:
	int coreCoolTime;
	int remainingTime;

	__inline Core(int inCoolTime) :coreCoolTime(inCoolTime), remainingTime(0) {}
	__inline Core(int inCoolTime, int inRemainingTime) : coreCoolTime(inCoolTime), remainingTime(inRemainingTime) {}
};

int solution(int n, vector<int> cores) {

	vector<Core> coreArr{};

	for (auto i : cores) {
		if (n) {
			n--;
			coreArr.emplace_back(i, i);
			std::cout << " " << ++INDEX_BUFFER << "��° �ھ �����ƽ��ϴ�. �ð��� : " << i << " �Դϴ�!" << std::endl;
		}
		else break;
	}

	int minValue{};

	while (n) {
		minValue = coreArr[0].remainingTime;

		for (auto i : coreArr) {
			if (i.remainingTime < minValue)
				minValue = i.remainingTime;
		}

		for (auto &i : coreArr) {
			i.remainingTime -= minValue;

			if (i.remainingTime == 0) {
				n--;
				i.remainingTime = i.coreCoolTime;
			}

			if (!n)
				break;
		}

		if (!n)
			break;

		INDEX_BUFFER = 0;

		for (auto i : coreArr) {
			std::cout << " " << ++INDEX_BUFFER << " ��° �ھ��� ���� �ð��� " << i.remainingTime << " �Դϴ�." << std::endl;
		}

		std::cout << " " << "���� �ϰ��� ������!! " << n << " �Դϴ�." << std::endl;
	}

	int bigValue = 0;
	int indexBuffer{ 0 };

	for (int i = 0; i < coreArr.size(); i++) {
		if (coreArr[i].remainingTime > bigValue) {
			bigValue = coreArr[i].remainingTime;
			indexBuffer = i;
		}
	}

	return indexBuffer + 1;
}

/*
#include <string>
#include <vector>

using namespace std;

static int INDEX_BUFFER{0};

class Core {
public:
	int coreCoolTime;
	int remainingTime;

	__inline Core(int inCoolTime) :coreCoolTime(inCoolTime), remainingTime(0) {}
};

int solution(int n, vector<int> cores) {

	vector<Core> coreArr{};

	for (auto i : cores) {
		coreArr.emplace_back(i);
		std::cout << " " << ++INDEX_BUFFER << "��° �ھ �����ƽ��ϴ�. �ð��� : " << i << " �Դϴ�!" << std::endl;
	}

	int minValue{};

	while (n) {
		for (auto &i : coreArr) {
			if (i.remainingTime == 0) {
				n--;
				i.remainingTime = i.coreCoolTime;
			}
			if (!n)
				break;
		}

		if (!n)
			break;

		minValue = coreArr[0].remainingTime;

		for (auto i : coreArr) {
			if (i.remainingTime < minValue)
				minValue = i.remainingTime;
		}

		for (auto &i : coreArr) {
			i.remainingTime -= minValue;
		}

		INDEX_BUFFER = 0;

		for (auto i : coreArr) {
			std::cout << " " << ++INDEX_BUFFER << " ��° �ھ��� ���� �ð��� " << i.remainingTime << " �Դϴ�." << std::endl;
		}
	}

	int bigValue = 0;
	int indexBuffer{ 0 };

	for (int i = 0; i < coreArr.size(); i++) {
		if (coreArr[i].remainingTime > bigValue) {
			bigValue = coreArr[i].remainingTime;
			indexBuffer = i;
		}
	}

	return indexBuffer + 1;
}
*/