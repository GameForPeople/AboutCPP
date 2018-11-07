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

public:
	// Debug.
	void PrintNodeInfo(rbTreeNode<KEY, VALUE>* pNullNode)
	{
		std::cout << "       ";

		cout << key << ' ';

		std::cout << "    ";

		if (color == RED)
			cout << "RED   ";
		else
			cout << "BLACK ";

		std::cout << "     ";

		cout << value << ' ';

		std::cout << "     ";

		if (up != pNullNode)
			cout << up->key << ' ';
		else
			cout << "NULL ";

		std::cout << "     ";

		if (left != pNullNode)
			cout << left->key << ' ';
		else
			cout << "NULL ";

		std::cout << "     ";

		if (right != pNullNode)
			cout << right->key << ' ';
		else
			cout << "NULL ";

		std::cout << endl;
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

	rbTreeNode<KEY, VALUE>* pNullNode;
	rbTreeNode<KEY, VALUE>* pRoot;

public:
	rbTree<KEY, VALUE>() : pNullNode(new rbTreeNode<KEY, VALUE>()) , pRoot(pNullNode)
	{
		/* In Node Construct rbTreeNode::rbTreeNode()
		pRoot = pNullNode;
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
		pRoot = nullptr;

		if(pNullNode != nullptr)
			delete pNullNode;
		pNullNode = nullptr;
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

	void					_NewLeftRotate(rbTreeNode<KEY, VALUE>* RetNode);
	void					_NewRightRotate(rbTreeNode<KEY, VALUE>* RetNode);

	rbTreeNode<KEY, VALUE>*	_GetNextNode(rbTreeNode<KEY, VALUE>* InNode);
	rbTreeNode<KEY, VALUE>*	_GetUncleNode(rbTreeNode<KEY, VALUE>* InNode);

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

#pragma region [ �����ϴ� ����� �ڽĳ�� �� �� ���� ]

	// ������ ��� ��ó���Դϴ�. �ڽ� ��, ��� pNullNode�� �������ݴϴ�, ���� - ��Ʈ�� ��Ģ�� ����, ������ ����� ���� RED(TRUE)�� �������ݴϴ�.
	// �Ʒ� 3����, �����ڿ��� ó��.
	//pRetNode->left = pNullNode;
	//pRetNode->right = pNullNode;
	//pRetNode->color = RED;

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
	{
		pRoot = pRetNode;
	}
	else 
	{
		// Ʈ���� ���� ��尡 �ƴ� ���, �θ� ���( pParentNode == pRetNode->up)�� Ű ���� ����, �θ� ��忡���� ��ġ (Left Or Right)�� ���� �� �������ݴϴ�.
		if (pRetNode->GetKey() < pParentNode->GetKey() /* ==  pRetNode->up->GetKey()	*/)
			pParentNode->left = pRetNode;
		else
			pParentNode->right = pRetNode;

		// ���� ����ߴ� ����Ʈ ����. ������ �߸����� ��� ����.
		pTraversalNode = pRetNode;

		// ���� ��, ���� ���θ� �˻��ϰ� ���� �ʿ� ó���� �ϴ� �Լ��Դϴ�. ( [Insert Case 1 ] ù �����϶��� �ʿ�����ϴ�.(���� if��, -- if (pParentNode == pNullNode) )
		_ChangeForInsert(pTraversalNode);
	}

#pragma endregion

	// ���� - ��Ʈ�� ��Ģ�� ����, � ��ȯ�� �Ͼ��, ���������� ������������ ��Ʈ ���� �׻� �������� �����ؾ��մϴ�.
	pRoot->color = BLACK;

	//����� �α� ����մϴ�.
	this->PrintTree();

	// ������ ��带 �������ݴϴ�.
	return pRetNode;
};


