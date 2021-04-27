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

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {


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


	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� 
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
listNode *find = h -> rlink;                  // find ��带 ����� rlink�� ����Ű�� ��带 ����Ű�� ����
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


