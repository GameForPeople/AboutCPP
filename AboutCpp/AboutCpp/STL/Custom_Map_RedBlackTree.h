#pragma once

//declare
template <typename KEY, typename VALUE>
class rbTree;

/*
	rbTreeNode는 rbTree에 사용되는 Node객체입니다.
	Key-Value 구조, 즉 std::Map에 영향을 받아, Pair의 형태를 띄고 있습니다.
 
	#1. Key에 사용되는 객체가 직접 만드신 객체일 경우, 키값 비교에 사용될 연산자 operator가 필요합니다.

		해당 예제는 다음과 같습니다.
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
	// for pNullNode, buffer #1 Key, Value에 대한 기본생성자가 필요합니다.
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
		// 다른 Node들에 대한 처리가 필요할 수 있음. 고냥 딤질 수 있음. 마 알아서 delete 해라 마.

		if (pRoot != nullptr)
			delete pRoot;

		if(pNullNode != nullptr)
			delete pNullNode;
	};

public:
	rbTreeNode<KEY, VALUE>*	Search(const KEY& InKey, bool& RetResult) const ;			// 해당 Key값으로 검색하여, True시 노드 포인터 리턴, False시 없음(pNullNode Return). 

	rbTreeNode<KEY, VALUE>* Insert(const KEY& InKey, const VALUE& InValue);		// 해당 key값과, Value 값을 가지고, 내부에서 할당하여 트리에 삽입 후, 해당 노드에 대한 포인터 리턴.
	void					Delete(rbTreeNode<KEY, VALUE>* DeletedNode);		// 해당 노드를 내부에서 delete 해줌. 

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
		- 주어진 키 값을 가지고, 트리에서 노드를 찾는 함수.

	인자 : 탐색하는 노드의 키 값, 탐색 성공 여부

	출력 : 노드 포인터(리턴값), 탐색 성공 여부(인자)
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>* rbTree<KEY, VALUE>::Search(const KEY& InKey, bool& RetResult) const
{
	// 최초 Search 결과를 거짓으로 둠.
	RetResult = false;

	// 리턴할 포인터를 선언하고, pRootNode로 설정함.
	rbTreeNode<KEY, VALUE>*  RetNodeBuffer = pRoot;

	while (true)
	{
		// 리턴할 노드 포인터 (검사하는 노드) 가 pNullNode일때 ( False ) 
		if (RetNodeBuffer == pNullNode)
		{
			RetResult = false;
			break;
		}

		// 찾는 키 (함수 인자)와 현재 검사하는 노드의 키가 동일할 때, (True)
		if (InKey == RetNodeBuffer->GetKey())
		{
			RetResult = true;
			break;
		}

		// 키 비교를 통한, Left Or Right 결정 (트리 구조에서의 탐색)
		if (InKey < RetNodeBuffer->GetKey())
			RetNodeBuffer = RetNodeBuffer->left;
		else
			RetNodeBuffer = RetNodeBuffer->right;
	}
};


/*
	Insert(const KEY& InKey, const VALUE& InValue);
		- 인자로 제공되는 해당 키, 결과 값을 가지는 노드를 삽입하는 함수. 
		#1. 동일한 키값에 대하여 Insert를 요청할 경우, 오류의 원인이 될 수 있습니다.
		#2. 내부에서 Node에 대한 할당(new) 가 일어납니다.

	인자 : 노드의 키, 데이터

	출력 : 해당 노드에 대한 포인터 제공.
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>* rbTree<KEY, VALUE>::Insert(const KEY& InKey, const VALUE& InValue)
{
#pragma region [ 삽입할 노드 할당 & 필요한 포인터 변수 정의 ]

	// 리턴할 노드의 포인터를 선언하고, 할당해줍니다. ( Key, Value는 인자 전달 (Node에서 생성자 정의됨)
	rbTreeNode<KEY, VALUE>* pRetNode = new rbTreeNode<KEY, VALUE>(InKey, InValue, pNullNode, RED);

	// 필요한 포인터들을 생성합니다.
	rbTreeNode<KEY, VALUE>* pTraversalNode = pRoot;			// 순회노드버퍼, 리턴 노드의 위치를 탐색하기 위해 순회하는 포인터입니다.
	rbTreeNode<KEY, VALUE>* pParentNode = pNullNode;		// 부모노드버퍼, 부모 노드를 저장해두기 위한 포인터입니다.

#pragma endregion

#pragma region [ 삽입하는 노드의 부모노드 찾기 ]
	// 삽입될 수 있는 빈 자리까지 이동합니다.
	// pTraversalNode는 pRetNode가 삽입될 수 있는 위치(정확히는 트리의 리프노드의 자식)까지 이동하는 노드-포인터 입니다.
	// pParentNode는 pNodeA의 이전 while문에서의 위치( 현재 pNodeA의 부모 노드 포인터) 입니다.
	while (pTraversalNode != pNullNode)
	{
		//현재 위치를 pParentNode에 저장하고, 다음 위치로 이동합니다.
		pParentNode = pTraversalNode;

		//키 비교를 통해, 적합한 노드의 위치 (Left Or Right)를 결정합니다. (트리 구조에서의 탐색)
		if (pRetNode->GetKey() /* == InKey */	< pTraversalNode->GetKey())
			pTraversalNode = pTraversalNode->left;
		else
			pTraversalNode = pTraversalNode->right;
	}

	// 리턴하는 포인터의 up Point(부모 노드 위치)에 먼저, pParentNode(이전 노드 포인터 - 부모 위치)를 넣어줍니다.
	pRetNode->up = pParentNode;
