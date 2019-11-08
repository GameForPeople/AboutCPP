#pragma once

#include <iostream>

using namespace std;

namespace CUSTOM_NODE_Queue
{
	template <typename DATA>
	class CustomNode
	{
		DATA data;

	public:
		CustomNode* left;
		CustomNode* right;

	public:
		CustomNode(const DATA& InData)
			: data(InData), left(nullptr), right(nullptr)
		{}

		CustomNode(DATA InData, CustomNode* InLeft, CustomNode* InRight)
			: data(InData), left(InLeft), right(InRight)
		{};

		void Print()
		{
			std::cout << "dataÀÇ °ªÀº : " << data << "\n";
		}
	};

	template <typename DATA>
	class NodeManager
	{
		CustomNode<DATA>* pStart;
		CustomNode<DATA>* pEnd;

	public:
		NodeManager() : pStart(nullptr), pEnd(nullptr)
		{}

		CustomNode<DATA>* Push(const DATA& InDATA)
		{
			CustomNode<DATA>* pRetNode = new CustomNode<DATA>(InDATA);
			
			if (pEnd == nullptr)
			{
				pStart = pRetNode;
				pEnd = pRetNode;
			}
			else
			{
				pEnd->right = pRetNode;
				pRetNode->left = pEnd;

				pEnd = pRetNode;
			}

			return pRetNode;
		}

		CustomNode<DATA>* Pop(bool& retBool)
		{
			if (pStart == nullptr)
			{
				retBool = false;
				return nullptr;
			}
			else
			{
				CustomNode<DATA>* pRetNode = pStart;

				if (pStart->right == nullptr)
				{
					pStart = nullptr;
					pEnd = nullptr;
				}
				else
				{
					pStart = pStart->right;
				}

				retBool = true;
				return pRetNode;
			}
		}

		void Print()
		{
			CustomNode<DATA>* pNewNode = pStart;

			while (pNewNode->right != nullptr)
			{
				pNewNode->Print();
				pNewNode = pNewNode->right;
			}
		}
	};

	//template <class DATA> //example
	void func()
	{
		NodeManager<int> nodeManager;

		CustomNode<int>* pRetNode = nullptr; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<int>* pRetNode1 = nullptr; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<int>* pRetNode2 = nullptr; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<int>* pRetNode3 = nullptr; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<int>* pRetNode4 = nullptr; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<int>* pRetNode5 = nullptr; //= new CustomNode(count++, nullptr, nullptr);

		pRetNode = nodeManager.Push(1);
		pRetNode1 = nodeManager.Push(2);
		pRetNode2 = nodeManager.Push(3);
		pRetNode3 = nodeManager.Push(4);
		pRetNode4 = nodeManager.Push(5);
		pRetNode5 = nodeManager.Push(6);

		std::cout << "Start Print \n\n";

		nodeManager.Print();

		std::cout << "Push - Pop \n\n";

		bool a;
		nodeManager.Pop(a);
		nodeManager.Pop(a);

		nodeManager.Print();

		std::cout << "\n\n";
	}
}