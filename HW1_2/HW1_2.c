//�ܼ����Ḯ��Ʈ
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;
// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert_next(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	p->data = value; //(2)
	p->link = pre->link; //(3)
	pre->link = p; //(4)
	return head; //(5)
}
ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	p->data = value; // (2)
	p->link = head; // ��� �������� ���� ���� //(3)
	head = p; // ��� ������ ���� //(4)
	return head; // ����� ��� ������ ��ȯ
}
ListNode* insert_last(ListNode* head, int value)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	p->data = value;
	p->link = NULL;
	// (2)
	if (head == NULL) // ���� ����Ʈ�̸�
		head = p;
	else {
		while (temp->link != 0)
			temp = temp->link;
		temp->link = p;
	}
	return head; // ����� ��� ������ ��ȯ
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
ListNode* delete_next(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link; // (2)
	free(removed); // (3)
	return head; // (4)
}
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) error("������ �׸��� ����");
	removed = head; // (1)
	head = removed->link; // (2)
	free(removed); // (3)

	return head; // (4)
}
ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	ListNode* prevTemp;
	ListNode* removed;
	if (head == NULL)
		error("������ �׸��� ����");
	if (temp->link == NULL) {	// �ϳ��� ���
		removed = temp->link;
		temp->link = NULL;
		free(removed);
		return NULL;
	}
	else {	 // �� �̻��� ���
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
		free(removed);
		return head;	// �״��
	}
}
void print_list(ListNode* head)
{
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}
ListNode* search(ListNode* head, int x)
{
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->data == x)
			return p;	// Ž�� ����
		p = p->link;
	}
	return NULL;	// Ž�� ������ ��� NULL ��ȯ
}
ListNode* concat(ListNode* head1, ListNode* head2)
{
	ListNode* p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}
ListNode* reverse(ListNode* head)
{
	// ��ȸ �����ͷ� p, q, r�� ���
	ListNode* p, * q, * r;
	p = head;	// p�� �������� ���� ����Ʈ
	q = NULL;	// q�� �������� ���� ���
	while (p != NULL) {
		r = q;	// r�� �������� �� ����Ʈ. r�� q, q�� p�� ���ʷ� ���󰣴�.
		q = p;
		p = p->link;
		q->link = r; // q�� ��ũ ������ �ٲ۴�. 
	}
	return q;	// q�� �������� �� ����Ʈ�� ��� ������
}

