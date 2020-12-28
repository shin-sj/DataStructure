//자기참조 구조체(4주차 1p)
#include <stdio.h>
#include <stdlib.h>
// 자기 참조 구조체의 정의(선언)
typedef struct ListNode {//이시점에서는 ListNode는 구조체명
	int number;
	struct ListNode* link;
}ListNode;//구조체 타입 정의

// 6) 반복을 이용하여 노드리스트를 출력
// 출력 예: 1->10->20->30->44->
// 힌트: temp를 head부터 시작하여 전진하면서 temp가 가리키는 number를 출력. temp가 NULL이 될때까지.
void displayList1(ListNode* head)
{
	ListNode* temp = head;

	while (temp != NULL)
	{
		printf("%d->", temp->number);
		temp = temp->link;
	}
}
// 7) 순환을 이용하여 노드리스트를 출력
// 출력 예: 1->10->20->30->44->
void displayList2(ListNode* head)
{
	if (head != NULL) 
	{
		printf("%d->", head->number);
		displayList2(head->link);
	}
}
int main(void)
{
	ListNode* head, * newNode, * temp;
// 1)
// ListNode타입의 메모리(노드)를 생성한 후 newNode가 가리키게하고 10과 NULL을 넣어 노드값을 채우고
// 이를 head가 가르키게한다. 즉 head는 노드 하나를 가리킨다.
// 즉, head --> 10,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 10;
	newNode->link = NULL;

	head = newNode; // newNode 연결

 // 2)
 // 같은 방법으로 newNode가 가르키는 메모리(노드)를 생성한후 20과 NULL을 넣어 노드값을 채우고
 // 아래처럼 되게 한다, 즉, 노드리스트 끝에 새로운 노드를 삽입한다.
 // head --> 10,--> 20,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 20;
	newNode->link = NULL;

	head->link = newNode; // newNode 연결
 // 3)
 // 다시 newNode가 가르키는 메모리(노드)를 생성한후 30과 NULL을 넣어 노드값을 채우고
 // 아래처럼 되게 한다. 즉, 노드리스트 끝에 새로운 노드를 삽입한다.
 // head --> 10,--> 20,--> 30,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 30;
	newNode->link = NULL;

	head->link->link = newNode;// newNode 연결

 // 4)
 // 다음과 같이 되게 한다.
 // head --> 10,--> 20,--> 30,--> 44,NULL
 // 노드리스트 끝에 새로운 노드를 삽입할 때,
// temp포인터를 사용하여 head가 가리키는 노드리스트의 마지막을 가리키게 한 후
 // 이 temp를 사용하여 새노드(44,NULL)을 끝에 연결해보자.
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;

	temp = head;
	while (temp->link != NULL)
		temp = temp->link;	//하나 전진
	temp->link = newNode;
	// 5)
	// 다음과 같이 되게 한다. 즉 노드리스트의 앞에 1을 갖는 노드를 삽입
	// head --> 1,--> 10,--> 20,--> 30,--> 44,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1;
	newNode->link = NULL;	//불필요

	newNode->link = head;
	head = newNode;

	// 6)7) displayList1, displayList2를 완성한 후 호출해본다
	displayList1(head);
	printf("\n");
	displayList2(head);
	printf("\n");
}