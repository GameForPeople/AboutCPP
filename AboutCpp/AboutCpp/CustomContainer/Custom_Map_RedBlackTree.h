#pragma once

/*
	Custom_Map_RedBlackTree.h

	2018/11/11

		- Key�� Value�� ������ STL::MAP�� �䳻��(���� �߳��� �� ���󰩴ϴ�. ), �����Ʈ��(���泪��) �Դϴ�.
		- �н������� (��� �н������� ����ϱ⵵...), ������Ʈ�� ����ϸ�� �ȵ˴ϴ�.. ���� ���� Ȯ�� ���� �����ο���. ���ɵ� ������, �����ϴ� �Լ��� �����... STL Map, Set ���ſ�!
*/

#define INLINE __inline

#pragma region [ Declare rbTreeNode, rbTree ]

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

	#2. �� �ٵ� 1�� ���غþ��...��� �ص� �ȵɼ��� �־��! ��
*/

template <typename KEY, typename VALUE>
class rbTreeNode {
	friend class rbTree<KEY, VALUE>;

	// Define Color RED = true, BLACK = false;
	enum
	{
		RED			=		true	,	//TRUE
		BLACK		=		false		//FALSE
	};

private:
	KEY							key;	// Key
	VALUE						value;	// Value

	bool						color;	// false ( 0 ) == black , true (1) == red;

	rbTreeNode<KEY, VALUE>*		up;		// Parent Node Pointer
	rbTreeNode<KEY, VALUE>*		left;	// Left Child Node Pointer
	rbTreeNode<KEY, VALUE>*		right;	// Right Child Node Pointer

public:
	// Define the constructor for pNullNode, buffer #1 Key, Value�� ���� �⺻�����ڰ� �ʿ��մϴ�.
	rbTreeNode<KEY, VALUE>() 
		: key(), value(), up(this), left(this), right(this), color(false)
	{}

	// Define the constructor for Insert 1
	rbTreeNode<KEY, VALUE>(const KEY& InKEY, const VALUE& InValue) 
		: key(InKEY), value(InValue), up(nullptr), left(nullptr), right(nullptr), color(false)
	{}

	// Define the constructor for Insert 2
	rbTreeNode<KEY, VALUE>(const KEY& InKEY, const VALUE& InValue, rbTreeNode<KEY, VALUE>* pInNode, const bool& InColor)
		: key(InKEY), value(InValue), up(pInNode), left(pInNode), right(pInNode), color(InColor)
	{}

	// Define the destructor. 
	~rbTreeNode<KEY, VALUE>() = default;

public:
	// Get Function
	INLINE KEY					GetKey() const
	{
		return key;
	}

	INLINE VALUE				GetValue() const
	{
		return value;
	}

public:
	//for Debug.
	void						PrintNodeInfo(rbTreeNode<KEY, VALUE>* pNullNode)
	{
		std::cout << "       ";

		std::cout << key << ' ';

		std::cout << "    ";

		if (color == RED)
			std::cout << "RED   ";
		else
			std::cout << "BLACK ";

		std::cout << "     ";

		std::cout << value << ' ';

		std::cout << "     ";

		if (up != pNullNode)
			std::cout << up->key << ' ';
		else
			std::cout << "NULL ";

		std::cout << "     ";

		if (left != pNullNode)
			std::cout << left->key << ' ';
		else
			std::cout << "NULL ";

		std::cout << "     ";

		if (right != pNullNode)
			std::cout << right->key << ' ';
		else
			std::cout << "NULL ";

		std::cout << endl;
	}
};

template <typename KEY, typename VALUE>
class rbTree 
{
	// Define Color RED = true, BLACK = false;
	enum
	{
		RED			=		true	,	//TRUE
		BLACK		=		false		//FALSE
	};

	rbTreeNode<KEY, VALUE>*			pNullNode;	// NullNode's Color is Black. == same nil
	rbTreeNode<KEY, VALUE>*			pRoot;		// Root!

public:
	rbTree<KEY, VALUE>() 
		: pNullNode(new rbTreeNode<KEY, VALUE>()) , pRoot(pNullNode)
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
		// �ٸ� Node�鿡 ���� ó���� �ʿ��� �� ����. ó�����ϰ� ��� ���� �� ����. �˾Ƽ� delete �ض� ��.

