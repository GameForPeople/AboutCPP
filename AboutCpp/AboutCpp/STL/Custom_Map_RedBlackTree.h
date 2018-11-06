#pragma once

//declare
template <typename KEY, typename VALUE>
class rbTree;

/*
	rbTreeNode�� rbTree�� ���Ǵ� Node��ü�Դϴ�.
	Key-Value ����, �� std::Map�� ������ �޾�, Pair�� ���¸� ��� �ֽ��ϴ�.
 
	#1. Key�� ���Ǵ� ��ü�� ���� ����� ��ü�� ���, Ű�� �񱳿� ���� ������ operator�� �ʿ��մϴ�.

		�ش� ������ ������ �����ϴ�.
			bool operator <(const AAA &rhs) const {
				return aaa < rhs.aaa;
			}

	#2.
*/
template <typename KEY, typename VALUE>
class rbTreeNode {
	friend class rbTree<KEY, VALUE>;

	enum
	{
		RED			=		true	,	//TRUE
		BLACK		=		false		//FALSE
	};

private:
	KEY							key;
	VALUE						value;

	bool						color; // false ( 0 ) == black , true (1) == red;

	rbTreeNode<KEY, VALUE>*		up;
	rbTreeNode<KEY, VALUE>*		left;
	rbTreeNode<KEY, VALUE>*		right;

public:
	// for pNullNode, buffer #1 Key, Value�� ���� �⺻�����ڰ� �ʿ��մϴ�.
	rbTreeNode<KEY, VALUE>() : key(), value(), up(nullptr), left(nullptr), right(nullptr), color(false)
	{}

	// for Insert 1
	rbTreeNode<KEY, VALUE>(const KEY& InKEY, const VALUE& InValue) 
		: key(InKEY), value(InValue), up(nullptr), left(nullptr), right(nullptr), color(false)
	{}

	// for Insert 2
	rbTreeNode<KEY, VALUE>(const KEY& InKEY, const VALUE& InValue, rbTreeNode<KEY, VALUE>* pInNode, const bool& InColor)
		: key(InKEY), value(InValue), up(pInNode), left(pInNode), right(pInNode), color(InColor)
	{}

	~rbTreeNode<KEY, VALUE>() = default;

public:
	KEY GetKey() const
	{
		return key;
	}

	VALUE GetValue() const
	{
		return value;
	}

	// like pair (same Function --> GetKey() )
	KEY First() const 
	{
		return key;
	}

	// like pair (same Function --> GetValue() )
	VALUE Second() const
	{
		return value;
	}
};

template <typename KEY, typename VALUE>
class rbTree 
{
	enum
	{
		RED			=		true	,	//TRUE
		BLACK		=		false		//FALSE
	};

	rbTreeNode<KEY, VALUE>* pRoot;
	rbTreeNode<KEY, VALUE>* pNullNode;

public:
	rbTree<KEY, VALUE>() : pNullNode(new rbTreeNode<KEY, VALUE>()) //, pRoot(pNullNode) // <-- Error
	{
		pRoot = pNullNode;
		/* In Node Construct rbTreeNode::rbTreeNode()
		pNullNode->up = 0;
		pNullNode->left = 0;
		pNullNode->right = 0;
		pNullNode->color = BLACK;
		*/
	};

	~rbTree<KEY, VALUE>()
	{
		// �ٸ� Node�鿡 ���� ó���� �ʿ��� �� ����. ��� ���� �� ����. �� �˾Ƽ� delete �ض� ��.

		if (pRoot != nullptr)
			delete pRoot;

		if(pNullNode != nullptr)
			delete pNullNode;
	};

public:
	rbTreeNode<KEY, VALUE>*	Search(const KEY& InKey, bool& RetResult) const ;			// �ش� Key������ �˻��Ͽ�, True�� ��� ������ ����, False�� ����(pNullNode Return). 

