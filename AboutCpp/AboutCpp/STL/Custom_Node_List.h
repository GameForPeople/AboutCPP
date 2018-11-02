#pragma once

#include <iostream>

using namespace std;

namespace CUSTOM_NODE_LIST
{
	template <typename DATA>
	class CustomNode
	{
		DATA data;

	public:
		CustomNode* left;
		CustomNode* right;

	public:
		CustomNode(DATA InData, CustomNode* InLeft, CustomNode* InRight)
			: data(InData), left(InLeft), right(InRight)
		{};

		void Print()
		{
			std::cout << "data의 값은 : "<< data << "\n";
		}
	};

	int count = 0;

	template <typename T>
	class NodeManager
	{
		CustomNode<T>* WaitNodeCont;

	public:
		NodeManager() 
		{ 
			WaitNodeCont = new CustomNode<T>(0, nullptr, nullptr);
			//WaitNodeCont = nullptr;
		}

		CustomNode<T>* Create()
		{
			CustomNode<T>* pRetNode = new CustomNode<T>(count++, nullptr, nullptr);

			WaitNodeCont->left = pRetNode;
			pRetNode->right = WaitNodeCont;
			WaitNodeCont = pRetNode;

			return pRetNode;
		}

		void Push(CustomNode<T>* pRetNode)
		{
			// 한칸씩 밀고는 귀찮으니 포인터만 슥.
			WaitNodeCont->left = pRetNode;
			pRetNode->right = WaitNodeCont;
			pRetNode->left = nullptr;
			WaitNodeCont = pRetNode;
		}

		void Pop(CustomNode<T>* pRetNode)
		{
			// 기존 노드만 이어주면 됩니다.
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
			CustomNode<T>* newNode = WaitNodeCont;
			
			while (newNode->right != nullptr)
			{
				newNode->Print();
				newNode = newNode->right;
			}
		}
	};

	template <class T> //example
	void func()
	{
		NodeManager<T> nodeManager;
		NodeManager<T> nodeManager2;
		
		CustomNode<T>* pRetNode   =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<T>* pRetNode1  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<T>* pRetNode2  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<T>* pRetNode3  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<T>* pRetNode4  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);
		CustomNode<T>* pRetNode5  =nullptr ; //= new CustomNode(count++, nullptr, nullptr);

		pRetNode = nodeManager.Create();
		pRetNode1 = nodeManager.Create();
		pRetNode2 = nodeManager.Create();
		pRetNode3 = nodeManager.Create();
		pRetNode4 = nodeManager.Create();
		pRetNode5 = nodeManager.Create();

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