		if (pRoot != nullptr)
			delete pRoot;
		pRoot = nullptr;

		if(pNullNode != nullptr)
			delete pNullNode;
		pNullNode = nullptr;
	};

public:
	rbTreeNode<KEY, VALUE>*			Search(const KEY& InKey, bool& RetResult) const ;		// �ش� Key������ �˻��Ͽ�, True�� ��� ������ ����, False�� ����(pNullNode Return). 

	rbTreeNode<KEY, VALUE>*			Insert(const KEY& InKey, const VALUE& InValue);			// �ش� key����, Value ���� ������, ���ο��� �Ҵ��Ͽ� Ʈ���� ���� ��, �ش� ��忡 ���� ������ ����.

	void							Delete(rbTreeNode<KEY, VALUE>* DeletedNode);			// ���ڷ� ���޵� ����� �����͸� ����, �ش� ��带 �������ݴϴ�.
	bool							DeleteWithSearch(const KEY& InKey);						// �ش� Ű�� �ش��ϴ� ��带 ã�� �������ݴϴ�.

private:
	void							_ChangeForInsert(rbTreeNode<KEY, VALUE>* RetNode);    
	void							_ChangeForDelete(rbTreeNode<KEY, VALUE>* RetNode);

	void							_LeftRotate(rbTreeNode<KEY, VALUE>* RetNode);
	void							_RightRotate(rbTreeNode<KEY, VALUE>* RetNode);

	INLINE rbTreeNode<KEY, VALUE>*	_GetPrevNode(rbTreeNode<KEY, VALUE>* const InNode);
	INLINE rbTreeNode<KEY, VALUE>*	_GetNextNode(rbTreeNode<KEY, VALUE>* const InNode);

	INLINE rbTreeNode<KEY, VALUE>*	_GetSiblingNode(rbTreeNode<KEY, VALUE>* const InNode);
	INLINE rbTreeNode<KEY, VALUE>*	_GetUncleNode(rbTreeNode<KEY, VALUE>* const InNode);

//for Debug
public:
	void							PrintTree();

private:
	void							_PrintNodes(rbTreeNode<KEY, VALUE>* pNodeBuffer);
};

#pragma endregion

#pragma region [ Definition of Functions ]

// ================================== Search

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


// ================================== Insert

/*
	Insert(const KEY& InKey, const VALUE& InValue);
		- ���ڷ� �����Ǵ� �ش� Ű, ��� ���� ������ ��带 �����ϴ� �Լ�. 
		!1. ������ Ʈ���� �����ϴ� ��忡 ���� ������ Ű���� ���Ͽ� Insert�� ��û�� ���, ������ ������ �� �� �ֽ��ϴ�.
		!2. ���ο��� Node�� ���� �Ҵ�(new) �� �Ͼ�ϴ�.

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

	// ���� - ��Ʈ�� ��Ģ�� ����, � ��ȯ�� �Ͼ��, ���������� �������������� ��Ʈ ���� �׻� �������� �����ؾ��մϴ�.
	pRoot->color = BLACK;

	////(�����)���� �Ҷ�����, Ʈ���� ����մϴ�.
	//this->PrintTree();

	// ������ ��带 �������ݴϴ�.
	return pRetNode;
};

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
LIKE_RECURSION:

	// [Insert Case 2] �̹� ������ Ʈ����, ���� �� Ʈ���� ������ �����ϱ� ������, �θ��� ��尡 �������� ���, ����� �ʿ䰡 �����ϴ�. (-> ��� ������ ���� ���忡�� �߻��մϴ�.)  // �ش� ������ Insert Case 1�� �����ϴ� �����Դϴ�.
	if (pRetNode->up->color == BLACK)
	{
		return;
	}
	
	rbTreeNode<KEY, VALUE>* pUncleNode = _GetUncleNode(pRetNode); // UncleNode Pointer  
	rbTreeNode<KEY, VALUE>* pGrandNode = pRetNode->up->up; // ���θ�(�պθ�) ��� --> nullptr�� ���� ������� �ʾƵ� �˴ϴ�. (Insert Case 1 - 2���� �ɷ����ϴ�.)

	// [Insert Case 3] Recoloring - �θ���� UncleNode ��� �������� ��, �̸� ��� ���������� �ٲٰ�, ���θ��带 ���������� �����մϴ�. 
	if (pUncleNode->color == RED /*&& pUncleNode != pNullNode // �� ������ �������� ����. */)
	{
		pRetNode->up->color = BLACK;
		pUncleNode->color = BLACK;
		pGrandNode->color = RED;

		// �� ���θ��带 ���������� �����߱� ������, �̿� ���� �����ϰ� �����Ʈ�� ����(���� ���� �׽�Ʈ �����)�� ���� �˻簡 �ʿ���.
		//_ChangeForInsert(pGrandNode); // <- ����Լ��� ������� ���� ( �޸� ������� )

		// ��� �����͸� ���� ��, pGrandNode���� ���� ��, goto������ �Լ� ù°�ٷ� �̵�.
		pRetNode = pGrandNode;
		goto LIKE_RECURSION;
		//return;
	}

	// [Insert Case 4] Restructuring - �θ���� �������̳�, UncleNode�� �������� ��, ��翡 ����. ���� ȸ���� ���� ( Insert Case 4�� ��ģ Ʈ���� ���� ���� ���°� �Ǹ� ��Ģ�� ���ݵ˴ϴ�. )
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
		_RightRotate(pGrandNode);
	else
		_LeftRotate(pGrandNode);
};