	rbTreeNode<KEY, VALUE>* Insert(const KEY& InKey, const VALUE& InValue);		// �ش� key����, Value ���� ������, ���ο��� �Ҵ��Ͽ� Ʈ���� ���� ��, �ش� ��忡 ���� ������ ����.
	void					Delete(rbTreeNode<KEY, VALUE>* DeletedNode);		// �ش� ��带 ���ο��� delete ����. 

private:
	void					_ChangeForInsert(rbTreeNode<KEY, VALUE>* RetNode);    
	void					_ChangeForDelete(rbTreeNode<KEY, VALUE>* RetNode);

	void					_LeftRotate(rbTreeNode<KEY, VALUE>* RetNode);
	void					_RightRotate(rbTreeNode<KEY, VALUE>* RetNode);

	rbTreeNode<KEY, VALUE>*	_GetNextNode(rbTreeNode<KEY, VALUE>* InNode);

public:
	void					PrintTree();

private:
	void					_PrintNodes(rbTreeNode<KEY, VALUE>* pNodeBuffer);
};


//////////////////////////////////////////////////////////////////////////////
// Public Function
//////////////////////////////////////////////////////////////////////////////

/*
	Search(const KEY& InKey, bool& RetResult);
		- �־��� Ű ���� ������, Ʈ������ ��带 ã�� �Լ�.

	���� : Ž���ϴ� ����� Ű ��, Ž�� ���� ����

	��� : ��� ������(���ϰ�), Ž�� ���� ����(����)
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>* rbTree<KEY, VALUE>::Search(const KEY& InKey, bool& RetResult) const
{
	// ���� Search ����� �������� ��.
	RetResult = false;

	// ������ �����͸� �����ϰ�, pRootNode�� ������.
	rbTreeNode<KEY, VALUE>*  RetNodeBuffer = pRoot;

	while (true)
	{
		// ������ ��� ������ (�˻��ϴ� ���) �� pNullNode�϶� ( False ) 
		if (RetNodeBuffer == pNullNode)
		{
			RetResult = false;
			break;
		}

		// ã�� Ű (�Լ� ����)�� ���� �˻��ϴ� ����� Ű�� ������ ��, (True)
		if (InKey == RetNodeBuffer->GetKey())
		{
			RetResult = true;
			break;
		}

		// Ű �񱳸� ����, Left Or Right ���� (Ʈ�� ���������� Ž��)
		if (InKey < RetNodeBuffer->GetKey())
			RetNodeBuffer = RetNodeBuffer->left;
		else
			RetNodeBuffer = RetNodeBuffer->right;
	}
};


/*
	Insert(const KEY& InKey, const VALUE& InValue);
		- ���ڷ� �����Ǵ� �ش� Ű, ��� ���� ������ ��带 �����ϴ� �Լ�. 
		#1. ������ Ű���� ���Ͽ� Insert�� ��û�� ���, ������ ������ �� �� �ֽ��ϴ�.
		#2. ���ο��� Node�� ���� �Ҵ�(new) �� �Ͼ�ϴ�.

	���� : ����� Ű, ������

	��� : �ش� ��忡 ���� ������ ����.
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>* rbTree<KEY, VALUE>::Insert(const KEY& InKey, const VALUE& InValue)
{
#pragma region [ ������ ��� �Ҵ� & �ʿ��� ������ ���� ���� ]

	// ������ ����� �����͸� �����ϰ�, �Ҵ����ݴϴ�. ( Key, Value�� ���� ���� (Node���� ������ ���ǵ�)
	rbTreeNode<KEY, VALUE>* pRetNode = new rbTreeNode<KEY, VALUE>(InKey, InValue, pNullNode, RED);

	// �ʿ��� �����͵��� �����մϴ�.
	rbTreeNode<KEY, VALUE>* pTraversalNode = pRoot;			// ��ȸ������, ���� ����� ��ġ�� Ž���ϱ� ���� ��ȸ�ϴ� �������Դϴ�.
	rbTreeNode<KEY, VALUE>* pParentNode = pNullNode;		// �θ������, �θ� ��带 �����صα� ���� �������Դϴ�.

#pragma endregion

#pragma region [ �����ϴ� ����� �θ��� ã�� ]
	// ���Ե� �� �ִ� �� �ڸ����� �̵��մϴ�.
	// pTraversalNode�� pRetNode�� ���Ե� �� �ִ� ��ġ(��Ȯ���� Ʈ���� ��������� �ڽ�)���� �̵��ϴ� ���-������ �Դϴ�.
	// pParentNode�� pNodeA�� ���� while�������� ��ġ( ���� pNodeA�� �θ� ��� ������) �Դϴ�.
	while (pTraversalNode != pNullNode)
	{
		//���� ��ġ�� pParentNode�� �����ϰ�, ���� ��ġ�� �̵��մϴ�.
		pParentNode = pTraversalNode;

		//Ű �񱳸� ����, ������ ����� ��ġ (Left Or Right)�� �����մϴ�. (Ʈ�� ���������� Ž��)
		if (pRetNode->GetKey() /* == InKey */	< pTraversalNode->GetKey())
			pTraversalNode = pTraversalNode->left;
		else
			pTraversalNode = pTraversalNode->right;
	}

	// �����ϴ� �������� up Point(�θ� ��� ��ġ)�� ����, pParentNode(���� ��� ������ - �θ� ��ġ)�� �־��ݴϴ�.
	pRetNode->up = pParentNode;
