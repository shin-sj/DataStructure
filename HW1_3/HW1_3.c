#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { // ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;
void display(ListNode* head)
{
	ListNode* p;
	printf("< ");
	for (p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(">\n");
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
int get_total(ListNode* head)// �ܼ����Ḯ��Ʈ�� ��� ������ ���� ���� ���� ��ȯ
{
	ListNode* p = head;
	int sum = 0;

	while (p != NULL) {
		sum += p->data;
		p = p->link;
	}
	return sum;
}
void* delete_by_key(ListNode* head, int key) //����Ʈ���� key���� �˻��Ͽ� �׸� ����
{

	ListNode* removed = head;
	ListNode* pre = NULL;

	if (!is_in_list(head, key)) {
		printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�.\n", key);
		return;
	}

	while (removed != NULL && removed->data != key) {
		pre = removed;
		removed = pre->link;
	}

	if (removed->data == NULL) {
		printf("�������� �������.\n");
		return;
	}
	else {
		pre->link = removed->link;
		free(removed);
		return;
	}
}
void add_item(ListNode** phead, int new_item)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (get_total(*phead) + new_item > 100) {
		printf("�ִ빫��<100kg> �ʰ��� ������ %d�� �߰��Ҽ� ����\n", new_item);
	}
	else {//�������߰�
		p->data = new_item;
		p->link = *phead;
		*phead = p;
	}
}
int main(void)
{
	ListNode* list = NULL;
	char answer;
	int num;
	int check = 0;

	while (check == 0) {
		fflush(stdin);
		printf("enter a<dd>, d<elete>, or q<uit>: ");
		scanf("%c", &answer);
		fflush(stdin);
		switch (answer) {
		case 'a':
			printf("enter the weight of the item: ");
			scanf("%d", &num);
			add_item(&list, num);
			display(list);
			break;
		case 'd':
			printf("enter the weight of the item: ");
			scanf("%d", &num);
			delete_by_key(list, num);
			display(list);
			break;
		case 'q':
			check = 1;
			break;
		default:
			printf("�ٽ� �Է��ϼ���\n");
			break;
		}
	}
}
