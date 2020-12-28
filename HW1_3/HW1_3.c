#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { // 노드 타입
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
int get_total(ListNode* head)// 단순연결리스트의 모든 데이터 값을 더한 합을 반환
{
	ListNode* p = head;
	int sum = 0;

	while (p != NULL) {
		sum += p->data;
		p = p->link;
	}
	return sum;
}
void* delete_by_key(ListNode* head, int key) //리스트에서 key값을 검색하여 그를 삭제
{

	ListNode* removed = head;
	ListNode* pre = NULL;

	if (!is_in_list(head, key)) {
		printf("아이템 %d는 보유하고 있지 않습니다.\n", key);
		return;
	}

	while (removed != NULL && removed->data != key) {
		pre = removed;
		removed = pre->link;
	}

	if (removed->data == NULL) {
		printf("아이템이 비어있음.\n");
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
		printf("최대무게<100kg> 초과로 아이템 %d를 추가할수 없음\n", new_item);
	}
	else {//아이템추가
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
			printf("다시 입력하세요\n");
			break;
		}
	}
}