#pragma endregion

#pragma region [ �����ϴ� ����� ��ġ ���ϱ� ]

	// ���� �θ� ���(RetNode->up == oldBuffer)�� pNullNode�� ���, ������ ���� Ʈ���� pRoot��尡 �˴ϴ�.
	if (pParentNode == pNullNode)
		pRoot = pRetNode;
	else 
	{
		// Ʈ���� ���� ��尡 �ƴ� ���, �θ� ���( pParentNode == pRetNode->up)�� Ű ���� ����, �θ� ��忡���� ��ġ (Left Or Right)�� ���� �� �������ݴϴ�.
		if (pRetNode->GetKey() < pParentNode->GetKey() /* ==  pRetNode->up->GetKey()	*/)
			pParentNode->left = pRetNode;
		else
			pParentNode->right = pRetNode;
	}

#pragma endregion

#pragma region [ ������ ����� �ڽĳ�� �� �� ���� ]

	// ������ ��� ��ó���Դϴ�. �ڽ� ��, ��� pNullNode�� �������ݴϴ�, ���� - ��Ʈ�� ��Ģ�� ����, ������ ����� ���� RED(TRUE)�� �������ݴϴ�.
	// �Ʒ� 3����, �����ڿ��� ó��.
	//pRetNode->left = pNullNode;
	//pRetNode->right = pNullNode;
	//pRetNode->color = RED;

#pragma endregion

	// ���� ��, ���� ���θ� �˻��ϰ� ���� �ʿ� ó���� �ϴ� �Լ��Դϴ�.
	_ChangeForInsert(pRetNode);

	// ���� - ��Ʈ�� ��Ģ�� ����, � ��ȯ�� �Ͼ��, ���������� ������������ ��Ʈ ���� �׻� �������� �����ؾ��մϴ�.
	pRoot->color = BLACK;

	// ������ ��带 �������ݴϴ�.
	return pRetNode;
};


