//���Ḯ��Ʈ�� �̿��� ���� ADT
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
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ翡��\n");
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
		//exit(1); //��� �����Ϸ��� ����
	}
	else {
		StackNode* temp = s->top;
		int item = temp->item;
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