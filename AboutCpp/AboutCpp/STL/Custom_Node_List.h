#pragma once

#include <iostream>

using namespace std;

namespace CUSTOM_NODE_LIST
{
	class CustomNode
	{
		int a;

	public:
		CustomNode* left;
		CustomNode* right;

	public:
		CustomNode(int InA, CustomNode* InLeft, CustomNode* InRight)
			: a(InA), left(InLeft), right(InRight) 
		{};

		void Print()
		{
			std::cout << "a의 값은 : "<< a << "\n";
		}
	};

	int count = 0;

	class NodeManager
	{
		CustomNode* WaitNodeCont;

	public:
		NodeManager() 
		{ 
			WaitNodeCont = new CustomNode(0, nullptr, nullptr);
			//WaitNodeCont = nullptr;
		}

		void Create(CustomNode* pRetNode)
		{
			pRetNode = new CustomNode(count++, nullptr, nullptr);

			WaitNodeCont->left = pRetNode;
			pRetNode->right = WaitNodeCont;
			WaitNodeCont = pRetNode;
		}

		void Push(CustomNode* pRetNode)
		{
			// 한칸씩 밀고는 귀찮으니 포인터만 슥.
			WaitNodeCont->left = pRetNode;
			pRetNode->right = WaitNodeCont;
			pRetNode->left = nullptr;
			WaitNodeCont = pRetNode;
		}

		void Pop(CustomNode* pRetNode)
		{
			// 기존 노드만 새로 이어주면 됩니다.
			if (pRetNode->left == nullptr)
			{
				WaitNodeCont = WaitNodeCont->right;
				WaitNodeCont->left = nullptr;

				return;
			}
			
			pRetNode->left->right = pRetNode->right;
			pRetNode->right->left = pRetNode->left;
		}

		void Print()
		{
			CustomNode* newNode = WaitNodeCont;
			
			while (newNode->right != nullptr)
			{
				newNode->Print();
				newNode = newNode->right;
			}
		}
	};

	void func()
	{
		NodeManager nodeManager;
		NodeManager nodeManager2;
		
		CustomNode* pRetNode   =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode* pRetNode1  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode* pRetNode2  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode* pRetNode3  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode* pRetNode4  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode* pRetNode5  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);

		nodeManager.Create(pRetNode);
		nodeManager.Create(pRetNode1);
		nodeManager.Create(pRetNode2);
		nodeManager.Create(pRetNode3);
		nodeManager.Create(pRetNode4);
		nodeManager.Create(pRetNode5);

		std::cout << "Start Print \n\n";

		nodeManager.Print();
		nodeManager2.Print();

		std::cout << "Push - Pop \n\n";

		nodeManager.Pop(pRetNode3);
		nodeManager2.Push(pRetNode3);

		nodeManager.Print();
		nodeManager2.Print();
	}
}