/*
	Delete(rbTreeNode<KEY, VALUE>* DeletedNode);
		- ���ڷ� �����Ǵ� ����� �����͸� Ȱ����, �ش� ��带 �����մϴ�.
		#1. ���ο��� Node�� ���� �޸� ȸ��(delete) �� �Ͼ�ϴ�.
		?1. deleted�� ����� �����Ͱ� pNullNode�� ����Ű��, nullptr ���� ������ �������� ������?

	���� : ����� ������

	��� : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::Delete(rbTreeNode<KEY, VALUE>* DeletedNode)
{
	// �����Ϸ��� ��尡 pNullNode�� �ƴ��� Ȯ���մϴ�. (pNullNode �����ϸ� Ŭ���ϴ�.)
	if (DeletedNode != pNullNode)
	{
		rbTreeNode<KEY, VALUE>* nodeA = pNullNode;
		rbTreeNode<KEY, VALUE>* nodeB = pNullNode;

		//�����ϴ� ����� �ڽ� ���� ���θ� Ȯ���մϴ�.
		if (DeletedNode->left == pNullNode || DeletedNode->right == pNullNode)
			nodeB = DeletedNode;
		else
			// �ڽ��� ���� ���, �ش� �ڸ��� � ��尡 �;��ϴ����� ���մϴ�.
			nodeB = _GetNextNode(DeletedNode);

		// ���� ��ġ�Ǵ� ����� �ڽĿ��θ� �˻��մϴ�. �ش� ���� �׻� 0 �Ǵ� 1 ���� �ڽ��� �����ϴ�. ( 2���� �ڽ��� ���� �� �����ϴ�. #1 pNullNode�� �ڽ� ī��Ʈ���� �����մϴ�.)
		if (nodeB->left != pNullNode)
			nodeA = nodeB->left;
		else
			nodeA = nodeB->right;

		nodeA->up = nodeB->up;

		// � ����� �θ��尡 pNullNode�� ����, �ش� ��尡 pRootNode���� ���մϴ�.
		if (nodeB->up == pNullNode)
			pRoot = nodeA;
		// nodeB�� �θ��, nodeA�� ���������ϴ�.
		else
		{
			if (nodeB == nodeB->up->left)
				nodeB->up->left = nodeA;
			else
				nodeB->up->right = nodeA;
		}

		// nodeB�� 
		if (nodeB != DeletedNode) 
		{
			DeletedNode->key = nodeB->key;
			//DeletedNode->value = nodeB->value;
		}

		if (nodeB->color == BLACK)
			_ChangeForDelete(nodeA);

		nodeA->color = BLACK;
		delete nodeB;
	}
};


// Private Function


/*
_ChangeForInsert(rbTreeNode<KEY, VALUE>* RetNode);
	- Insert �Լ� ���ο��� ���Ǹ�, ��带 Insert �� �Ŀ���, Red-Black Tree�� Ư¡�� �����ϱ� ���� �˻� �� ó���� ���ִ� �Լ��Դϴ�.

	#1. ���� �̷��� ��Ű ���, ����-�� Ʈ���� Ȯ���� �ּ���! https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC

	���� : Insert�� ����� ������

	��� : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_ChangeForInsert(rbTreeNode<KEY, VALUE>* pRetNode)
{
	while (pRetNode->up->color == RED)
	{
		// (�ǿ�) �츮 �ƺ���, �Ҿƹ����� ù° �Ƶ��϶�,...?
		if (pRetNode->up == pRetNode->up->up->left)
			// Uncle Node �� ��ġ ã��. --> Uncle�� Right!
		{
			rbTreeNode<KEY, VALUE>* uncleNode = pRetNode->up->up->right;

			if (uncleNode->color == RED)
			{
				//���Կ����� 3��° ���.

				// �� ����. (Recoloring)
				pRetNode->up->color = BLACK;
				uncleNode->color = BLACK;

				pRetNode->up->up->color = RED;

				// Red ������, �θ��� �θ��� ��ȯ ��, �ش� ��忡 ���� Double Red Test �ʿ�.
				pRetNode = pRetNode->up->up;
			}
			else {
				//���Կ����� 4��° ���.

				// ��� ���� (Restructuring)
				if (pRetNode == pRetNode->up->right)
				{
					pRetNode = pRetNode->up;
					_LeftRotate(pRetNode);
				}

				pRetNode->up->color = BLACK;
				pRetNode->up->up->color = RED;
				pRetNode->up->right->color = BLACK;
				_RightRotate(pRetNode->up->up);
			}
		}
		else
			// Uncle Node �� ��ġ ã��. --> Uncle�� Left!
		{
			rbTreeNode<KEY, VALUE>* uncleNode = pRetNode->up->up->left;

			if (uncleNode->color == RED)
			{
				// �� ����. (Recoloring)
				pRetNode->up->color = BLACK;
				uncleNode->color = BLACK;

				pRetNode->up->up->color = RED;

				// Red ������, �θ��� �θ��� ��ȯ ��, �ش� ��忡 ���� Double Red Test �ʿ�.
				pRetNode = pRetNode->up->up;
			}
			else {
				// ��� ���� (Restructuring)
				if (pRetNode == pRetNode->up->left)
				{
					pRetNode = pRetNode->up;
					_RightRotate(pRetNode);
				}

				pRetNode->up->color = BLACK;
				pRetNode->up->up->color = RED;
				pRetNode->up->right->color = BLACK;
				_LeftRotate(pRetNode->up->up);
			}
		}
	}
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_ChangeForDelete(rbTreeNode<KEY, VALUE>* RetNode)
{
	while (RetNode != pRoot && RetNode->color == BLACK)
	{
		rbTreeNode<KEY, VALUE>* buffer = 0;

		if (RetNode->up->left == RetNode)
		{
			buffer = RetNode->up->right;

			if (buffer->color == RED)
			{
				buffer->color = BLACK;
				RetNode->up->color = RED;
				_LeftRotate(RetNode->up);
				buffer = RetNode->up->right;
			}

			if (buffer->left->color == BLACK && buffer->right->color == BLACK)
			{
				buffer->color = RED;
				RetNode = RetNode->up;
			}
			else
			{
				if (buffer->right->color == BLACK)
				{
					buffer->left->color = BLACK;
					buffer->color = RED;
					_RightRotate(buffer);
					buffer = RetNode->up->right;
				}
				buffer->color = RetNode->up->color;
				RetNode->up->color = BLACK;
				buffer->right->color = BLACK;
				_LeftRotate(RetNode->up);
				RetNode = pRoot;
			}
		}
		else
		{
			buffer = RetNode->up->left;
			if (buffer->color == RED)
			{
				buffer->color = BLACK;
				RetNode->up->color = RED;
				_RightRotate(RetNode->up);
				buffer = RetNode->up->left;
			}
			if (buffer->right->color == BLACK && buffer->left->color == BLACK)
			{
				buffer->color = RED;
				RetNode = RetNode->up;
			}
			else
			{
				if (buffer->left->color == BLACK)
				{
					buffer->right->color = BLACK;
					buffer->color = RED;
					_LeftRotate(buffer);
					buffer = RetNode->up->left;
				}

				buffer->color = RetNode->up->color;
				RetNode->up->color = BLACK;
				buffer->left->color = BLACK;
				_RightRotate(RetNode->up);
				RetNode = pRoot;
			}
		}
	}
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_LeftRotate(rbTreeNode<KEY, VALUE>* RetNode)
{
	rbTreeNode<KEY, VALUE>* rightChildNode = RetNode->right;

	// RetNode�� ���� Ʈ���� pRootNode�� �� ( ������ �ڽ��� ��Ʈ�� �� (LeftRotate) )
	if (RetNode->up == pNullNode)
		pRoot = rightChildNode;
	else
	{
		//���� ��尡 �θ� ����� ���� �ڽ� ����϶�,
		if (RetNode == RetNode->up->left)
			RetNode->up->left = rightChildNode;

		//���� ��尡 �θ� ����� ������ �ڽ� ����϶�,
		else
			RetNode->up->right = rightChildNode;
	}

	//���� Ret�� �θ����, Ret�� ������ �ڽ� ��带 �θ����� �ٲ��ְ�, Ret���� �ڽĳ���� �ڽ����� �����մϴ�.

	// �� �θ���� ���, �� �ڽ��� �θ���̴�.
	rightChildNode->up = RetNode->up;

	// �� �ڽ��� ���, �� �ڽ��� �ڽ� - ���ڴ�.
	RetNode->right = rightChildNode->left;

	// ���� �� �ڽ� - ������ �θ�� ����.
	rightChildNode->left->up = RetNode;

	// ...���� �� ���� �ڽ��� �ڽ��̴�.
	rightChildNode->left = RetNode;

	// �ᱹ �� �θ���� �� �� �ڽ��̴�.
	RetNode->up = rightChildNode;
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_RightRotate(rbTreeNode<KEY, VALUE>* RetNode)
{
	rbTreeNode<KEY, VALUE>* leftChildNode = RetNode->left;

	// �ּ� _LeftRotate �ϰ� �����մϴ�..

	if (RetNode->up == pNullNode) 
		pRoot = leftChildNode;
	else
	{
		if (RetNode == RetNode->up->left)
			RetNode->up->left = leftChildNode;
		else
			RetNode->up->right = leftChildNode;
	}

	leftChildNode->up = RetNode->up;
	RetNode->left = leftChildNode->right;
	leftChildNode->right->up = RetNode;
	leftChildNode->right = RetNode;
	RetNode->up = leftChildNode;
};

/*
_GetNextNode(rbTreeNode<KEY, VALUE>* InNode);
	����(�����Դϴ�.) : https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/

	���� �����帮��, ���� ��� ������ GetNextNode��� �Լ����� ������
	���� ��Ī�� Predecessor, Successor�̸� ����, �ش� ����� ���� ����Ʈ���� �ִ밪 (Predecessor), �ش� ����� ���� ����Ʈ���� �ּҰ� (Successor) �Դϴ�.

	�̸� ���ؾ��� ����, 
	�����Ǵ� ��尡 �� ���� pNullNode�� �ƴ� �ڽ��� ���� ���, �ش� ����� �ڸ��� � ��尡 �;��ϴ� ���� ���ϴ� ���̸�,
	�� �ڸ��� �� �� �ִ� ���� Predecessor �Ǵ� Successor�� �ֽ��ϴ�.

	����� �����ϴ� ��尡 �ڽ��� ���� ���, ��� �����ϸ� �ǰ�,
	�����ϴ� ��尡 1���� �ڽ��� ���� ���� ���, �ش� �ڽ��� �� �ڸ��� ��ġ��Ű�� �˴ϴ�(like list)
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetNextNode(rbTreeNode<KEY, VALUE>* InNode)
{
	// ������ �ΰ��� �ƴ� ���, 
	if (InNode->right != pNullNode) {

		InNode = InNode->right;

		while (InNode->left != pNullNode)
		{
			InNode = InNode->left;
		}

		return InNode;
	}

	rbTreeNode<KEY, VALUE>* bufferNode = InNode->up;

	while (bufferNode != pNullNode && InNode == bufferNode->right) 
	{
		InNode = bufferNode;
		bufferNode = bufferNode->up;
	}

	return bufferNode;
};


//Debug Function

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::PrintTree()
{
		
	if (pRoot != pNullNode)
	{
		std::cout << "pRootNode's Key : " << pRoot->GetKey() << "\n";
		std::cout << "Node - Key   Color   Value    Up     Left     Right \n";
		_PrintNodes(pRoot);
	}
	else
		cout << "Tree pRoot is pNullNode (VOID-TREE) \n";
}

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_PrintNodes(rbTreeNode<KEY, VALUE>* pNodeBuffer)
{
	if (pNodeBuffer->left != pNullNode)
		_PrintNodes(pNodeBuffer->left);
	if (pNodeBuffer != pNullNode) {
		std::cout << "       ";

		cout << pNodeBuffer->key << ' ';

		std::cout << "    ";

		if (pNodeBuffer->color == RED)
			cout << "RED   ";
		else
			cout << "BLACK ";

		std::cout << "     ";

		cout << pNodeBuffer->value << ' ';

		std::cout << "     ";

		if (pNodeBuffer->up != pNullNode)
			cout << pNodeBuffer->up->key << ' ';
		else
			cout << "NULL ";

		std::cout << "     ";

		if (pNodeBuffer->left != pNullNode)
			cout << pNodeBuffer->left->key << ' ';
		else
			cout << "NULL ";

		std::cout << "     ";

		if (pNodeBuffer->right != pNullNode)
			cout << pNodeBuffer->right->key << ' ';
		else
			cout << "NULL ";
	}
	cout << endl;
	if (pNodeBuffer->right != pNullNode)
		_PrintNodes(pNodeBuffer->right);
}