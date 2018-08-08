#pragma once

#include <vector>
#include <iostream>

using namespace std;

class nodeData {
public:
	int boolValue{ 0 };
	int spareValue{ 0 };

	//vector<bool> cont;
	__inline nodeData(int inBoolValue, int inSpareValue) : boolValue(inBoolValue), spareValue(inSpareValue)
	{

	}

	//__inline nodeData(int inBoolValue, int inSpareValue, bool inbValue) : boolValue(inBoolValue), spareValue(inSpareValue)
	//{
	//	cont.emplace_back(inbValue);
	//}
	//
	//__inline nodeData(vector<bool> inCont, int inBoolValue, int inSpareValue) : cont(inCont), boolValue(inBoolValue), spareValue(inSpareValue)
	//{
	//
	//}
	//
	//__inline nodeData(vector<bool> inCont, int inBoolValue, int inSpareValue, bool inbValue) : cont(inCont), boolValue(inBoolValue), spareValue(inSpareValue)
	//{
	//	cont.emplace_back(inbValue);
	//}
	//
	//__inline void Set(const nodeData& a)
	//{
	//	boolValue = a.boolValue;
	//	spareValue = a.spareValue;
	//	cont = a.cont;
	//}

	__inline nodeData() = default;
	__inline ~nodeData() = default;
};

int solution(int n) {

	vector<nodeData> oldCont{};
	vector<nodeData> newCont{};
	
	for (int i = 0; i < 2*n; i++)
	{
		if (i == 0) {
			newCont.emplace_back(1, n - 1);
		}
		else {
			for (auto j : oldCont) {
				if (j.spareValue) {
					//newCont.emplace_back(j.cont, j.boolValue + 1, j.spareValue - 1, true);
					newCont.emplace_back(j.boolValue + 1, j.spareValue - 1);

					if(j.boolValue)
						//newCont.emplace_back(j.cont, j.boolValue - 1, j.spareValue, false);
						newCont.emplace_back(j.boolValue - 1, j.spareValue);
				}
				else if (!(j.spareValue)) {
						//newCont.emplace_back(j.cont, j.boolValue - 1, j.spareValue, false);
						newCont.emplace_back(j.boolValue - 1, j.spareValue);
				}
			}
		}
		oldCont.clear();
		oldCont = newCont;
		newCont.clear();
	}

	return oldCont.size();
}