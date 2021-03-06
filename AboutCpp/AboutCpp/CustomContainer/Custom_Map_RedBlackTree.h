#pragma once

/*
	Custom_Map_RedBlackTree.h

	2018/11/11

		- Key와 Value를 가지는 STL::MAP을 흉내낸(물론 발끝도 못 따라갑니다. ), 레드블랙트리(적흑나무) 입니다.
		- 학습용이지 (사실 학습용으로 사용하기도...), 프로젝트에 사용하면시 안됩니다.. 버그 있을 확률 거의 백프로여요. 성능도 안좋고, 제공하는 함수도 없어요... STL Map, Set 쓰셔요!
*/

#define INLINE __inline

#pragma region [ Declare rbTreeNode, rbTree ]

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
		// 다른 Node들에 대한 처리가 필요할 수 있음. 처리안하고 고냥 딤질 수 있음. 알아서 delete 해라 마.

		if (pRoot != nullptr)
			delete pRoot;
		pRoot = nullptr;

		if(pNullNode != nullptr)
			delete pNullNode;
		pNullNode = nullptr;
	};

public:
	rbTreeNode<KEY, VALUE>*			Search(const KEY& InKey, bool& RetResult) const ;		// 해당 Key값으로 검색하여, True시 노드 포인터 리턴, False시 없음(pNullNode Return). 

	rbTreeNode<KEY, VALUE>*			Insert(const KEY& InKey, const VALUE& InValue);			// 해당 key값과, Value 값을 가지고, 내부에서 할당하여 트리에 삽입 후, 해당 노드에 대한 포인터 리턴.

	void							Delete(rbTreeNode<KEY, VALUE>* DeletedNode);			// 인자로 전달된 노드의 포인터를 통해, 해당 노드를 제거해줍니다.
	bool							DeleteWithSearch(const KEY& InKey);						// 해당 키에 해당하는 노드를 찾아 제거해줍니다.

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


// ================================== Insert

/*
	Insert(const KEY& InKey, const VALUE& InValue);
		- 인자로 제공되는 해당 키, 결과 값을 가지는 노드를 삽입하는 함수. 
		!1. 기존에 트리에 존재하는 노드에 대한 동일한 키값에 대하여 Insert를 요청할 경우, 오류의 원인이 될 수 있습니다.
		!2. 내부에서 Node에 대한 할당(new) 가 일어납니다.

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

	// 레드 - 블랙트리 법칙에 의해, 어떤 변환이 일어나든, 최종적으로 적색나무에서의 루트 노드는 항상 검정색을 유지해야합니다.
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

	// [Insert Case 2] 이미 기존의 트리는, 레드 블랙 트리의 성질을 만족하기 때문에, 부모의 노드가 검정색일 경우, 고려할 필요가 없습니다. (-> 모든 문제는 더블 레드에서 발생합니다.)  // 해당 조건은 Insert Case 1도 포함하는 조건입니다.
	if (pRetNode->up->color == BLACK)
	{
		return;
	}
	
	rbTreeNode<KEY, VALUE>* pUncleNode = _GetUncleNode(pRetNode); // UncleNode Pointer  
	rbTreeNode<KEY, VALUE>* pGrandNode = pRetNode->up->up; // 조부모(왕부모) 노드 --> nullptr일 경우는 고려하지 않아도 됩니다. (Insert Case 1 - 2에서 걸러집니다.)

	// [Insert Case 3] Recoloring - 부모노드와 UncleNode 모두 빨간색일 때, 이를 모두 검정색으로 바꾸고, 조부모노드를 빨간색으로 변경합니다. 
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

	// [Insert Case 4] Restructuring - 부모노드는 빨간색이나, UncleNode는 검은색일 때, 모양에 따라. 작은 회전을 해줌 ( Insert Case 4를 거친 트리는 더블 레드 상태가 되며 규칙에 위반됩니다. )
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
		- 인자로 제공되는 노드의 포인터를 활용해, 해당 노드를 삭제합니다!

		#1. 기존 레드 - 블랙트리 방식과 조금 다른 점은 Copy Value가 아니라, Node 자체를 변경하는 점입니다.
		( 내부에서 Node에 대한 ptr를 활용할 때, 이에 대한 참조를 보장하기 위함.)

		!1. 내부에서 Node에 대한 메모리 회수(delete) 가 일어납니다.

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


/*
	_ChangeForDelete(rbTreeNode<KEY, VALUE>* pInNode);
		- Delete 함수 내부에서 사용되며, 노드를 Delete 한 후에도, Red-Black Tree의 특징을 유지하기 위해 검사 및 처리를 해주는 함수입니다.
	
	#1. 관련 이론은 위키 백과, 레드-블랙 트리를 확인해 주세요! https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC
	
	인자 : Delete할 노드의 NextNode( Successor )의 ChildNode (dir - Right)
	출력 : void
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


/*
	DeleteWithSearch(const KEY& InKey);
	
		- 키릉 인자로 받아, 해당 키에 해당하는 노드를 찾고, 그 노드를 삭제합니다.

		#1. Ptr를 사용하는 삭제 함수 (Delete) 보다 당연히 무겁습니다.

		!1. 내부에서 Node에 대한 메모리 회수(delete) 가 일어납니다.

		!2. 따라서, 외부에서 해당 노드에 포인터를 통한 참조가 있을 경우, nullptr에러가 날 가능성이 큽니다.

	인자 : 제거하려는 노드의 키값.

	출력 : bool값 - 노드 삭제 여부 ( == 해당 키를 가진 노드의 존재 여부 )
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
		트리구조에서 왼쪽 회전을 시도합니다.

		#1. https://en.wikipedia.org/wiki/Tree_rotation

	인자 : 회전의 기준이 되는 노드의 포인터
	출력 : void
*/

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

