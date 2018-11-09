#pragma once

#define INLINE __inline

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

	#2. 아 근데 1번 안해봤어요...사실 해도 안될수도 있어요! ㅎ
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
	// Define the constructor for pNullNode, buffer #1 Key, Value에 대한 기본생성자가 필요합니다.
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
	// Define Color RED = true, BLACK = false;
	enum
	{
		RED			=		true	,	//TRUE
		BLACK		=		false		//FALSE
	};

	rbTreeNode<KEY, VALUE>*			pNullNode;	// NullNode's Color is Black.
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
		// 다른 Node들에 대한 처리가 필요할 수 있음. 처리안하고 고냥 딤질 수 있음. 알아서 delete 해라 마.

		if (pRoot != nullptr)
			delete pRoot;
		pRoot = nullptr;

		if(pNullNode != nullptr)
			delete pNullNode;
		pNullNode = nullptr;
	};

public:
	rbTreeNode<KEY, VALUE>*			Search(const KEY& InKey, bool& RetResult) const ;			// 해당 Key값으로 검색하여, True시 노드 포인터 리턴, False시 없음(pNullNode Return). 

	rbTreeNode<KEY, VALUE>*			Insert(const KEY& InKey, const VALUE& InValue);		// 해당 key값과, Value 값을 가지고, 내부에서 할당하여 트리에 삽입 후, 해당 노드에 대한 포인터 리턴.
	void							Delete(rbTreeNode<KEY, VALUE>* DeletedNode);		// 해당 노드를 내부에서 delete 해줌. 

private:
	void							_ChangeForInsert(rbTreeNode<KEY, VALUE>* RetNode);    
	void							_ChangeForDelete(rbTreeNode<KEY, VALUE>* RetNode);

	void							_LeftRotate(rbTreeNode<KEY, VALUE>* RetNode);
	void							_RightRotate(rbTreeNode<KEY, VALUE>* RetNode);

	INLINE rbTreeNode<KEY, VALUE>*	_GetPrevNode(rbTreeNode<KEY, VALUE>* InNode);
	INLINE rbTreeNode<KEY, VALUE>*	_GetNextNode(rbTreeNode<KEY, VALUE>* InNode);

	INLINE rbTreeNode<KEY, VALUE>*	_GetSiblingNode(rbTreeNode<KEY, VALUE>* InNode);
	INLINE rbTreeNode<KEY, VALUE>*	_GetUncleNode(rbTreeNode<KEY, VALUE>* InNode);

//for Debug
public:
	void					PrintTree();

private:
	void					_PrintNodes(rbTreeNode<KEY, VALUE>* pNodeBuffer);
};

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

#pragma region [ 삽입하는 노드의 자식노드 및 색 설정 ]

	// 삽입한 노드 후처리입니다. 자식 좌, 우는 pNullNode로 설정해줍니다, 레드 - 블랙트리 법칙에 의해, 삽입한 노드의 색은 RED(TRUE)로 설정해줍니다.
	// 아래 3줄은, 생성자에서 처리.
	//pRetNode->left = pNullNode;
	//pRetNode->right = pNullNode;
	//pRetNode->color = RED;

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
	{
		pRoot = pRetNode;
	}
	else 
	{
		// 트리의 최초 노드가 아닐 경우, 부모 노드( pParentNode == pRetNode->up)의 키 값과 비교해, 부모 노드에서의 위치 (Left Or Right)를 결정 후 연결해줍니다.
		if (pRetNode->GetKey() < pParentNode->GetKey() /* ==  pRetNode->up->GetKey()	*/)
			pParentNode->left = pRetNode;
		else
			pParentNode->right = pRetNode;

		// 위에 사용했던 포인트 재사용. 원본을 잘못쓰는 경우 방지.
		pTraversalNode = pRetNode;

		// 삽입 시, 균형 여부를 검사하고 관련 필요 처리를 하는 함수입니다. ( [Insert Case 1 ] 첫 삽입일때는 필요없습니다.(위의 if문, -- if (pParentNode == pNullNode) )
		_ChangeForInsert(pTraversalNode);
	}

