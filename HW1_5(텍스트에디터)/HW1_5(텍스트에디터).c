#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 100
typedef struct {
	char line[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;
element get_entry(ListNode* head, int pos)// pos 위치(0 이 첫 번째 노드)에 있는 노드의 data 를 반환
{
	ListNode* p = head;
	int i;

	for (i = 0; p != NULL && i < pos; i++)
		p = p->link;

	return p->data;
}
int get_length(ListNode* head)// 단순 연결 리스트에 존재하는 노드의 수를 반환
{
	ListNode* p = head;
	int cnt = 0;

	while (p != NULL) {
		cnt++;
		p = p->link;
	}
	return cnt;
}
void display_te(ListNode* head) // text editor 를 위해 변경 // 2)
{
	int c = get_length(head);
	int i;

	printf("-------text edited-------\n");
	for (i = 0; i < c; i++) {
		printf("(%d) %s", i + 1, get_entry(head, i).line);
	}
}

ListNode* insert_last(ListNode* head, element value)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	p->data = value;
	p->link = NULL;
	// (2)
	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != 0)
			temp = temp->link;
		temp->link = p;
	}
	return head; // 변경된 헤드 포인터 반환
}
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	p->data = value; // (2)
	p->link = head; // 헤드 포인터의 값을 복사 //(3)
	head = p; // 헤드 포인터 변경 //(4)
	return head; // 변경된 헤드 포인터 반환
}
ListNode* insert_next(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)
	p->data = value; //(2)
	p->link = pre->link; //(3)
	pre->link = p; //(4)
	return head; //(5)
}
ListNode* insert_pos(ListNode* head, int pos, element value) //pos 위치에 value 를 갖는 노드를 추가
{
	ListNode* temp = head;
	int i;

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
}
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
	//if (head == NULL) error("삭제할 항목이 없음");
	removed = head; // (1)
	head = removed->link; // (2)
	free(removed); // (3)

	return head; // (4)
}
ListNode* delete_pos(ListNode* head, int pos)// pos 위치의 노드를 삭제 
{
	int i;
	ListNode* temp = head;

	if (pos == 0) {
		head = delete_first(head);
	}
	else
	{
		for (i = 0; i < pos - 1; i++)
			temp = temp->link;
		head = delete_next(head, temp);
	}
	return head;

}

char askChoice(void) {
	char choice;
	printf("------------------------------\n");
	printf("a: 텍스트 끝에 라인 추가\n");
	printf("i: 라인 번호로 라인 추가\n");
	printf("d: 라인 번호로 라인 삭제\n");
	printf("v: 라인 번호로 해당 라인 출력\n");
	printf("p: 전체 텍스트 출력\n");
	printf("q: 끝\n");
	printf("메뉴 선택:");
	scanf("%c", &choice);
	return choice;
}
int main(void) // 3)
{
	ListNode* list = NULL;
	char choice;
	int lineNb;
	element newElement;

	while ((choice = askChoice()) != 'q') {
		switch (choice) {
		case 'a':
			printf("텍스트 끝에 삽입할 라인: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
			list = insert_last(list, newElement);
			display_te(list);
			break;
		case 'i':
			printf("삽입할 라인 번호: ");
			scanf("%d", &lineNb);
			printf("삽입할 라인: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
			list = insert_pos(list, lineNb - 1, newElement);
			display_te(list);
			break;
		case 'd':
			printf("삭제할 라인 번호: ");
			scanf("%d", &lineNb);
			list = delete_pos(list, lineNb - 1);
			display_te(list);
			break;
		case 'v':
			printf("출력할 라인 번호: ");
			scanf("%d", &lineNb);
			printf("(%d) %s", lineNb, get_entry(list, lineNb - 1).line);
			break;
		case 'p':
			display_te(list);
			break;
		}
		fflush(stdin);
	}
