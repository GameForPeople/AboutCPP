#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

namespace 베스트앨범
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

		// 입력 값, Map으로 정리해서 적재.
		for (int i = 0; i < genres.size(); ++i)
		{
			if (auto iter = genreSortCont.find(genres[i])
				; iter == genreSortCont.end())
			{
				_GenreMusicType tempCont;
				tempCont.emplace(std::make_pair(i, plays[i]));	// 새로운 장르를 만들고, 해당 장르의 지금 음악을 넣어줍니다.
				genreSortCont.emplace(std::make_pair(genres[i], tempCont)); // 만든 장르를 전체 장르 분류 컨테이너에 넣어줍니다.
			}
			else
			{
				iter->second.emplace(std::make_pair(i, plays[i]));	// 기존에 있던 장르는 음악만 넣어줍니다.
			}
		}

		// 각 장르를 사이즈로 Sort
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

		// 2개씩 뽑아서 정답 만들기.
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
