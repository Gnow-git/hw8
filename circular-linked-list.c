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
/* �ʿ��� ������� �߰� */

typedef struct Node {		// ���� ���Ḯ��Ʈ ��� ����
	int key;				// ����Ʈ�� ������ �ʵ� key ����
	struct Node* llink;		// ���� ���Ḯ��Ʈ�� ���ʳ��� �����ϴ� ������
	struct Node* rlink;		// ���� ���Ḯ��Ʈ�� �����ʳ��� �����ϴ� ������
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);				// ����Ʈ ���� �� �ʱ�ȭ�ϴ� �Լ�
int freeList(listNode* h);					// ����Ʈ �Ҵ��� �����ϴ� �Լ�
int insertLast(listNode* h, int key);		// ������ ��ġ�� ��带 �����ϴ� �Լ�
int deleteLast(listNode* h);				// ������ ��ġ�� ��带 �����ϴ� �Լ�
int insertFirst(listNode* h, int key);		// ù��° ��ġ�� ��带 �����ϴ� �Լ�
int deleteFirst(listNode* h);				// ù��° ��ġ�� ��带 �����ϴ� �Լ�
int invertList(listNode* h);				// ����� ��ġ�� ������Ű�� �Լ�

int insertNode(listNode* h, int key);		// �����ϴ� ��ġ�� ��� �����ϴ� �Լ�
int deleteNode(listNode* h, int key);		// ���ϴ� ����� ���� �����ϴ� �Լ�

void printList(listNode* h);				// ��带 �����ִ� �Լ�



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
		printf("\t[-----[�� �� ��]  [2017038100]-----]\n");
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


int initialize(listNode** h) {				// ����Ʈ ���� �� �ʱ�ȭ�ϴ� �Լ�

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){		// ����Ʈ �Ҵ��� �����ϴ� �Լ�
    listNode* p = h;          // ��� p�� ��� �� first ����

   listNode* prev = NULL;           // prev��� ��忡 NULL ����
   while(p != NULL) {               // ��� P�� NULL�� �ƴҶ����� �ݺ�
      prev = p;                     
      p = p->rlink;
      free(prev);                   // prev ��忡 �Ҵ�� �޸� ��ȯ
   }
   free(h);           
	return 0;
}