// ================================== Delete


/*
	Delete(rbTreeNode<KEY, VALUE>* DeletedNode);
		- ���ڷ� �����Ǵ� ����� �����͸� Ȱ����, �ش� ��带 �����մϴ�!

		#1. ���� ���� - ��Ʈ�� ��İ� ���� �ٸ� ���� Copy Value�� �ƴ϶�, Node ��ü�� �����ϴ� ���Դϴ�.
		( ���ο��� Node�� ���� ptr�� Ȱ���� ��, �̿� ���� ������ �����ϱ� ����.)

		!1. ���ο��� Node�� ���� �޸� ȸ��(delete) �� �Ͼ�ϴ�.

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
	
	rbTreeNode<KEY, VALUE>* pBuffer = pNullNode;
	rbTreeNode<KEY, VALUE>* pChildBuffer = pNullNode;
	bool deletedNodeColor = BLACK;

	// �ڽ� ��� �� �˻�. --> �ΰ� �� �������.
	if (pDeletedNode->left != pNullNode && pDeletedNode->right != pNullNode)
	{
		pBuffer = _GetNextNode(pDeletedNode);
 		pChildBuffer = pBuffer->right;
		
		// GetNextNode�� �ٷ�, ���� ���� �ڽ��� ���� �����ʿ�.
		if (pDeletedNode->right == pBuffer)
		{
			if (pChildBuffer == pNullNode)
			{
				pChildBuffer->up = pBuffer;
			}
		}
		else if (pChildBuffer != pNullNode)
		{
			pChildBuffer->up = pBuffer->up;
			pBuffer->up->left = pChildBuffer;
		}
		else
		{
			// TEST ------------------------
			pChildBuffer->up = pBuffer->up;
			// TEST ------------------------

			pBuffer->up->left = pNullNode;
		}

		// NextNode�� ������, pDeletedBuffer�� ��������. (���� �����ϴ� ���� pBuffer�̱� ������) --> [DEV_55] (bug_3) nullptr ���� ���� �߻�.
		// Data Copy
		//pDeletedNode->key = pBuffer->key;
		//pDeletedNode->value = pBuffer->value;

		// (!Data) Copy
		// ���� Data Copy �ÿ���, ���� �ش� pBuffer�� ptr�� �ش��ϴ� ��带 �����ͷ� �����ϰ� Ȱ���ϴ� ������ ������ nullptr�� �Ͼ ��찡 �ֱ� ������ nodeSwap�� ����.
		if (pDeletedNode->up == pNullNode) 
		{
			pRoot = pBuffer;
		}
		else
		{
			if (pDeletedNode->up->left == pDeletedNode)
				pDeletedNode->up->left = pBuffer;
			else
				pDeletedNode->up->right = pBuffer;
		}

		// �����ϴ� ����� �θ�� ����
		pBuffer->up = pDeletedNode->up;

		// �����ϴ� ����� �ڽĵ�� ����.
		pDeletedNode->left->up = pBuffer;
		pBuffer->left = pDeletedNode->left;

		// GetNextNode�� �ٷ�, ���� ���� �ڽ��� ���� �����ʿ�.
		if (pDeletedNode->right != pBuffer)
		{
			pDeletedNode->right->up = pBuffer;
			pBuffer->right = pDeletedNode->right;
		}

		// �÷� ���� ����.
		deletedNodeColor = pBuffer->color;
		pBuffer->color = pDeletedNode->color;
	}
	// �ڽ��� ���� ��常 �������.
	else if (pDeletedNode->left != pNullNode)
	{
		pBuffer = pDeletedNode;
		pChildBuffer = pBuffer->left;

		// �ڽĿ��� �� �θ� �˸�.
		pChildBuffer->up = pBuffer->up;

		// �����Ǵ� ��尡 root���� ���, ChildBuffer �� �ڽ��� �ǵ��� ��.
		if (pBuffer->up == pNullNode)
			pRoot = pChildBuffer;
		else 
		{
			// pBuffer�� �θ𿡰�, �� �ڽ��� �˷���.
			if (pBuffer->up->left == pBuffer)
				pBuffer->up->left = pChildBuffer;
			else
				pBuffer->up->right = pChildBuffer;
		}
		// �� ����
		deletedNodeColor = pBuffer->color;
	}
	// �ڽ��� ������ ��常 �������.
	else if (pDeletedNode->right != pNullNode)
	{
		pBuffer = pDeletedNode;
		pChildBuffer = pBuffer->right;

		pChildBuffer->up = pBuffer->up;

		if (pBuffer->up == pNullNode)
			pRoot = pChildBuffer;
		else
		{
			if (pBuffer->up->left == pBuffer)
				pBuffer->up->left = pChildBuffer;
			else
				pBuffer->up->right = pChildBuffer;
		}

		// �� ����
		deletedNodeColor = pBuffer->color;
	}
	// �ڽ��� ����.
	else
	{
		pBuffer = pDeletedNode;

		// TEST ------------------------
		//pChildBuffer = pBuffer->right;
		pChildBuffer->up = pBuffer->up;
		// TEST ------------------------

		if (pBuffer->up == pNullNode)
			pRoot = pNullNode;//pChildBuffer;
		else
		{
			if (pBuffer->up->left == pBuffer)
				pBuffer->up->left = pNullNode;
			else
				pBuffer->up->right = pNullNode;
		}

		// �� ����
		deletedNodeColor = pBuffer->color;
	}

	if (deletedNodeColor == BLACK)
	{
		if (pChildBuffer->color == BLACK)
			_ChangeForDelete(pChildBuffer);
		else
			pChildBuffer->color = BLACK;
	}

	pRoot->color = BLACK;

	// TEST ------------------------
	pNullNode->up = nullptr;
	// TEST ------------------------

	//delete pBuffer;
	delete pDeletedNode;
};


/*
	_ChangeForDelete(rbTreeNode<KEY, VALUE>* pInNode);
		- Delete �Լ� ���ο��� ���Ǹ�, ��带 Delete �� �Ŀ���, Red-Black Tree�� Ư¡�� �����ϱ� ���� �˻� �� ó���� ���ִ� �Լ��Դϴ�.
	
	#1. ���� �̷��� ��Ű ���, ����-�� Ʈ���� Ȯ���� �ּ���! https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC
	
	���� : Delete�� ����� NextNode( Successor )�� ChildNode (dir - Right)
	��� : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_ChangeForDelete(rbTreeNode<KEY, VALUE>* pInNode)
{
LIKE_RECURSION:

	// [Delete_Case_1]
	if (pInNode->up == pNullNode)
		return;

	// [Delete_Case_2]
	rbTreeNode<KEY, VALUE>* pSiblingNode = _GetSiblingNode(pInNode);

	if (pSiblingNode->color == RED)
	{
		pInNode->up->color = RED;
		pSiblingNode->color = BLACK;

		// �� ��尡, �θ��� ���� �ڽ��� ���
		if (pInNode == pInNode->up->left)
			_LeftRotate(pInNode->up);
		// �� ��尡, �θ��� ������ �ڽ��� ���
		else
			_RightRotate(pInNode->up);
	}

	// [Delete_Case_3]

	pSiblingNode = _GetSiblingNode(pInNode);

	if (pInNode->up->color == BLACK && pSiblingNode->color == BLACK && pSiblingNode->left->color == BLACK && pSiblingNode->right->color == BLACK)
	{
		pSiblingNode->color = RED;
		pInNode = pInNode->up;
		goto LIKE_RECURSION;
		// [Delete_Case_1] pInNode->up;
	}

	// [Delete_case_4]

	else if (pInNode->up->color == RED && pSiblingNode->color == BLACK && pSiblingNode->left->color == BLACK && pSiblingNode->right->color == BLACK)
	{
		pSiblingNode->color = RED;
		pInNode->up->color = BLACK;
	}

	else {
		// [Delete_case_5]

		if (pSiblingNode->color == BLACK)
		{
			if (pInNode == pInNode->up->left && pSiblingNode->right->color == BLACK && pSiblingNode->left->color == RED)
			{
				pSiblingNode->color = RED;
				pSiblingNode->left->color = BLACK;
				_RightRotate(pSiblingNode);
			}
			else if (pInNode == pInNode->up->right && pSiblingNode->left->color == BLACK && pSiblingNode->right->color == RED)
			{
				pSiblingNode->color = RED;
				pSiblingNode->right->color = BLACK;
				_LeftRotate(pSiblingNode);
			}
		}

		// [Delete_case_6]
		pSiblingNode = _GetSiblingNode(pInNode);

		pSiblingNode->color = pInNode->up->color;
		pInNode->up->color = BLACK;

		if (pInNode == pInNode->up->left)
		{
			pSiblingNode->right->color = BLACK;
			_LeftRotate(pInNode->up);
		}
		else {
			pSiblingNode->left->color = BLACK;
			_RightRotate(pInNode->up);
		}
	}
};


/*
	DeleteWithSearch(const KEY& InKey);
	
		- Ű�� ���ڷ� �޾�, �ش� Ű�� �ش��ϴ� ��带 ã��, �� ��带 �����մϴ�.

		#1. Ptr�� ����ϴ� ���� �Լ� (Delete) ���� �翬�� ���̽��ϴ�.

		!1. ���ο��� Node�� ���� �޸� ȸ��(delete) �� �Ͼ�ϴ�.

		!2. ����, �ܺο��� �ش� ��忡 �����͸� ���� ������ ���� ���, nullptr������ �� ���ɼ��� Ů�ϴ�.

	���� : �����Ϸ��� ����� Ű��.

	��� : bool�� - ��� ���� ���� ( == �ش� Ű�� ���� ����� ���� ���� )
*/

