/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {             // 첫번째 위치에 노드를 삽입하는 함수
    listNode* newNode, *temp;                       // newNode라는 첫번째 노드와 temp라는 임시 순회 포인터 지정
    newNode = (listNode*)malloc(sizeof(listNode));  // 첫번째 위치에 삽입하게 될 newNode 할당
    newNode -> key = key;                           // newNode의 데이터필드 값을 key로 지정
    if(h -> rlink == NULL){                         // 만약 헤더노드의 오른쪽 링크가 NULL 이라면(입력된 노드가 없다면)
        h -> rlink == newNode;                      // 헤더노드의 rlink가 newNode를 가리키게하고
        newNode -> rlink = newNode;                 // newNode의 rlink는 자기 자신을 가리키게하여 newNode가 첫번째 노드이자 마지막 노드가 되도록 설정한다.
    }
    else{                                           // 이미 입력된 노드가 있다면
        temp = h -> rlink;                          // 첫번째 노드의 rlink를 temp에 설정
        while(temp -> rlink != h ->rlink)           // temp의 rlink와 h의 rlink가 같지 않다면
            temp = temp->rlink;                     // temp를 temp의 rlink따라 이동 시킨다.
        newNode -> rlink = temp -> rlink;           // temp가 가리키는 노드의 rlink로 temp의 rlink를 가리킨다. 
        temp -> rlink = newNode;                    // temp가 가리키는 마지막 노드의 rlink는 newNode를 가리킨다.(원형 연결)
        h ->rlink = newNode;                        // newNode를 헤더 노드가 가리켜서 newNode를 첫번째 노드가 되도록 연결한다.
        h->llink = newNode;                         // 헤더노드의 왼쪽 링크를 맨 오른쪽 노드에 연결.
        newNode ->llink = h;
    
    }
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
listNode *find = h -> rlink;                  // find 노드를 헤더의 rlink가 가리키는 노드를 가리키게 지정
  listNode *frontfind = NULL;                          // frontfind 노드 지정하고 NULL로 초기화
  if(h->rlink == NULL)                    // 헤더의 rlink부터 탐색 시작
  {
     printf("저장된 데이터가 없습니다 !\n");
     return 0;
  }
  else{
     while(find->rlink!=NULL){                    // find의 rlink가 NULL이 될때까지 돈다.
        if (find-> rlink-> key == key)            // 입력한 key 값과 같은 노드의 값이 있다면
        {
           frontfind = find ->rlink;              // find의 rlink를 frontfind로 가리킨다.
           find -> rlink = find ->rlink->rlink;     // 삭제하고자하는 노드의 양옆을 이어준다.
           free(frontfind);                      // 대상 노드를 삭제시킨다.
           return 0;
        }
        find = find -> rlink;                      // 찾는 값이 없으면 다음 데이터로 넘어간다.
     }
     if (find == NULL) printf("찾는 데이터가 없습니다\n");
  }
  return 0;
}


