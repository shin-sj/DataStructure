//배열로 구현된 스택
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 3

typedef int element;

typedef struct{
   element data[MAX_STACK_SIZE];
   int top;
}StackType;

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

void push(StackType *s, element item)
{
   if(is_full(s))
      printf("스택 포화 에러\n");
   else
      s->data[++(s->top)] = item;
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

   for(i = (s->top); i >= 0; i--)
   {
      if(i == (s->top))
         printf("%d <- top\n", s->data[i]); 
      else
         printf("%d\n", s->data[i]);
   }
   if(is_empty(s))
      printf("<empty>\n");


   printf("-----\n");
}

int main(void)
{
   StackType s;

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
}