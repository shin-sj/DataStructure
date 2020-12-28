//�������Ḯ��Ʈ ADT
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ����Ʈ�� �׸� ���
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
		printf("%d->", p->data); // ������ ��� ���
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
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
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
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}

	else if (head == head->link) {  // �� �ϳ��� ��尡 �������� 
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
		printf("����Ʈ�� ����־� ������ ����");
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
			return p; //Ž������

		p = p->link;
	} while (p != head->link);

	return NULL;
}
//����Ʈ�� ���̸� ��ȯ
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
// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
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

