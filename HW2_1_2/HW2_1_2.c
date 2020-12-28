//배열로 구현된 스택
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 3
#define MAX_STRING 10
typedef struct {
	int num;
	char numString[MAX_STRING];
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
void init(StackType *s)
{
   s->top = -1;
}

int is_empty(StackType *s)
{
   return (s->top == -1);
}

int is_full(StackType *s)
{
   return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, int num, char *str)
{
	if (is_full(s))
	{
		printf("스택 포화 에러\n");
		return;
	}
	else
		(s->top)++; 
		strcpy_s(s->data[s->top].numString, sizeof(s->data[s->top].numString), str); 
		s->data[s->top].num = num; 
}

element pop(StackType *s)
{
   if(is_empty(s))
      exit(1);
   else
      return s->data[(s->top)--];

}

element peek(StackType *s)
{
   if(is_empty(s))
      exit(1);
   else
      return s->data[s->top];
}

void stack_print(StackType *s)
{
	int i;

	if (is_empty(s))
		printf("<empty>\n");
	else
	{
		for (i = s->top; i >= 0; i--)
		{
			if (i == s->top)
				printf("[%d %s] <- top\n", s->data[i].num, s->data[i].numString);
			else
				printf("[%d %s]\n", s->data[i].num, s->data[i].numString);
		}
	}
}

int main(void)
{
	StackType s;

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