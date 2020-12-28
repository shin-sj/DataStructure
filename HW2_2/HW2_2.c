//연결리스트를 이용한 스택 ADT
//HW2_2_1
#include <stdio.h>
#include <malloc.h>
typedef int element;
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;
//초기화함수
void init(LinkedStackType* s)
{
	s->top = NULL;
}
//공백상태 검출함수
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
//포화상태 검출함수
int is_full(LinkedStackType* s)
{
	return 0;
}
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

	if (temp == NULL) {
		fprintf(stderr, "메모리 할당에러\n");
		return;
	}
	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
//삭제함수
element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
		//exit(1); //계속 진행하려면 빼기
	}
	else {
		StackNode* temp = s->top;
		int item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
//피크함수
element peek(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else {
		return s->top->item;
	}
}
void stack_print(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link) {
		if (p == (s->top))
			printf("%d <- top\n", p->item);
		else
			printf("%d\n", p->item);
	}
	if (is_empty(s))
		printf("<empty>\n");

	printf("--\n");
}
void main()
{
	LinkedStackType s;

	init(&s);
	stack_print(&s);

	push(&s, 10);
	stack_print(&s);

	push(&s, 20);
	stack_print(&s);

	push(&s, 30);
	stack_print(&s);

	push(&s, 40);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	push(&s, 50);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
}