template <typename KEY, typename VALUE>
bool rbTree<KEY, VALUE>::DeleteWithSearch(const KEY& InKey)
{
	bool retBoolBuffer; 
	
	if (rbTreeNode<KEY, VALUE>* pDeletedNode = this->Search(InKey, retBoolBuffer), 
		retBoolBuffer)
	{
		Delete(pDeletedNode);

		return true;
	}
	else
	{
		return false;
	}
}

// ================================== Rotate

/*
	_LeftRotate(rbTreeNode<KEY, VALUE>* pRetNode)
		Ʈ���������� ���� ȸ���� �õ��մϴ�.

		#1. https://en.wikipedia.org/wiki/Tree_rotation

	���� : ȸ���� ������ �Ǵ� ����� ������
	��� : void
*/

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

/*
	_RightRotate(rbTreeNode<KEY, VALUE>* pRetNode)
		Ʈ���������� ������ ȸ���� �õ��մϴ�.

	#1. https://en.wikipedia.org/wiki/Tree_rotation

	���� : ȸ���� ������ �Ǵ� ����� ������
	��� : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_RightRotate(rbTreeNode<KEY, VALUE>* pRetNode)
{
	rbTreeNode<KEY, VALUE>* pParentNode = pRetNode->up;
	rbTreeNode<KEY, VALUE>* pLeftChildNode = pRetNode->left;

	// �ּ� _LeftRotate �ϰ� �����մϴ�..�� ���� �ʹ� �������...

	if (pParentNode == pNullNode)
		pRoot = pLeftChildNode;
	else
	{
		if (pRetNode == pRetNode->up->left)
			pRetNode->up->left = pLeftChildNode;
		else
		pParentNode->right = pLeftChildNode;
	}

	pLeftChildNode->up = pRetNode->up;

	pRetNode->left = pLeftChildNode->right;
	pLeftChildNode->right->up = pRetNode;

	pLeftChildNode->right = pRetNode;
	pRetNode->up = pLeftChildNode;
};


// ================================== GetNode Function

/*
	_GetPrevNode(rbTreeNode<KEY, VALUE>* InNode);
		Predecessor�� ���ϴ� �Լ�, ������ �ʽ��ϴ�.
	
	���� : Delete�Ǿ�, PrevNode�� ���ؾ��ϴ� ����� ������
	��� : Predecessor Node's Pointer
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetPrevNode(rbTreeNode<KEY, VALUE>* const pInNode)
{
	rbTreeNode<KEY, VALUE>* pRetNode = pInNode;

	// ������ NullNode�� �ƴ� ���, 
	if (pRetNode->left != pNullNode) {

		// �������� �����͸� �� �� �̵��ϰ� (���� ����Ʈ���� �����ϰ�)
		pRetNode = pRetNode->left;

		// �ش� ����Ʈ������ ���� ū �� (���� Right�� �ִ� ���)�� ã��,
		while (pRetNode->right != pNullNode)
		{
			pRetNode = pRetNode->right;
		}

		// �ش� ��带 �����մϴ�.
		return pRetNode;
	}
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
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetNextNode(rbTreeNode<KEY, VALUE>* const InNode)
{
	rbTreeNode<KEY, VALUE>* RetNode = InNode;

	// ������ NullNode�� �ƴ� ���, 
	if (RetNode->right != pNullNode) {

		// �������� �����͸� �� �� �̵��ϰ� (���� ����Ʈ���� �����ϰ�)
		RetNode = RetNode->right;

		// �ش� ����Ʈ������ ���� ���� �� (���� Left�� �ִ� ���)�� ã��,
		while (RetNode->left != pNullNode)
		{
			RetNode = RetNode->left;
		}

		// �ش� ��带 �����մϴ�.
		return RetNode;
	}
};


/*
	_GetSiblingNode(rbTreeNode<KEY, VALUE>* pInNode);
		- pInNode�� ���� ����� �����͸� ���ϴ� �Լ��Դϴ�.
	
	���� : ����� ������
	��� : ���� ����� ������
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetSiblingNode(rbTreeNode<KEY, VALUE>* const pInNode)
{
	rbTreeNode<KEY, VALUE>* pBufferNode = pInNode->up;

	if (pBufferNode->left == pInNode) 
	{
		return pBufferNode->right;
	}
	else //if (pBufferNode->right == pInNode)
	{
		return pBufferNode->left;
	}
	//else
	//{
	//	std::cout << "Error - ���� ��带 ��ȯ�ϴ� �Լ����� ���ܰ� �߻��߽��ϴ�. \n";
	//}
}


/*
	_GetUncleNode(rbTreeNode<KEY, VALUE>* pInNode);
		- pInNode�� Uncle ����� �����͸� ���ϴ� �Լ��Դϴ�.
	
	���� : ����� ������
	��� : ���� ����� ������
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetUncleNode(rbTreeNode<KEY, VALUE>* const pInNode) 
{
	rbTreeNode<KEY, VALUE>* pGrandParentNode = pInNode->up->up;

	if (pInNode->up == pGrandParentNode->left)
		return pGrandParentNode->right;
	else
		return pGrandParentNode->left;
	//else
	//{
	//		std::cout << "Error - Uncle ��带 ��ȯ�ϴ� �Լ����� ���ܰ� �߻��߽��ϴ�. \n";
	//}
}


// ================================== Debug Function

//Debug Function

/*
	!1. ���ο��� ����Լ��� ����ϰ� �ֽ��ϴ�. Ʈ�� ���̰� ���� ���, ���� �����÷ο찡 �߻��� �� �ֽ��ϴ�.
		(����� �뵵�θ� ����ϴ� ���� ��õ�帳�ϴ�.)
*/

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

#pragma endregion