#pragma endregion

	// 레드 - 블랙트리 법칙에 의해, 어떤 변환이 일어나든, 최종적으로 적색나무에서 루트 노드는 항상 검정색을 유지해야합니다.
	pRoot->color = BLACK;

	////(디버그)삽입 할때마다, 트리를 출력합니다.
	//this->PrintTree();

	// 삽입한 노드를 리턴해줍니다.
	return pRetNode;
};


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
LIKE_RECURSION:

	// [Insert Case 2] 이미 기존의 트리는, 레드 블랙 트리의 성질을 만족하기 때문에, 부모의 노드가 검정색일 경우, 고려해야할 문제는 없습니다.  // 해당 조건은 Insert Case 1도 포함하는 조건입니다.
	if (pRetNode->up->color == BLACK)
	{
		return;
	}
	
	rbTreeNode<KEY, VALUE>* pUncleNode = _GetUncleNode(pRetNode); // UncleNode Pointer : 
	rbTreeNode<KEY, VALUE>* pGrandNode = pRetNode->up->up; // 조부모(왕부모) 노드 --> nullNode일 경우는 없습니다.

	// [Insert Case 3] Recoloring - 부모노드와 UncleNode 모두 빨간색일 때, 이를 모두 검정색으로 바꾸고, 조부모노드를 빨간색으로 변경함. 
	if (pUncleNode->color == RED /*&& pUncleNode != pNullNode // 이 조건은 빨간색에 포함. */)
	{
		pRetNode->up->color = BLACK;
		pUncleNode->color = BLACK;
		pGrandNode->color = RED;

		// 이 조부모노드를 빨간색으로 변경했기 때문에, 이에 대해 동일하게 레드블랙트리 조건(더블 레드 테스트 불허용)에 대한 검사가 필요함.
		//_ChangeForInsert(pGrandNode); // <- 재귀함수를 사용하지 않음 ( 메모리 오버헤드 )

		// 노드 포인터를 변경 후, pGrandNode으로 변경 후, goto문으로 함수 첫째줄로 이동.
		pRetNode = pGrandNode;
		goto LIKE_RECURSION;
		//return;
	}

	// [Insert Case 4] Restructuring - 부모노드는 빨간색이나, UncleNode는 검은색일 때, 모양에 따라. 작은 회전을 해줌 ( 결과는 규칙에 위반됨! 더블 레드 상태 )
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
	*/
};


