//단순연결리스트
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;
// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 노드 pre 뒤에 새로운 노드 삽입
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
	p->link = head; // 헤드 포인터의 값을 복사 //(3)
	head = p; // 헤드 포인터 변경 //(4)
	return head; // 변경된 헤드 포인터 반환
}
ListNode* insert_last(ListNode* head, int value)
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
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
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
	if (head == NULL) error("삭제할 항목이 없음");
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
		error("삭제할 항목이 없음");
	if (temp->link == NULL) {	// 하나의 노드
		removed = temp->link;
		temp->link = NULL;
		free(removed);
		return NULL;
	}
	else {	 // 둘 이상의 노드
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
		free(removed);
		return head;	// 그대로
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
			return p;	// 탐색 성공
		p = p->link;
	}
	return NULL;	// 탐색 실패일 경우 NULL 반환
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
	// 순회 포인터로 p, q, r을 사용
	ListNode* p, * q, * r;
	p = head;	// p는 역순으로 만들 리스트
	q = NULL;	// q는 역순으로 만들 노드
	while (p != NULL) {
		r = q;	// r은 역순으로 된 리스트. r은 q, q는 p를 차례로 따라간다.
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 바꾼다. 
	}
	return q;	// q는 역순으로 된 리스트의 헤드 포인터
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
int get_length(ListNode* head)	// 단순 연결 리스트에 존재하는 노드의 수를 반환
{
	ListNode* p = head;
	int cnt = 0;

	while (p != NULL) {
		cnt++;
		p = p->link;
	}
	return cnt;
}
int get_total(ListNode* head)	// 단순연결리스트의 모든 데이터 값을 더한 합을 반환
{
	ListNode* p = head;
	int sum = 0;

	while (p != NULL) {
		sum += p->data;
		p = p->link;
	}
	return sum;
}
element get_entry(ListNode* head, int pos)	// pos 위치(0 이 첫 번째 노드)에 있는 노드의 data 를 반환
{
	ListNode* p = head;
	int i;

	for (i = 0; p != NULL && i < pos; i++)
		p = p->link;

	return p->data;
}
ListNode* delete_by_key(ListNode* head, int key)	//리스트에서 key값을 검색하여 그를 삭제
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
ListNode* insert_pos(ListNode* head, int pos, element value)	//pos 위치에 value 를 갖는 노드를 추가
{
	/*
	// 방법#1
	ListNode *p;
	int index = 0;

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));

	p = head;
	while(index != pos-1)
	{
		index++;
		p = p->link;
	}*/

	// 방법#2
	ListNode* temp = head;
	int i;

	if (get_length(head) - 1 < pos) {
		error("잘못된pos");
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
	//제출
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
ListNode* delete_pos(ListNode* head, int pos)// pos 위치의 노드를 삭제 
{
	// #1
	ListNode* temp = head;
	ListNode* prevTemp;
	ListNode* removed;
	int index = 0;

	if (head == NULL)
		error("삭제할 항목이 없음");
	if (temp->link == NULL)//하나의 노드
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
		error("잘못된 pos");
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
	//list1 = 30->20->10->를 만든다. 이때 10, 20, 30의 순으로 노드를 삽입한다.
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	// list1을 출력
	printf("list1 = ");
	print_list(list1);
	//list1의 맨 앞 노드를 삭제한다 즉, list1 = 20->10->
	list1 = delete_first(list1);
	// list1을 출력
	printf("list1 = ");
	print_list(list1);
	//list2 = 11->22->33->44->를 만든다. 이때 11, 22, 33, 44의 순으로 노드를 삽입한다.
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	// list2를 출력
	printf("list2 = ");
	print_list(list2);
	// list2의 맨 뒤 노드를 삭제한다. 즉, list2 = 11->22->33->
	list2 = delete_last(list2);
	// list2를 출력
	printf("list2 = ");
	print_list(list2);
	//list2를 역순으로 바꾼 리스트를 list3가 가리키게 한다. list3 = 33->22->11->를 만든다.
	list3 = reverse(list2);

	//list3를 출력한다.
	printf("list3 = ");
	print_list(list3);
	//list1 = 20->10->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다.
	list1 = concat(list1, list3);
	//list1을 출력한다.
	printf("list1 = ");
	print_list(list1);

	//(A) 주의: 여기서부터는 list1만 사용하여 함수들을 테스트하자
	printf("%d\n", is_in_list(list1, 15)); //0
	printf("%d\n", is_in_list(list1, 10)); //1
	printf("list1의 노드의 수는: %d\n", get_length(list1));
	printf("list1의 모든 데이터의 합: %d\n", get_total(list1));
	printf("list1의 3번째 데이터: %d\n", get_entry(list1, 3));//0부터 시작, 22

	printf("list1에서 33삭제: ");
	list1 = delete_by_key(list1, 2);
	print_list(list1);

	printf("\n3번째에 100추가: ");//0부터 시작
	list1 = insert_pos(list1, 3, 100);
	print_list(list1);

	printf("\n3번째 노드 삭제: ");
	delete_pos(list1, 3);
	print_list(list1);
}