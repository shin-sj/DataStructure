//원형연결리스트 ADT
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);

	if (p->link != head)
		printf("%d->", p->data); // 마지막 노드 출력
	printf("\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
	}
	return head;	// 변경된 헤드 포인터를 반환한다. 
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
		head = node;		// (3)
	}
	return head;	// 변경된 헤드 포인터를 반환한다. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}

	else if (head == head->link) {  // 즉 하나의 노드가 남았을때 
		temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;

}

ListNode* delete_last(ListNode* head)
{
	ListNode* removed;
	ListNode* temp;

	if (head == NULL)
		printf("리스트가 비어있어 삭제를 못함");
	else {
		removed = head;
		temp = head->link;
		while (temp->link != head)
			temp = temp->link;
		temp->link = head->link;
		head = temp;
		free(removed);
	}
	return head;
}

ListNode* search(ListNode* head, element x)
{
	ListNode* p;
	p = head->link;

	do {
		if (p->data == x)
			return p; //탐색성공

		p = p->link;
	} while (p != head->link);

	return NULL;
}
//리스트의 길이를 반환
int get_size(ListNode* head)
{
	ListNode* p = head;
	int cnt = 0;

	while (p->link != head) {
		cnt++;
		p = p->link;
	}

	return cnt;
}
// 원형 연결 리스트 테스트 프로그램
int main(void)
{
	ListNode* head = NULL;
	ListNode* p;

	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);

	head = insert_last(head, 30);
	print_list(head);
	head = insert_last(head, 40);
	print_list(head);
	head = insert_first(head, 10);
	print_list(head);

	head = delete_first(head);
	print_list(head); //20->30->40

	printf("TEST\n");
	head = delete_last(head);
	print_list(head); //20->30

	p = search(head, 203);
	printf("%d\n", p->data);

	printf("%d\n", get_size(head)); //1

	return 0;
}

