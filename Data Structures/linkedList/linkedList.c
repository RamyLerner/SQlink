#include<stdio.h>
#include<stdlib.h>
#define N 5

struct Node{
	int num;
	struct Node* next;
};

typedef struct Node Node;

Node* createNode(num){
	Node* nd= (Node*)malloc(sizeof(Node));
	if (!nd)
		return NULL;
	nd->num = num;
	nd->next = NULL;
	return nd;
}

Node* createList(){
	return NULL;
}

void addNode (Node** list, int n){
	Node* nd = createNode(n);
	Node* first = *list;
	if (*list == NULL){
		*list = nd;
		return;
	}
	while ((*list)->next != NULL)
		*list = (*list)->next;
	(*list)->next = nd;
	*list = first;
}

void printList (Node* list){
	while (list != NULL){
		printf("%d ", list->num);
		list = list->next;
	}
	printf("NULL\n");
}

void destroyNode (Node* nd){
	free(nd);
}

void destroyList (Node* list){
	Node* nextNd;
	while(list != NULL){
		nextNd = list->next;
		free(list);
		list = nextNd;
	}
}

void flipList (Node** list){
	Node *nd2, *nd3;
	if (*list==NULL || (*list)->next==NULL)
		return;
	nd2 = (*list)->next;
	nd3 = nd2->next;
	(*list)->next = NULL;
	while (nd2 != NULL){
		nd2->next = *list;
		(*list) = nd2;
		nd2 = nd3;
		if (nd3!=NULL)
			nd3 = nd3->next;
	}
}

Node* findMiddle(Node* list){
	Node *i1 = list, *i2 = list;
	while (i2 != NULL && i2->next != NULL){
		i2 = i2->next->next;
		i1 = i1->next;
	}
	return i1;
}

int isLoop (Node* list){
	Node *i1 = list, *i2 = list;
	while (i2 != NULL && i2->next != NULL){
		i2 = i2->next->next;
		i1 = i1->next;
		if (i1 == i2)
			return 1;
	}
	return 0;
}

void listCat (Node** l1, Node* l2){
	Node* temp = *l1;
	if (*l1 == NULL){
		*l1 = l2;
		return;
	}
	if (l2 == NULL) return;
	while (temp->next != NULL) 
		temp = temp->next;
	
	temp->next = l2;
}

int listSize (Node* list){
	int size = 0;
	while (list != NULL){
		size++;
		list = list->next;
	}
	return size;
}

Node* findCommon(Node* l1, Node* l2){
	int size1, size2, i;
	Node *longer, *shorter;
	size1 = listSize(l1);
	size2 = listSize(l2);
	longer = (size1>size2) ? l1 : l2;
	shorter = (longer==l1) ? l2 : l1;

	for (i=0; i<abs(size1 - size2); i++)
		longer = longer->next;
	while (longer != NULL){
		if (longer == shorter)
			return longer;
		longer = longer->next;
		shorter = shorter->next;
	}
	return longer;
}



int main(){
	int i,elem, input;
	Node *list, *middle, *second, *third;
	list = createList();
	printf("list created\n");
	while (input != -1 && input != 6){
		printf("type 1 to insert\ntype 2 to print\ntype 3 to flip\ntype 4 for fineMiddle()\ntype 5 for isLoop()\ntype 6 for findCommon()\ntype -1 to exit\n");
		scanf("%d", &input);
		switch (input){
			case 1: printf("enter element to insert at the end\n");
				scanf("%d", &elem);
				addNode(&list, elem);
				break;
			case 2: printList(list);
				break;
			case 3: flipList(&list);
				break;
			case 4: middle = findMiddle(list);
				if (middle != NULL)
					printf("middle: %d\n", middle->num);
				else
					printf("empty\n");
				break;
			case 5: printf("loop: %d\n",isLoop(list));
				break;
			case 6:
				srand(time(NULL));
				second = createList();
				third = createList();
				for (i=0; i<5; i++){
					addNode(&second, rand() % 100);
					addNode(&third, rand() % 100);
				}
				listCat(&list, third);
				listCat(&second, third);
				printf("two lists:\n");
				printList(list);
				printList(second);
				middle = findCommon(list, second);
				printf("lists meet at: %d\n", middle->num);
				destroyList(second);
				break;
			case -1: break;
			default: printf("invalid input\n");
		}
	}

	
	destroyList(list);
	
	
	return 0;
}