int is_in_list(ListNode* head, element item)
{
	ListNode* p = head;

	while (p != NULL)
	{
		if (p->data == item)
			return 1;
		p = p->link;
	}

	return 0;
}
int get_length(ListNode* head)	// �ܼ� ���� ����Ʈ�� �����ϴ� ����� ���� ��ȯ
{
	ListNode* p = head;
	int cnt = 0;

	while (p != NULL) {
		cnt++;
		p = p->link;
	}
	return cnt;
}
int get_total(ListNode* head)	// �ܼ����Ḯ��Ʈ�� ��� ������ ���� ���� ���� ��ȯ
{
	ListNode* p = head;
	int sum = 0;

	while (p != NULL) {
		sum += p->data;
		p = p->link;
	}
	return sum;
}
element get_entry(ListNode* head, int pos)	// pos ��ġ(0 �� ù ��° ���)�� �ִ� ����� data �� ��ȯ
{
	ListNode* p = head;
	int i;

	for (i = 0; p != NULL && i < pos; i++)
		p = p->link;

	return p->data;
}
ListNode* delete_by_key(ListNode* head, int key)	//����Ʈ���� key���� �˻��Ͽ� �׸� ����
{
	ListNode* removed = NULL;
	ListNode* temp = NULL;

	if (head->data == key)
	{
		removed = head;
		head = removed->link;
		free(removed);
	}
	else
	{
		while (removed != NULL)
		{
			if (temp->link->data == key)
			{
				removed = temp->link;
				temp->link = removed->link;
				free(removed);
			}
		}
	}
	return head;
}
ListNode* insert_pos(ListNode* head, int pos, element value)	//pos ��ġ�� value �� ���� ��带 �߰�
{
	/*
	// ���#1
	ListNode *p;
	int index = 0;

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));

	p = head;
	while(index != pos-1)
	{
		index++;
		p = p->link;
	}*/

	// ���#2
	ListNode* temp = head;
	int i;

	if (get_length(head) - 1 < pos) {
		error("�߸���pos");
		return head;
	}
	if (pos == 0)
	{
		head = insert_first(head, value);
	}
	else
	{
		for (i = 0; i < pos - 1; i++)
			temp = temp->link;
		head = insert_next(head, temp, value);
	}

	/*
	//����
	int i;
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	ListNode *temp = head;

	p->data = value;

	for(i = 0; i < pos-1; i++)
		temp = temp->link;

	p->link = temp->link;
	temp->link = p;

	return head;
	*/
}
ListNode* delete_pos(ListNode* head, int pos)// pos ��ġ�� ��带 ���� 
{
	// #1
	ListNode* temp = head;
	ListNode* prevTemp;
	ListNode* removed;
	int index = 0;

	if (head == NULL)
		error("������ �׸��� ����");
	if (temp->link == NULL)//�ϳ��� ���
	{
		removed = temp->link;
		temp->link = NULL;
		free(removed);

		return NULL;
	}
	else
	{
		while (index != pos)
		{
			index++;
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
		free(removed);

		return head;
	}

	/*
	// #2
	ListNode *removed = head;
	ListNode *temp = head;
	int i;

	if(pos-1 == 0)
		temp = head;
	else
	{
		for(i = 0; i < pos-1; i++)
			temp = temp->link;
	}
	removed = temp->link;
	temp->link = removed->link;
	free(removed);

	return head;
	*/

	/*
	//#3
	int i;
	ListNode *temp = head;

	if(get_length(head) -1 <pos) {
		error("�߸��� pos");
		return head;
	}
	if(pos == 0) {
		head = delete_first(head);
	}
	else
	{
		for(i = 0; i < pos-1; i++)
			temp = temp->link;
		head = delete_next(head, temp);
	}
	return head;
	*/
}

int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3;
	//list1 = 30->20->10->�� �����. �̶� 10, 20, 30�� ������ ��带 �����Ѵ�.
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	// list1�� ���
	printf("list1 = ");
	print_list(list1);
	//list1�� �� �� ��带 �����Ѵ� ��, list1 = 20->10->
	list1 = delete_first(list1);
	// list1�� ���
	printf("list1 = ");
	print_list(list1);
	//list2 = 11->22->33->44->�� �����. �̶� 11, 22, 33, 44�� ������ ��带 �����Ѵ�.
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	// list2�� ���
	printf("list2 = ");
	print_list(list2);
	// list2�� �� �� ��带 �����Ѵ�. ��, list2 = 11->22->33->
	list2 = delete_last(list2);
	// list2�� ���
	printf("list2 = ");
	print_list(list2);
	//list2�� �������� �ٲ� ����Ʈ�� list3�� ����Ű�� �Ѵ�. list3 = 33->22->11->�� �����.
	list3 = reverse(list2);

	//list3�� ����Ѵ�.
	printf("list3 = ");
	print_list(list3);
	//list1 = 20->10->33->22->11->�� �����. ��, list1�� list3�� ���ļ� list1�� ����Ű�� �Ѵ�.
	list1 = concat(list1, list3);
	//list1�� ����Ѵ�.
	printf("list1 = ");
	print_list(list1);

	//(A) ����: ���⼭���ʹ� list1�� ����Ͽ� �Լ����� �׽�Ʈ����
	printf("%d\n", is_in_list(list1, 15)); //0
	printf("%d\n", is_in_list(list1, 10)); //1
	printf("list1�� ����� ����: %d\n", get_length(list1));
	printf("list1�� ��� �������� ��: %d\n", get_total(list1));
	printf("list1�� 3��° ������: %d\n", get_entry(list1, 3));//0���� ����, 22

	printf("list1���� 33����: ");
	list1 = delete_by_key(list1, 2);
	print_list(list1);

	printf("\n3��°�� 100�߰�: ");//0���� ����
	list1 = insert_pos(list1, 3, 100);
	print_list(list1);

	printf("\n3��° ��� ����: ");
	delete_pos(list1, 3);
	print_list(list1);
}