/*
	Delete(rbTreeNode<KEY, VALUE>* DeletedNode);
		- 인자로 제공되는 노드의 포인터를 활용해, 해당 노드를 삭제합니다.
		#1. 내부에서 Node에 대한 메모리 회수(delete) 가 일어납니다.
		?1. deleted된 노드의 포인터가 pNullNode를 가르키면, nullptr 관련 에러를 방지하지 않을까?

	인자 : 제거하려는 노드의 포인터

	출력 : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::Delete(rbTreeNode<KEY, VALUE>* pDeletedNode)
{
	// 제거하려는 노드가 pNullNode가 아닌지 확인합니다. (pNullNode 제거하면 클납니다.) 실제에서는 이럴 일 거의 없기 떄문에, 주석처리.
	if (pDeletedNode == pNullNode)
	{
		return;
	}
	
	rbTreeNode<KEY, VALUE>* pBuffer = pNullNode;
	rbTreeNode<KEY, VALUE>* pChildBuffer = pNullNode;
	bool deletedNodeColor = BLACK;

	// 자식 노드 수 검사. --> 두개 다 살아있음.
	if (pDeletedNode->left != pNullNode && pDeletedNode->right != pNullNode)
	{
		pBuffer = _GetNextNode(pDeletedNode);
 		pChildBuffer = pBuffer->right;
		
		// GetNextNode가 바로, 다음 우측 자식일 때는 예외필요.
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

		// NextNode의 정보를, pDeletedBuffer로 전달해줌. (실제 삭제하는 노드는 pBuffer이기 떄문에) --> [DEV_55] (bug_3) nullptr 참조 오류 발생.
		// Data Copy
		//pDeletedNode->key = pBuffer->key;
		//pDeletedNode->value = pBuffer->value;

		// (!Data) Copy
		// 위의 Data Copy 시에는, 만약 해당 pBuffer의 ptr에 해당하는 노드를 포인터로 저장하고 활용하는 포인터 변수가 nullptr가 일어날 경우가 있기 때문에 nodeSwap을 해줌.
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

		// 삭제하는 노드의 부모와 연결
		pBuffer->up = pDeletedNode->up;

		// 삭제하는 노드의 자식들과 연결.
		pDeletedNode->left->up = pBuffer;
		pBuffer->left = pDeletedNode->left;

		// GetNextNode가 바로, 다음 우측 자식일 때는 예외필요.
		if (pDeletedNode->right != pBuffer)
		{
			pDeletedNode->right->up = pBuffer;
			pBuffer->right = pDeletedNode->right;
		}

		// 컬러 버퍼 설정.
		deletedNodeColor = pBuffer->color;
		pBuffer->color = pDeletedNode->color;
	}
	// 자식의 왼쪽 노드만 살아있음.
	else if (pDeletedNode->left != pNullNode)
	{
		pBuffer = pDeletedNode;
		pChildBuffer = pBuffer->left;

		// 자식에게 새 부모 알림.
		pChildBuffer->up = pBuffer->up;

		// 삭제되는 노드가 root였을 경우, ChildBuffer 가 자식이 되도록 함.
		if (pBuffer->up == pNullNode)
			pRoot = pChildBuffer;
		else 
		{
			// pBuffer의 부모에게, 새 자식을 알려줌.
			if (pBuffer->up->left == pBuffer)
				pBuffer->up->left = pChildBuffer;
			else
				pBuffer->up->right = pChildBuffer;
		}
		// 색 저장
		deletedNodeColor = pBuffer->color;
	}
	// 자식의 오른쪽 노드만 살아있음.
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

		// 색 저장
		deletedNodeColor = pBuffer->color;
	}
	// 자식이 없음.
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

		// 색 저장
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

		// 현 노드가, 부모의 왼쪽 자식일 경우
		if (pInNode == pInNode->up->left)
			_LeftRotate(pInNode->up);
		// 현 노드가, 부모의 오른쪽 자식일 경우
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

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_LeftRotate(rbTreeNode<KEY, VALUE>* pRetNode)
{
	rbTreeNode<KEY, VALUE>* pParentNode = pRetNode->up;
	rbTreeNode<KEY, VALUE>* pRightChildNode = pRetNode->right;

	// RetNode가 현재 트리의 pRootNode일 때 ( 오른쪽 자식이 루트가 됨 (LeftRotate) )
	if (pParentNode == pNullNode)
		pRoot = pRightChildNode;
	else
	{
		//현재 노드가 부모 노드의 왼쪽 자식 노드일때,
		if (pRetNode == pParentNode->left)
			pParentNode->left = pRightChildNode;

		//현재 노드가 부모 노드의 오른쪽 자식 노드일때,
		else
			pParentNode->right = pRightChildNode;
	}

	//현재 Ret의 부모노드와, Ret의 오른쪽 자식 노드를 부모관계로 바꿔주고, Ret노드는 자식노드의 자식으로 변경합니다.

	// 내 부모님은 사실, 내 자식의 부모님이다.
	pRightChildNode->up = pRetNode->up;

	// 내 자식은 사실, 내 자식의 자식 - 손자다.
	pRetNode->right = pRightChildNode->left;

	// 따라서 내 자식 - 손자의 부모는 나다.
	pRightChildNode->left->up = pRetNode;

	// ...나는 내 예전 자식의 자식이다.
	pRightChildNode->left = pRetNode;

	// 결국 내 부모님은 내 옛 자식이다.
	pRetNode->up = pRightChildNode;
};

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_RightRotate(rbTreeNode<KEY, VALUE>* pRetNode)
{
	rbTreeNode<KEY, VALUE>* pParentNode = pRetNode->up;
	rbTreeNode<KEY, VALUE>* pLeftChildNode = pRetNode->left;

	// 주석 _LeftRotate 하고 동일합니다..

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

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetPrevNode(rbTreeNode<KEY, VALUE>* InNode)
{
	rbTreeNode<KEY, VALUE>* RetNode = InNode;

	// 좌측이 널값이 아닐 경우, 
	if (RetNode->left != pNullNode) {

		RetNode = RetNode->left;

		while (RetNode->right != pNullNode)
		{
			RetNode = RetNode->right;
		}

		return RetNode;
	}
	//	rbTreeNode<KEY, VALUE>* bufferNode = InNode->up;
	//
	//	while (bufferNode != pNullNode && InNode == bufferNode->right) 
	//	{
	//		InNode = bufferNode;
	//		bufferNode = bufferNode->up;
	//	}
	//
	//	return bufferNode;
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
	rbTreeNode<KEY, VALUE>* RetNode = InNode;

	// 우측이 널값이 아닐 경우, 
	if (RetNode->right != pNullNode) {

		RetNode = RetNode->right;

		while (RetNode->left != pNullNode)
		{
			RetNode = RetNode->left;
		}

		return RetNode;
	}
//	rbTreeNode<KEY, VALUE>* bufferNode = InNode->up;
//
//	while (bufferNode != pNullNode && InNode == bufferNode->right) 
//	{
//		InNode = bufferNode;
//		bufferNode = bufferNode->up;
//	}
//
//	return bufferNode;
};

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetSiblingNode(rbTreeNode<KEY, VALUE>* pInNode)
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
	//	std::cout << "Error - 형제 노드를 반환하는 함수에서 예외가 발생했습니다. \n";
	//}
}

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetUncleNode(rbTreeNode<KEY, VALUE>* pInNode) 
{
	rbTreeNode<KEY, VALUE>* pGrandParentNode = pInNode->up->up;

	if (pInNode->up == pGrandParentNode->left)
		return pGrandParentNode->right;
	else
		return pGrandParentNode->left;
	//else
	//{
	//		std::cout << "Error - Uncle 노드를 반환하는 함수에서 예외가 발생했습니다. \n";
	//}
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