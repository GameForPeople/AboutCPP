#pragma once

#include<string>
#include<vector>
#include<iostream>
#include <unordered_map>

namespace ¿ß¿Â
{
	int solution(std::vector<std::vector<std::string>> clothes) 
	{
		std::vector<std::pair<std::string, std::vector<std::string>>> myCont;

		for (auto& cloth : clothes)
		{
			bool isFind = false;
			for (auto& type : myCont)
			{
				if (cloth[1].compare(type.first) == 0)
				{
					isFind = true;
					type.second.emplace_back(cloth[0]);
				}
			}
			if (isFind == false)
			{
				auto emplaced = myCont.emplace_back();
				emplaced.first = cloth[1];
				emplaced.second.emplace_back(cloth[0]);
			}
		}

		int answer = 1;
		for (const auto& clothCont : myCont)
		{
			answer *= (clothCont.second.size() + 1);
		}

		return answer - 1;
	}


	int otherSolution(std::vector<std::vector<std::string>> clothes)
	{
		using namespace std;
		
		int answer = 1;

		std::unordered_map <string, int> cont;

		for (int i = 0, size = clothes.size(); i < size; ++i)
		{
			++cont[clothes[i][1]];
		}

		for (auto it = cont.begin(); it != cont.end(); ++it)
		{
			answer *= (it->second + 1);
		}

		--answer;
		 
		return answer;
	}
}