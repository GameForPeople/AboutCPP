#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

namespace ����Ʈ�ٹ�
{
	using namespace std;

	using _MusicKeyType = int;
	using _PlayCountType = int;
	using _MusicType = std::pair< _MusicKeyType, _PlayCountType>;

	struct cmp {
		bool operator()(_MusicType& a, _MusicType& b) {
			return a.second == b.second
				? a.first > b.first
				:  a.second < b.second;
		}
	};

	using _GenreMusicType = std::priority_queue < _MusicType, std::vector< _MusicType>, cmp >;

	std::vector<int> solution(vector<string> genres, vector<int> plays) 
	{
		std::map<std::string, _GenreMusicType> genreSortCont;

		// �Է� ��, Map���� �����ؼ� ����.
		for (int i = 0; i < genres.size(); ++i)
		{
			if (auto iter = genreSortCont.find(genres[i])
				; iter == genreSortCont.end())
			{
				_GenreMusicType tempCont;
				tempCont.emplace(std::make_pair(i, plays[i]));	// ���ο� �帣�� �����, �ش� �帣�� ���� ������ �־��ݴϴ�.
				genreSortCont.emplace(std::make_pair(genres[i], tempCont)); // ���� �帣�� ��ü �帣 �з� �����̳ʿ� �־��ݴϴ�.
			}
			else
			{
				iter->second.emplace(std::make_pair(i, plays[i]));	// ������ �ִ� �帣�� ���Ǹ� �־��ݴϴ�.
			}
		}

		// �� �帣�� ������� Sort
		//auto compFunctor = [](const _GenreMusicType& a,const _GenreMusicType& b) noexcept -> bool
		//{
		//	return a.size() < b.size();
		//};
		//
		//std::priority_queue<_GenreMusicType, std::vector<_GenreMusicType>, decltype(compFunctor)> sizeSortCont(compFunctor);
		
		std::vector<_GenreMusicType> sizeSortCont;
		sizeSortCont.reserve(genreSortCont.size());

		for (auto& iter : genreSortCont)
		{
			sizeSortCont.push_back(iter.second);
		}

		//std::sort(sizeSortCont.begin(), sizeSortCont.end());

		// 2���� �̾Ƽ� ���� �����.
		std::vector<_MusicKeyType> retCont;
		retCont.reserve(sizeSortCont.size() * 2);

		for (auto& cont : sizeSortCont)
		{
			for (int i = 0 ; i < 2; ++i)
			{
				//retCont.emplace_back(cont.top());
				cont.pop();
				
				if (!cont.size()) break;
			}
		}

		return retCont;
	}
}