void printList(listNode* h) {	// ��带 �����ִ� �Լ�
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {				// ��尡 ������ ���
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


	/* print addresses */					//��尡 ������ ���
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {					    // ������ ��ġ�� ��带 �����ϴ� �Լ�

   listNode* node = (listNode*)malloc(sizeof(listNode));   // �ű� ��� ���� �� node�� ������ ������ �޸𸮿� �Ҵ� �޾� node�� ����.
   listNode* lastNode;        							   // ��� ����� ������ ��� ����.
   node -> key = key;         							   // node �ʵ忡 key�� ����
   node ->rlink = NULL;         						   // key ���� �� ���� ����Ű�� ��尡 ���⶧���� NULL �Ҵ�	
   if(h  == NULL ){   									   // NULL�� ���
      h -> rlink = node;      							   // h�� rlink�� node�� ����Ŵ
	  h -> llink = node;								   // h�� llink�� node�� ����Ŵ
	  node -> llink = h;								   // node�� llink�� h�� ����Ŵ
	  node -> rlink = h;								   // node�� rlink�� h�� ����Ŵ
      return 1;            // ����
   }
   else{
	   node -> rlink = h;								   // node�� rlink�� h�� ����Ŵ
	   node-> llink = h->llink;							   // node�� llink�� h�� llink�� ����Ŵ
	   h->llink ->rlink = node;							   // h�� llink�� ����Ű�� �ִ� ����� rlink�� node�� ����Ŵ
	   h->llink = node;									   // h�� llink�� node�� ����Ŵ

	   return 1;
   }
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
   listNode* frontnode;                // ������ ����
   listNode* delLastnode;              // �����ϰ��ϴ� ���� ����Ű�� ��� ����
   
   if(h -> rlink == h)
   {   // ������ ��尡 ���� ��� ����
   	  freeList(h);
      return 1;
   } 
   else if(h->rlink ->rlink == h){                           // 2�� �̻��� ��尡 ���� ���
		  free(h);
		  h->rlink = NULL;
		  return 1;
   }
	else{
	  frontnode = h->rlink;               // ������ delLastnode ���� frontnode�� ù��° ���� ����
	  delLastnode = h -> rlink ->rlink;      // ������ ��带 �ι�° ���� ����
      while(delLastnode -> rlink != h){      // ������ ��尡 NULL�� �ƴҶ����� 
         frontnode = delLastnode;         // frontnode�� delLastnode�� �ڷ� �̵�
         delLastnode = delLastnode -> rlink;
      }
      free(delLastnode);                  // ������ ��� �߽߰� ������ ��� �޸� ��ȯ
      frontnode -> rlink = NULL;            // frontnode�� delLastnode�� ����Ű�� ��ũ NULL ����
	  }
	  return 1;
   }	


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {             // ù��° ��ġ�� ��带 �����ϴ� �Լ�
    
	listNode* newNode, *temp;                       // newNode��� ù��° ���� temp��� �ӽ� ��ȸ ������ ����
    newNode = (listNode*)malloc(sizeof(listNode));  // ù��° ��ġ�� �����ϰ� �� newNode �Ҵ�
    newNode -> key = key;                           // newNode�� �������ʵ� ���� key�� ����
    if(h -> rlink == NULL){                         // ���� �������� ������ ��ũ�� NULL �̶��(�Էµ� ��尡 ���ٸ�)
        h -> rlink == newNode;                      // �������� rlink�� newNode�� ����Ű���ϰ�
        newNode -> rlink = newNode;                 // newNode�� rlink�� �ڱ� �ڽ��� ����Ű���Ͽ� newNode�� ù��° ������� ������ ��尡 �ǵ��� �����Ѵ�.
    }
    else{                                           // �̹� �Էµ� ��尡 �ִٸ�
        temp = h -> rlink;                          // ù��° ����� rlink�� temp�� ����
        while(temp -> rlink != h ->rlink)           // temp�� rlink�� h�� rlink�� ���� �ʴٸ�
            temp = temp->rlink;                     // temp�� temp�� rlink���� �̵� ��Ų��.
        newNode -> rlink = temp -> rlink;           // temp�� ����Ű�� ����� rlink�� temp�� rlink�� ����Ų��. 
        temp -> rlink = newNode;                    // temp�� ����Ű�� ������ ����� rlink�� newNode�� ����Ų��.(���� ����)
        h ->rlink = newNode;                        // newNode�� ��� ��尡 �����Ѽ� newNode�� ù��° ��尡 �ǵ��� �����Ѵ�.
        h->llink = newNode;                         // �������� ���� ��ũ�� �� ������ ��忡 ����.
        newNode ->llink = h;
    
    }
	return 1;
	
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
    listNode* trail;
   if(h -> rlink == NULL)
   {   // ������ ��尡 ���� ��� ����
      printf("������ ������ ��尡 �����ϴ�.\n");
      return 0;
   } 

   else if(h -> rlink == NULL){         // h����� rlink�� NULL�̸�
      freeList(h);                      // h��忡 �Ҵ�� �޸� ����
      h -> rlink = NULL;                // h����� rlink, llink NULL ó��
      h -> llink = NULL;              
      return 1;                     
   }
   else{                 
   trail = h -> rlink;                  // trail�� h����� rlink�� ����
   h -> rlink = trail ->rlink;          // h����� rlink�� trail�� rlink�� ����Ŵ
   
   }

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
    listNode* one;                   // ��� one, two, three ����
      listNode* two;
      listNode* three;

      one = h ;                // one �����͸� ù��° ��忡 ����
      two = NULL;
      three = NULL;

      while (one != NULL){             // one�� ���� NULL�� �ƴҵ��� �ݺ�
         three = two;                  // three�� two�� ����Ű�� ��忡 ����
         two = one;                    // two ��带 one�� ����Ű�� ��忡 ����
         one = one ->rlink;            // one ��带 ���� ���� �̵�
         two -> rlink = three;          // two ��尡 ����Ű�� rlink�� three�� ����
      }
      h = two;                // h ��带 two�� ����
	return 0;

}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� 
 **/
int insertNode(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));	//node��� ����Ʈ ��� �Ҵ�
	listNode* find = h ->llink;								
	node->key = key;
	if(h == NULL)
	{
		printf("����� �����Ͱ� �����ϴ�.\n");				
		node->rlink = NULL;
		node->llink = NULL;
		return 0;
		
	}else{
		while(find->rlink!=NULL){
			if(find->rlink->key > node->key)
			{
				node->rlink = find->rlink;		//node�� rlink�� find�� rlink�� ����
				find->rlink->llink = node;		//find�� rlink�� link�� node�� ����
				node->llink = find;				//node�� llink�� find�� ����
				find->rlink = node;				//find�� rlink�� node�� ����
				return 0;
			}
			find = find->rlink;					//find�� ���� �ܰ踦 Ž��
		}
		insertLast(h, key);						//ū ���� ������ �������� ��� �߰�
	}
	
	
	return 0;;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
listNode *find = h ;                  // find ��带 ����� ����Ű�� ��带 ����Ű�� ����
  listNode *frontfind = NULL;                          // frontfind ��� �����ϰ� NULL�� �ʱ�ȭ
  if(h->rlink == NULL)                    // ����� rlink���� Ž�� ����
  {
     printf("����� �����Ͱ� �����ϴ� !\n");
     return 0;
  }
  else{
     while(find->rlink!=NULL){                    // find�� rlink�� NULL�� �ɶ����� ����.
        if (find-> rlink-> key == key)            // �Է��� key ���� ���� ����� ���� �ִٸ�
        {
           frontfind = find ->rlink;              // find�� rlink�� frontfind�� ����Ų��.
           find -> rlink = find ->rlink->rlink;     // �����ϰ����ϴ� ����� �翷�� �̾��ش�.
           free(frontfind);                      // ��� ��带 ������Ų��.
           return 0;
        }
        find = find -> rlink;                      // ã�� ���� ������ ���� �����ͷ� �Ѿ��.
     }
     if (find == NULL) printf("ã�� �����Ͱ� �����ϴ�\n");
  }
  return 0;
}