#pragma endregion

#pragma region [ 삽입하는 노드의 위치 정하기 ]

	// 현재 부모 노드(RetNode->up == oldBuffer)가 pNullNode일 경우, 삽입한 노드는 트리의 pRoot노드가 됩니다.
	if (pParentNode == pNullNode)
		pRoot = pRetNode;
	else 
	{
		// 트리의 최초 노드가 아닐 경우, 부모 노드( pParentNode == pRetNode->up)의 키 값과 비교해, 부모 노드에서의 위치 (Left Or Right)를 결정 후 연결해줍니다.
		if (pRetNode->GetKey() < pParentNode->GetKey() /* ==  pRetNode->up->GetKey()	*/)
			pParentNode->left = pRetNode;
		else
			pParentNode->right = pRetNode;
	}

#pragma endregion

#pragma region [ 삽입한 노드의 자식노드 및 색 설정 ]

	// 삽입한 노드 후처리입니다. 자식 좌, 우는 pNullNode로 설정해줍니다, 레드 - 블랙트리 법칙에 의해, 삽입한 노드의 색은 RED(TRUE)로 설정해줍니다.
	// 아래 3줄은, 생성자에서 처리.
	//pRetNode->left = pNullNode;
	//pRetNode->right = pNullNode;
	//pRetNode->color = RED;

#pragma endregion

	// 삽입 시, 균형 여부를 검사하고 관련 필요 처리를 하는 함수입니다.
	_ChangeForInsert(pRetNode);

	// 레드 - 블랙트리 법칙에 의해, 어떤 변환이 일어나든, 최종적으로 적색나무에서 루트 노드는 항상 검정색을 유지해야합니다.
	pRoot->color = BLACK;

	// 삽입한 노드를 리턴해줍니다.
	return pRetNode;
};


