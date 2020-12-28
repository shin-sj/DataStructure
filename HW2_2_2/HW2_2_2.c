//���Ḯ��Ʈ�� �̿��� ���� ADT
//HW2_2_2
/*
* //����
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef struct {
	int num;
	char* str;

}element;
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;
//�ʱ�ȭ�Լ�
void init(LinkedStackType* s)
{
	s->top = NULL;
}
//������� �����Լ�
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
//��ȭ���� �����Լ�
int is_full(LinkedStackType* s)
{
	return 0;
}
void push(LinkedStackType* s, int item, char *str)
{
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode));

	if (temp == NULL) {
		fprintf(stderr, "������ �������\n");
		return;
	}
	else {
		temp->item.num = item;
		temp->item.str = (char*)malloc(strlen(str) + 1);
		strcpy(temp->item.str, str);
		temp->link = s->top;
		s->top = temp;
	}
}
//�����Լ�
element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
//��ũ�Լ�
element peek(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		return s->top->item;
	}
}
void stack_print(LinkedStackType* s)
{
	StackNode* p = s->top;

	if (is_empty(s)) {
		printf("stack is empty\n");
		return;
	}
	printf("%d %s <-top\n", p->item.num, p->item.str);
	for (p = p->link; p; p = p->link)
	{
		printf("%d %s\n", p->item.num, p->item.str);
	}
}
void main()
{
	LinkedStackType s;

	init(&s);

	stack_print(&s);
	printf("--\n");
	push(&s, 10, "ten");
	stack_print(&s);
	printf("--\n");
	push(&s, 20, "twenty");
	stack_print(&s);
	printf("--\n");
	push(&s, 30, "thirty");
	stack_print(&s);
	printf("--\n");
	push(&s, 40, "forty");
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	printf("--\n");
	push(&s, 50, "fifty");
	stack_print(&s);
	printf("--\n");
	pop(&s);
	stack_print(&s);
	printf("--\n");
	pop(&s);
	stack_print(&s);
	printf("--\n");
	pop(&s);
	stack_print(&s);
}

*/
//���� �ڵ�
//HW2_2_2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 3
#define MAX_STRING 100

typedef struct {
	int num;
	char* numString[MAX_STRING];

}element;
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;
//�ʱ�ȭ�Լ�
void init(LinkedStackType* s)
{
	s->top = NULL;
}
//������� �����Լ�
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
//��ȭ���� �����Լ�
int is_full(LinkedStackType* s)
{
	return 0;
}
//�����Լ�
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		return;
	}
	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
//�����Լ�
element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
//��ũ�Լ�
element peek(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		return s->top->item;
	}
}
void stack_print(LinkedStackType* s)
{
	StackNode* p;

	if (is_empty(s)) {
		printf("<empty>\n");
		printf("--\n");
	}
	else
	{
		for (p = s->top; p != NULL; p = p->link) {
			printf("[%d, %s]", p->item.num, p->item.numString);
			if (p == s->top)
				printf(" <- top");
			printf("\n");
		}
		printf("--\n");
	}
}
void main()
{
	LinkedStackType s;
	element e;

	init(&s);
	stack_print(&s);

	e.num = 10;
	strcpy(e.numString, "ten");
	push(&s, e);
	stack_print(&s);

	e.num = 20;
	strcpy(e.numString, "twenty");
	push(&s, e);
	stack_print(&s);

	e.num = 30;
	strcpy(e.numString, "thirty");
	push(&s, e);
	stack_print(&s);

	e.num = 40;
	strcpy(e.numString, "forty");
	push(&s, e);
	stack_print(&s);

	e.num = 50;
	strcpy(e.numString, "fifty");
	push(&s, e);
	stack_print(&s);
}