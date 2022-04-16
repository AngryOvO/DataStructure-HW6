/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */
// 연결리스트의 노드 구조체 선언 구조체 안에는 주소값을 저장할 구조체 포인터가 선언되어있음.
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

// 단일 리스트의 헤드부분을 가리키는 구조체 선언 멤버 변수로는 구조체 포인터 변수가 선언
typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main() // 메인함수 시작
{
	char command;
	int key; // 리스트의 값이 저장되는 변수
	headNode* headnode=NULL; // 헤드노드를 구조체 포인터 변수로 선언

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("--------------[201803805]------[정하용]-------------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 노드 생성 동적할당
	node->key = key; // 노드의 key 부분에 입력받은 key 값 할당

	node->link = h->first; // 생성된 노드가 가리키는 주소는 헤드가 가리키는 주소
	h->first = node; // 헤드의 위치를 새로 생성된 노드로 이동

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	//노드 생성부분
	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	newnode->link = NULL;

	if(h->first == NULL) // 헤드가 아무것도 가리키지 않는다면 == 리스트가 비어있다면
	{
		h->first = newnode; // 헤드는 새로 생성한 노드를 가리킴
		return 0;
	}
	// 리스트가 비어있지 않다면
	listNode* p = NULL; //리스트를 검색할 구조체포인터 p생성
	listNode* tail = NULL; // 항상 p보다 한 노드 뒤에있을 구조체 포인터 tail 생성
	// 초기에 p와 tail은 헤드와 같은 노드를 가리킴
	p = h->first; 
	tail = h->first;

	while(p != NULL) //p가 NULL일 때까지 반복
	{
		if(p->key >= key) // 만약 입력받은 key 값이 p가 가리키는 key값보다 작다면
		{
			if(p == h->first) // 리스트에 노드가 한개 있을 경우
			{
				// 리스트의 처음부분에 노드를 위치시킴
				h->first = newnode; 
				newnode->link = p;
			}
			else // 리스트에 노드가 여러개 있을 경우
			{
				newnode->link = p; // 새 노드는 p를 가리킴
				tail->link = newnode; //p의 이전 노드는 새 노드를 가리킴
			}
			return 0;
		}
		tail = p; // tail을 p의 위치로 이동
		p = p->link; // p를 다음 노드의 위치로 이동
	}
	//입력받은 key값보다 큰 값의 노드가 없을 경우
	tail->link = newnode; // 리스트의 가장 마지막 노드가 새 노드를 가리킴 
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* newnode = (listNode*)malloc(sizeof(listNode));
	newnode->key = key;
	newnode->link = NULL;

	if(h->first == NULL)
	{
		h->first = newnode;
		return 0;
	}
	
	listNode* p = NULL;
	p = h->first;

	while(p->link != NULL)
	{
		p = p->link;
	}
	p->link = newnode;

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL)
	{
		printf("삭제할 리스트가 없습니다.\n");
		return 0;
	}
	
	
	listNode* p = NULL;

	p = h->first;
	h->first = p->link;
	free(p);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if(h->first == NULL)
	{
		printf("삭제할 리스트가 없습니다.\n");
		return 0;
	}

	listNode* p = NULL;
	listNode* tail = NULL;
	p = h->first;
	tail = h->first;

	while(p != NULL)
	{
		if(p->key == key)
		{
			if(p == h->first)
			{
				h->first = p->link;
				free(p);
				return 0;
			}
			
			tail->link = p->link;
			free(p);
			return 0;
		}
		
		tail = p;
		p = p->link;

	}

	printf("cannot find node for key.\n");	
	return 0;
		
	

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if(h->first == NULL)
	{
		printf("삭제할 리스트가 없습니다.\n");
		return 0;
	}

	listNode *p = h->first;
	listNode *tail = NULL;

	if(p->link == NULL)
	{
		h->first == NULL;
		free(p);
		return 0;
	}

	while(p->link != NULL)
	{
		tail = p;
		p = p->link;
	}
	
	tail->link = NULL;
	free(p);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL)
	{
		printf("역순할 리스트가 없습니다.\n");
		return 0;
	}

	listNode *a = h->first;
	listNode *b = h->first;
	listNode *c = h->first;

	while(c != NULL)
	{
	
		a = b;
		b = c;
		c = c->link;
		b->link = a;
	}

	h->first->link = NULL;
	h->first = b;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

