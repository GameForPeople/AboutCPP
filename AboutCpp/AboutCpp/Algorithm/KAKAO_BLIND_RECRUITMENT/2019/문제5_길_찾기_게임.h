#pragma once

// 미해결


#include <iostream>
#include <string>
#include <vector>

#include <algorithm>

using namespace std;

struct Position 
{
	int				x;
	int				y;

public:
	__inline Position(vector<int> InPos) : x(InPos[0]), y(InPos[1])
	{}
};

class Node
{
	int				originIndex;
	Position		pos;

	Node*			upNode;
	Node*			leftNode;
	Node*			rightNode;

	int				upIndex;
	int				leftIndex;
	int				rightIndex;

	//int				minX;
	//int				maxX;

public:
	__inline Node(const int InIndex, const vector<int> InPos) 
		: originIndex(InIndex + 1), pos(InPos), upIndex(-1), leftIndex(-1), rightIndex(-1) //, minX(0), maxX(100000)
	{}

	__inline ~Node() = default;

public:
	__inline const Position& GetPos() const { return pos; }

	__inline Node* GetInstance()
	{
		return this;
	}

	__inline int GetOriginIndex() { return originIndex; }

	__inline int GetUpIndex() { return upIndex; }

	__inline int GetLeftIndex() { return leftIndex;  }

	__inline int GetRightIndex() { return rightIndex; }


	__inline bool SetUpIndex(const int InUpIndex) 
	{ 
		if (upIndex == -1) 
		{
			upIndex = InUpIndex;
			return true;
		}
		return false;
	}

	__inline void SetLeftIndex(const int InLeftIndex) { if(leftIndex == -1)leftIndex = InLeftIndex; }

	__inline void SetRightIndex(const int InRightIndex) { if(rightIndex == -1) rightIndex = InRightIndex; }



	__inline void SetUpNode(Node* InUpNode) { if (upNode == NULL) upNode = InUpNode; }

	__inline void SetLeftNode(Node* InLeftNode) { if (leftNode == NULL)leftNode = InLeftNode; }

	__inline void SetRightNode(Node* InRightNode) { if (rightNode == NULL) rightNode = InRightNode; }


	__inline void Print() const
	{
		//std::cout << originIndex << " 번 Position  X = " << pos.x << "   Y = " << pos.y << "\n";
		if(leftNode != NULL && rightNode != NULL)
			std::cout << originIndex << " 번 LeftIndex = " << leftNode->GetOriginIndex() << "   RightIndex = " << rightNode->GetOriginIndex() << "\n";
	}

};

class NodeManager
{
	vector<Node>	nodes;
	vector<int>		preOrder;
	vector<int>		postOrder;


public:
	__inline NodeManager(vector<vector<int>> InNodeInfos)
	{
		nodes.reserve(InNodeInfos.size());
		preOrder.reserve(InNodeInfos.size());
		postOrder.reserve(InNodeInfos.size());

		for (int i = 0; i < InNodeInfos.size(); ++i)
		{
			nodes.emplace_back(i, InNodeInfos[i]);
		}
	}

public:
	void MakeTree()
	{
		sort(nodes.begin(), nodes.end(), [](Node a, Node b)->bool
		{
			if (a.GetPos().y == b.GetPos().y)
			{
				return a.GetPos().x < b.GetPos().x;
			}
			else
			{
				return a.GetPos().y > b.GetPos().y;
			}
		});

		RecursionMakeTree(0, 100000, 0);
	}

	void RecursionMakeTree(int nowIndex, int maxX, int minX)
	{
		// 으악! 스파게티 코드입니다....;;
		for (int i = nowIndex + 1; i < nodes.size(); ++i)
		{
			if (nodes[nowIndex].GetPos().y > nodes[i].GetPos().y)
			{

				if (nodes[nowIndex].GetPos().x > nodes[i].GetPos().x &&
					minX < nodes[i].GetPos().x )
				{
					//nodes[nowIndex].SetLeftNode( &(nodes[i]) );
					//nodes[i].SetUpNode( &(nodes[nowIndex]));

					if (nodes[i].SetUpIndex(nowIndex)) 
					{
						nodes[nowIndex].SetLeftIndex(i);
						
						if(nodes[nowIndex].GetPos().x < maxX)
							RecursionMakeTree(i, nodes[nowIndex].GetPos().x, minX);
						else
							RecursionMakeTree(i, maxX, minX);
					}
				}

				if (nodes[nowIndex].GetPos().x < nodes[i].GetPos().x &&
					maxX > nodes[i].GetPos().x)
				{
					//nodes[nowIndex].SetRightNode( &(nodes[i]));
					//nodes[i].SetUpNode( &(nodes[nowIndex]));

					if (nodes[i].SetUpIndex(nowIndex))
					{
						nodes[nowIndex].SetRightIndex(i);

						if (nodes[nowIndex].GetPos().x > minX)
							RecursionMakeTree(i, maxX, nodes[nowIndex].GetPos().x);
						else
							RecursionMakeTree(i, maxX, minX);
					}
				}

			}
		}
	}

	void DoPreOrder()
	{
		RecursionProOrder(0);
	}

	void RecursionProOrder(const int InIndex)
	{
		preOrder.emplace_back(nodes[InIndex].GetOriginIndex());

		if (nodes[InIndex].GetLeftIndex() != -1)
		{
			RecursionProOrder(nodes[InIndex].GetLeftIndex());
		}
		
		if (nodes[InIndex].GetRightIndex() != -1)
		{
			RecursionProOrder(nodes[InIndex].GetRightIndex());
		}
	}

	void DoPostOrder()
	{
		RecursionPostOrder(0);
	}

	void RecursionPostOrder(const int InIndex)
	{
		if (nodes[InIndex].GetLeftIndex() != -1)
		{
			RecursionPostOrder(nodes[InIndex].GetLeftIndex());
		}

		if (nodes[InIndex].GetRightIndex() != -1)
		{
			RecursionPostOrder(nodes[InIndex].GetRightIndex());
		}

		postOrder.emplace_back(nodes[InIndex].GetOriginIndex());
	}

	//for Debug
	void PrintAllNode(const bool InBoolValue) const
	{
		if (InBoolValue) 
		{
			std::cout << "전위 순회는 ";

			for (int i : preOrder)
			{
				std::cout << "  " << i;
			}
		}
		else
		{
			std::cout << "후위 순회는 ";

			for (int i : postOrder)
			{
				std::cout << "  " << i;
			}
		}
	}
};


//vector<vector<int>>
void Solution(vector<vector<int>> InNodeInfos)
{
	NodeManager nodeManager(InNodeInfos);

	nodeManager.MakeTree();

	//nodeManager.PrintAllNode();
	nodeManager.DoPreOrder();
	nodeManager.PrintAllNode(true);

	nodeManager.DoPostOrder();
	nodeManager.PrintAllNode(false);
}