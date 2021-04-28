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

typedef struct Node {		// 원형 연결리스트 노드 생성
	int key;				// 리스트의 데이터 필드 key 생성
	struct Node* llink;		// 원형 연결리스트의 왼쪽노드와 연결하는 포인터
	struct Node* rlink;		// 원형 연결리스트의 오른쪽노드와 연결하는 포인터
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);				// 리스트 생성 후 초기화하는 함수
int freeList(listNode* h);					// 리스트 할당을 해제하는 함수
int insertLast(listNode* h, int key);		// 마지막 위치에 노드를 삽입하는 함수
int deleteLast(listNode* h);				// 마지막 위치의 노드를 삭제하는 함수
int insertFirst(listNode* h, int key);		// 첫번째 위치에 노드를 삽입하는 함수
int deleteFirst(listNode* h);				// 첫번째 위치의 노드를 삭제하는 함수
int invertList(listNode* h);				// 노드의 위치를 반전시키는 함수

int insertNode(listNode* h, int key);		// 조건하는 위치에 노드 삽입하는 함수
int deleteNode(listNode* h, int key);		// 원하는 노드의 값을 삭제하는 함수

void printList(listNode* h);				// 노드를 보여주는 함수



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
		printf("\t[-----[이 명 국]  [2017038100]-----]\n");
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


int initialize(listNode** h) {				// 리스트 생성 후 초기화하는 함수

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
int freeList(listNode* h){		// 리스트 할당을 해제하는 함수
    listNode* p = h;          // 노드 p에 헤드 값 first 지정

   listNode* prev = NULL;           // prev라는 노드에 NULL 지정
   while(p != NULL) {               // 노드 P가 NULL이 아닐때까지 반복
      prev = p;                     
      p = p->rlink;
      free(prev);                   // prev 노드에 할당된 메모리 반환
   }
   free(h);           
	return 0;
}



void printList(listNode* h) {	// 노드를 보여주는 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {				// 노드가 없을때 출력
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


	/* print addresses */					//노드가 있을때 출력
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
int insertLast(listNode* h, int key) {					    // 마지막 위치에 노드를 삽입하는 함수

   listNode* node = (listNode*)malloc(sizeof(listNode));   // 신규 노드 지정 후 node의 데이터 공간을 메모리에 할당 받아 node에 저장.
   listNode* lastNode;        							   // 노드 존재시 마지막 노드 정의.
   node -> key = key;         							   // node 필드에 key를 저장
   node ->rlink = NULL;         						   // key 저장 후 아직 가리키는 노드가 없기때문에 NULL 할당	
   if(h  == NULL ){   									   // NULL일 경우
      h -> rlink = node;      							   // h의 rlink가 node를 가리킴
	  h -> llink = node;								   // h의 llink가 node를 가리킴
	  node -> llink = h;								   // node의 llink가 h를 가리킴
	  node -> rlink = h;								   // node의 rlink가 h를 가리킴
      return 1;            // 종료
   }
   else{
	   node -> rlink = h;								   // node의 rlink가 h를 가리킴
	   node-> llink = h->llink;							   // node의 llink가 h의 llink를 가리킴
	   h->llink ->rlink = node;							   // h의 llink가 가리키고 있는 노드의 rlink가 node를 가리킴
	   h->llink = node;									   // h의 llink가 node를 가리킴

	   return 1;
   }
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
   listNode* frontnode;                // 선행노드 선언
   listNode* delLastnode;              // 삭제하고하는 곳을 가리키는 노드 선언
   
   if(h -> rlink == h)
   {   // 삭제할 노드가 없을 경우 종료
   	  freeList(h);
      return 1;
   } 
   else if(h->rlink ->rlink == h){                           // 2개 이상의 노드가 있을 경우
		  free(h);
		  h->rlink = NULL;
		  return 1;
   }
	else{
	  frontnode = h->rlink;               // 삭제할 delLastnode 앞의 frontnode를 첫번째 노드로 설정
	  delLastnode = h -> rlink ->rlink;      // 삭제할 노드를 두번째 노드로 설정
      while(delLastnode -> rlink != h){      // 삭제할 노드가 NULL이 아닐때까지 
         frontnode = delLastnode;         // frontnode와 delLastnode를 뒤로 이동
         delLastnode = delLastnode -> rlink;
      }
      free(delLastnode);                  // 마지막 노드 발견시 마지막 노드 메모리 반환
      frontnode -> rlink = NULL;            // frontnode가 delLastnode에 가리키는 링크 NULL 지정
	  }
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
    listNode* trail;
   if(h -> rlink == NULL)
   {   // 삭제할 노드가 없을 경우 종료
      printf("삭제할 마지막 노드가 없습니다.\n");
      return 0;
   } 

   else if(h -> rlink == NULL){         // h노드의 rlink가 NULL이면
      freeList(h);                      // h노드에 할당된 메모리 제거
      h -> rlink = NULL;                // h노드의 rlink, llink NULL 처리
      h -> llink = NULL;              
      return 1;                     
   }
   else{                 
   trail = h -> rlink;                  // trail을 h노드의 rlink로 지정
   h -> rlink = trail ->rlink;          // h노드의 rlink가 trail의 rlink를 가리킴
   
   }

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    listNode* one;                   // 노드 one, two, three 생성
      listNode* two;
      listNode* three;

      one = h ;                // one 포인터를 첫번째 노드에 설정
      two = NULL;
      three = NULL;

      while (one != NULL){             // one의 값이 NULL이 아닐동안 반복
         three = two;                  // three를 two가 가리키는 노드에 지정
         two = one;                    // two 노드를 one이 가리키는 노드에 지정
         one = one ->rlink;            // one 노드를 다음 노드로 이동
         two -> rlink = three;          // two 노드가 가리키는 rlink를 three로 지정
      }
      h = two;                // h 노드를 two로 변경
	return 0;

}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));	//node라는 리스트 노드 할당
	listNode* find = h ->llink;								
	node->key = key;
	if(h == NULL)
	{
		printf("저장된 데이터가 없습니다.\n");				
		node->rlink = NULL;
		node->llink = NULL;
		return 0;
		
	}else{
		while(find->rlink!=NULL){
			if(find->rlink->key > node->key)
			{
				node->rlink = find->rlink;		//node의 rlink를 find의 rlink로 변경
				find->rlink->llink = node;		//find의 rlink와 link를 node에 지정
				node->llink = find;				//node의 llink를 find에 지정
				find->rlink = node;				//find의 rlink를 node에 지정
				return 0;
			}
			find = find->rlink;					//find의 다음 단계를 탐색
		}
		insertLast(h, key);						//큰 값이 없을시 마지막에 노드 추가
	}
	
	
	return 0;;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
listNode *find = h ;                  // find 노드를 헤더를 가리키는 노드를 가리키게 지정
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