/*
	_RightRotate(rbTreeNode<KEY, VALUE>* pRetNode)
		트리구조에서 오른쪽 회전을 시도합니다.

	#1. https://en.wikipedia.org/wiki/Tree_rotation

	인자 : 회전의 기준이 되는 노드의 포인터
	출력 : void
*/

template <typename KEY, typename VALUE>
void rbTree<KEY, VALUE>::_RightRotate(rbTreeNode<KEY, VALUE>* pRetNode)
{
	rbTreeNode<KEY, VALUE>* pParentNode = pRetNode->up;
	rbTreeNode<KEY, VALUE>* pLeftChildNode = pRetNode->left;

	// 주석 _LeftRotate 하고 동일합니다..또 쓰기 너무 귀찮어요...

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
		Predecessor를 구하는 함수, 사용되지 않습니다.
	
	인자 : Delete되어, PrevNode를 구해야하는 노드의 포인터
	출력 : Predecessor Node's Pointer
*/

template <typename KEY, typename VALUE>
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetPrevNode(rbTreeNode<KEY, VALUE>* const pInNode)
{
	rbTreeNode<KEY, VALUE>* pRetNode = pInNode;

	// 좌측이 NullNode가 아닐 경우, 
	if (pRetNode->left != pNullNode) {

		// 좌측으로 포인터를 한 번 이동하고 (좌측 서브트리에 진입하고)
		pRetNode = pRetNode->left;

		// 해당 서브트리에서 가장 큰 값 (가장 Right에 있는 노드)를 찾고,
		while (pRetNode->right != pNullNode)
		{
			pRetNode = pRetNode->right;
		}

		// 해당 노드를 리턴합니다.
		return pRetNode;
	}
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
rbTreeNode<KEY, VALUE>*	rbTree<KEY, VALUE>::_GetNextNode(rbTreeNode<KEY, VALUE>* const InNode)
{
	rbTreeNode<KEY, VALUE>* RetNode = InNode;

	// 우측이 NullNode가 아닐 경우, 
	if (RetNode->right != pNullNode) {

		// 우측으로 포인터를 한 번 이동하고 (우측 서브트리에 진입하고)
		RetNode = RetNode->right;

		// 해당 서브트리에서 가장 작은 값 (가장 Left에 있는 노드)를 찾고,
		while (RetNode->left != pNullNode)
		{
			RetNode = RetNode->left;
		}

		// 해당 노드를 리턴합니다.
		return RetNode;
	}
};


/*
	_GetSiblingNode(rbTreeNode<KEY, VALUE>* pInNode);
		- pInNode의 형제 노드의 포인터를 구하는 함수입니다.
	
	인자 : 노드의 포인터
	출력 : 형제 노드의 포인터
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
	//	std::cout << "Error - 형제 노드를 반환하는 함수에서 예외가 발생했습니다. \n";
	//}
}


/*
	_GetUncleNode(rbTreeNode<KEY, VALUE>* pInNode);
		- pInNode의 Uncle 노드의 포인터를 구하는 함수입니다.
	
	인자 : 노드의 포인터
	출력 : 삼촌 노드의 포인터
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
	//		std::cout << "Error - Uncle 노드를 반환하는 함수에서 예외가 발생했습니다. \n";
	//}
}


// ================================== Debug Function

//Debug Function

/*
	!1. 내부에는 재귀함수를 사용하고 있습니다. 트리 높이가 높을 경우, 스택 오버플로우가 발생할 수 있습니다.
		(디버그 용도로만 사용하는 것을 추천드립니다.)
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