/*
	Delete(rbTreeNode<KEY, VALUE>* DeletedNode);
		- ���ڷ� �����Ǵ� ����� �����͸� Ȱ����, �ش� ��带 �����մϴ�.
		#1. ���ο��� Node�� ���� �޸� ȸ��(delete) �� �Ͼ�ϴ�.
		?1. deleted�� ����� �����Ͱ� pNullNode�� ����Ű��, nullptr ���� ������ �������� ������?

	���� : �����Ϸ��� ����� ������

	��� : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::Delete(rbTreeNode<KEY, VALUE>* pDeletedNode)
{
	// �����Ϸ��� ��尡 pNullNode�� �ƴ��� Ȯ���մϴ�. (pNullNode �����ϸ� Ŭ���ϴ�.) ���������� �̷� �� ���� ���� ������, �ּ�ó��.
	if (pDeletedNode == pNullNode)
	{
		return;
	}

	// �����Ϸ��� ����� ���� �������� ���, ������ ����Ʈ���� ����ϰ� �������ֽø� �˴ϴ�.
	if (pDeletedNode.color == RED)
	{
		// �ڽ��� ���� ���(�� �ڽ��� ��� nullNode�� ���, 
		if (pDeletedNode->left == pNullNode && pDeletedNode->right == pNullNode)
		{
			//if(pDeletedNode->up == pNullNode) -> ��� ���� ���� ����, ��Ʈ��尡 �� �� ����.

			//�θ��忡�� �ڽ��� ����ϼ����� �˸���.... (nullNode�� �������ְ�).
			if (pDeletedNode->up->left == pDeletedNode)
				pDeletedNode->up->left = pNullNode;
			else
				pDeletedNode->up->right = pNullNode;

			// (���)
			delete pDeletedNode;
			pDeletedNode = nullptr;

			return;
		}

		// �ڽ��� �ΰ��� ���� ���,
		else if (pDeletedNode->left != pNullNode && pDeletedNode->right != pNullNode)
		{

		}

		// �Ʒ� �� ������ �����Ʈ������ �߻����� ����.

		// �ڽ��� 1�и� ��ŵ�, �������� ��� (�߻����� ����)
		else if (pDeletedNode->left == pNullNode)
		{
			std::cout << " [DEBUG_LOG] line 371 �߻����� ���ƾ��� ���� �б� �Դϴ�. "
			//�θ��忡�� ������ �ڽ��� �±��..
			if (pDeletedNode->up->left == pDeletedNode)
				pDeletedNode->up->left = pDeletedNode->right;
			else
				pDeletedNode->up->right = pDeletedNode->right;

			// ���̿��Ե� �� �θ���� ������ �˷��ְ�..
			pDeletedNode->right->up = pDeletedNode->up->up;

			// (���)
			delete pDeletedNode;
			pDeletedNode = nullptr;

			return;
		}
		// �ڽ��� 1�и� ��ŵ�, ������ ��� (�߻����� ����)
		else if (pDeletedNode->right == pNullNode)
		{
			std::cout << " [DEBUG_LOG] line 390 �߻����� ���ƾ��� ���� �б� �Դϴ�. "

			//�θ��忡�� ���� �ڽ��� �±��..
			if (pDeletedNode->up->left == pDeletedNode)
				pDeletedNode->up->left = pDeletedNode->left;
			else
				pDeletedNode->up->right = pDeletedNode->left;

			// ���̿��Ե� �� �θ���� ������ �˷��ְ�..
			pDeletedNode->left->up = pDeletedNode->up->up;

			// (���)
			delete pDeletedNode;
			pDeletedNode = nullptr;

			return;
		}
	}


	rbTreeNode<KEY, VALUE>* nodeA = pNullNode;
	rbTreeNode<KEY, VALUE>* nodeB = pNullNode;

	//�����ϴ� ����� �ڽ� ���� ���θ� Ȯ���մϴ�.
		nodeB = pDeletedNode;
	else
		// �ڽ��� ���� ���, �ش� �ڸ��� � ��尡 �;��ϴ����� ���մϴ�.
		nodeB = _GetNextNode(pDeletedNode);

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
	if (nodeB != pDeletedNode)
	{
		pDeletedNode->key = nodeB->key;
		//pDeletedNode->value = nodeB->value;
	}

	if (nodeB->color == BLACK)
		_ChangeForDelete(nodeA);

	nodeA->color = BLACK;
	delete nodeB;
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
	// [Insert Case 2] �̹� ������ Ʈ����, ���� �� Ʈ���� ������ �����ϱ� ������, �θ��� ��尡 �������� ���, ����ؾ��� ������ �����ϴ�.  // �ش� ������ Insert Case 1�� �����ϴ� �����Դϴ�.
	if (pRetNode->up->color == BLACK)
	{
		return;
	}
	
	rbTreeNode<KEY, VALUE>* pUncleNode = _GetUncleNode(pRetNode); // UncleNode Pointer : 
	rbTreeNode<KEY, VALUE>* pGrandNode = pRetNode->up->up; // ���θ�(�պθ�) ��� --> nullNode�� ���� �����ϴ�.

	// [Insert Case 3] Recoloring - �θ���� UncleNode ��� �������� ��, �̸� ��� ���������� �ٲٰ�, ���θ��带 ���������� ������. 
	if (pUncleNode->color == RED /*&& pUncleNode != pNullNode // �� ������ �������� ����. */)
	{
		pRetNode->up->color = BLACK;
		pUncleNode->color = BLACK;
		pGrandNode->color = RED;

		// �� ���θ��带 ���������� �����߱� ������, �̿� ���� �����ϰ� �����Ʈ�� ����(���� ���� �׽�Ʈ �����)�� ���� �˻簡 �ʿ���.
		_ChangeForInsert(pGrandNode);

		return;
	}

	// [Insert Case 4] Restructuring - �θ���� �������̳�, UncleNode�� �������� ��, ��翡 ����. ���� ȸ���� ���� ( ����� ��Ģ�� ���ݵ�! ���� ���� ���� )
	if ((pRetNode == pRetNode->up->right) && (pRetNode->up == pGrandNode->left)) 
	{
		_LeftRotate(pRetNode->up);
		//_NewLeftRotate(pRetNode->up);
		pRetNode = pRetNode->left;
	}
	else if ((pRetNode == pRetNode->up->left) && (pRetNode->up == pGrandNode->right)) {
		_RightRotate(pRetNode->up);
		//_NewRightRotate(pRetNode->up);
		pRetNode = pRetNode->right;
	}


	// [Insert Case 5] 
	pGrandNode = pRetNode->up->up;

	pRetNode->up->color = BLACK;
	pGrandNode->color = RED;

	if (pRetNode == pRetNode->up->left)
		//_NewRightRotate(pGrandNode);
		_RightRotate(pGrandNode);
	else
		//_NewLeftRotate(pGrandNode);
		_LeftRotate(pGrandNode);

	/*
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
	*/
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
void rbTree<KEY, VALUE>::_LeftRotate(rbTreeNode<KEY, VALUE>* pRetNode)
{
	rbTreeNode<KEY, VALUE>* pParentNode = pRetNode->up;
	rbTreeNode<KEY, VALUE>* pRightChildNode = pRetNode->right;

	// RetNode�� ���� Ʈ���� pRootNode�� �� ( ������ �ڽ��� ��Ʈ�� �� (LeftRotate) )
	if (pParentNode == pNullNode)
		pRoot = pRightChildNode;
	else
	{
		//���� ��尡 �θ� ����� ���� �ڽ� ����϶�,
		if (pRetNode == pParentNode->left)
			pParentNode->left = pRightChildNode;

		//���� ��尡 �θ� ����� ������ �ڽ� ����϶�,
		else
			pParentNode->right = pRightChildNode;
	}

	//���� Ret�� �θ����, Ret�� ������ �ڽ� ��带 �θ����� �ٲ��ְ�, Ret���� �ڽĳ���� �ڽ����� �����մϴ�.

	// �� �θ���� ���, �� �ڽ��� �θ���̴�.
	pRightChildNode->up = pRetNode->up;

	// �� �ڽ��� ���, �� �ڽ��� �ڽ� - ���ڴ�.
	pRetNode->right = pRightChildNode->left;

	// ���� �� �ڽ� - ������ �θ�� ����.
	pRightChildNode->left->up = pRetNode;

	// ...���� �� ���� �ڽ��� �ڽ��̴�.
	pRightChildNode->left = pRetNode;

	// �ᱹ �� �θ���� �� �� �ڽ��̴�.
	pRetNode->up = pRightChildNode;
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_RightRotate(rbTreeNode<KEY, VALUE>* pRetNode)
{
	rbTreeNode<KEY, VALUE>* pParentNode = pRetNode->up;
	rbTreeNode<KEY, VALUE>* pLeftChildNode = pRetNode->left;

	// �ּ� _LeftRotate �ϰ� �����մϴ�..

	if (pParentNode == pNullNode)
		pRoot = pLeftChildNode;
	else
	{
		if (RetNode == RetNode->up->left)
			RetNode->up->left = leftChildNode;
		else
		pParentNode->right = pLeftChildNode;
	}

	pLeftChildNode->up = pRetNode->up;

	pRetNode->left = pLeftChildNode->right;
	pLeftChildNode->right->up = pRetNode;

	pLeftChildNode->right = pRetNode;
	pRetNode->up = pLeftChildNode;
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_NewLeftRotate(rbTreeNode<KEY, VALUE>* n)
{
	rbTreeNode<KEY, VALUE> *c = n->right;
	rbTreeNode<KEY, VALUE> *p = n->up;

	if (c->left != pNullNode)
		c->left->up = n;

	n->right = c->left;
	n->up = c;
	c->left = n;
	c->up = p;

	if (p != pNullNode) {
		if (p->left == n)
			p->left = c;
		else
			p->right = c;
	}
}

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_NewRightRotate(rbTreeNode<KEY, VALUE>* n)
{
	rbTreeNode<KEY, VALUE> *c = n->left;
	rbTreeNode<KEY, VALUE> *p = n->up;

	if (c->right != pNullNode)
		c->right->up = n;

	n->left = c->right;
	n->up = c;
	c->right = n;
	c->up = p;

	if (p != pNullNode) {
		if (p->right == n)
			p->right = c;
		else
			p->left = c;
	}
}

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


template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetUncleNode(rbTreeNode<KEY, VALUE>* pInNode) 
{
	rbTreeNode<KEY, VALUE>* pGrandParentNode = pInNode->up->up;

	if (pInNode->up == pGrandParentNode->left)
		return pGrandParentNode->right;
	else
		return pGrandParentNode->left;
}



//Debug Function

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::PrintTree()
{
	rbTreeNode<KEY, VALUE>* pNodeBuffer = pRoot;

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

	pNodeBuffer->PrintNodeInfo(pNullNode);

	if (pNodeBuffer->right != pNullNode)
		_PrintNodes(pNodeBuffer->right);
}