/*
	Delete(rbTreeNode<KEY, VALUE>* DeletedNode);
		- 인자로 제공되는 노드의 포인터를 활용해, 해당 노드를 삭제합니다.
		#1. 내부에서 Node에 대한 메모리 회수(delete) 가 일어납니다.
		?1. deleted된 노드의 포인터가 pNullNode를 가르키면, nullptr 관련 에러를 방지하지 않을까?

	인자 : 노드의 포인터

	출력 : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::Delete(rbTreeNode<KEY, VALUE>* DeletedNode)
{
	// 제거하려는 노드가 pNullNode가 아닌지 확인합니다. (pNullNode 제거하면 클납니다.)
	if (DeletedNode != pNullNode)
	{
		rbTreeNode<KEY, VALUE>* nodeA = pNullNode;
		rbTreeNode<KEY, VALUE>* nodeB = pNullNode;

		//삭제하는 노드의 자식 개수 여부를 확인합니다.
		if (DeletedNode->left == pNullNode || DeletedNode->right == pNullNode)
			nodeB = DeletedNode;
		else
			// 자식이 있을 경우, 해당 자리에 어떤 노드가 와야하는지를 구합니다.
			nodeB = _GetNextNode(DeletedNode);

		// 새로 위치되는 노드의 자식여부를 검사합니다. 해당 노드는 항상 0 또는 1 개의 자식을 가집니다. ( 2개의 자식을 가질 수 없습니다. #1 pNullNode는 자식 카운트에서 제외합니다.)
		if (nodeB->left != pNullNode)
			nodeA = nodeB->left;
		else
			nodeA = nodeB->right;

		nodeA->up = nodeB->up;

		// 어떤 노드의 부모노드가 pNullNode일 때는, 해당 노드가 pRootNode임을 뜻합니다.
		if (nodeB->up == pNullNode)
			pRoot = nodeA;
		// nodeB의 부모와, nodeA를 연결짓습니다.
		else
		{
			if (nodeB == nodeB->up->left)
				nodeB->up->left = nodeA;
			else
				nodeB->up->right = nodeA;
		}

		// nodeB가 
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
	- Insert 함수 내부에서 사용되며, 노드를 Insert 한 후에도, Red-Black Tree의 특징을 유지하기 위해 검사 및 처리를 해주는 함수입니다.

	#1. 관련 이론은 위키 백과, 레드-블랙 트리를 확인해 주세요! https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC

	인자 : Insert된 노드의 포인터

	출력 : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_ChangeForInsert(rbTreeNode<KEY, VALUE>* pRetNode)
{
	while (pRetNode->up->color == RED)
	{
		// (의역) 우리 아빠가, 할아버지의 첫째 아들일때,...?
		if (pRetNode->up == pRetNode->up->up->left)
			// Uncle Node 의 위치 찾기. --> Uncle이 Right!
		{
			rbTreeNode<KEY, VALUE>* uncleNode = pRetNode->up->up->right;

			if (uncleNode->color == RED)
			{
				//삽입에서의 3번째 경우.

				// 색 변경. (Recoloring)
				pRetNode->up->color = BLACK;
				uncleNode->color = BLACK;

				pRetNode->up->up->color = RED;

				// Red 색으로, 부모의 부모노드 변환 시, 해당 노드에 대한 Double Red Test 필요.
				pRetNode = pRetNode->up->up;
			}
			else {
				//삽입에서의 4번째 경우.

				// 모습 변경 (Restructuring)
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
			// Uncle Node 의 위치 찾기. --> Uncle이 Left!
		{
			rbTreeNode<KEY, VALUE>* uncleNode = pRetNode->up->up->left;

			if (uncleNode->color == RED)
			{
				// 색 변경. (Recoloring)
				pRetNode->up->color = BLACK;
				uncleNode->color = BLACK;

				pRetNode->up->up->color = RED;

				// Red 색으로, 부모의 부모노드 변환 시, 해당 노드에 대한 Double Red Test 필요.
				pRetNode = pRetNode->up->up;
			}
			else {
				// 모습 변경 (Restructuring)
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

	// RetNode가 현재 트리의 pRootNode일 때 ( 오른쪽 자식이 루트가 됨 (LeftRotate) )
	if (RetNode->up == pNullNode)
		pRoot = rightChildNode;
	else
	{
		//현재 노드가 부모 노드의 왼쪽 자식 노드일때,
		if (RetNode == RetNode->up->left)
			RetNode->up->left = rightChildNode;

		//현재 노드가 부모 노드의 오른쪽 자식 노드일때,
		else
			RetNode->up->right = rightChildNode;
	}

	//현재 Ret의 부모노드와, Ret의 오른쪽 자식 노드를 부모관계로 바꿔주고, Ret노드는 자식노드의 자식으로 변경합니다.

	// 내 부모님은 사실, 내 자식의 부모님이다.
	rightChildNode->up = RetNode->up;

	// 내 자식은 사실, 내 자식의 자식 - 손자다.
	RetNode->right = rightChildNode->left;

	// 따라서 내 자식 - 손자의 부모는 나다.
	rightChildNode->left->up = RetNode;

	// ...나는 내 예전 자식의 자식이다.
	rightChildNode->left = RetNode;

	// 결국 내 부모님은 내 옛 자식이다.
	RetNode->up = rightChildNode;
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_RightRotate(rbTreeNode<KEY, VALUE>* RetNode)
{
	rbTreeNode<KEY, VALUE>* leftChildNode = RetNode->left;

	// 주석 _LeftRotate 하고 동일합니다..

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
	참고(영어입니다.) : https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/

	조금 말씀드리면, 제가 영어가 부족해 GetNextNode라는 함수명을 썻으나
	관련 명칭은 Predecessor, Successor이며 각각, 해당 노드의 좌측 서브트리의 최대값 (Predecessor), 해당 노드의 우측 서브트리의 최소값 (Successor) 입니다.

	이를 구해야할 경우는, 
	삭제되는 노드가 두 개의 pNullNode가 아닌 자식을 가질 경우, 해당 노드의 자리에 어떤 노드가 와야하는 지를 구하는 것이며,
	그 자리에 올 수 있는 노드는 Predecessor 또는 Successor가 있습니다.

	참고로 삭제하는 노드가 자식이 없을 경우, 고냥 삭제하면 되고,
	삭제하는 노드가 1개의 자식을 갖고 있을 경우, 해당 자식을 그 자리에 위치시키면 됩니다(like list)
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetNextNode(rbTreeNode<KEY, VALUE>* InNode)
{
	// 우측이 널값이 아닐 경우, 
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