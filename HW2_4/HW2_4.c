//스택의 활용, Palindrome
#include<stdio.h> 
#define MAX_STRING 100 

typedef struct{ 
	char data[MAX_STRING]; 
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
	return (s->top == (MAX_STRING - 1));
}

void push(StackType *s, char item)
{
	if(is_full(s))
		printf("스택 포화 에러\n");
	else
		s->data[++(s->top)] = item;
}

char pop(StackType *s)
{
	if(is_empty(s))
		return;
	else
		return s->data[(s->top)--];

}
int palindrome(char str[])
{
	StackType s;	// 배열을 사용할 경우, 연결리스트를 사용하면 LinkedStackType s;
	int i;	 // 필요한 변수들 선언
	
	init(&s);	// 스택을 초기화하라
	
	for(i = 0; str[i] != 0; i++)	//str 의 문자들을 스택에 넣는다
	{
		push(&s, str[i]);
	}
	for(i = 0; str[i] != 0; i++)	//스택에서 하나씩 빼면서 str 의 문자들과 차례로 비교
	{
		if(str[i] != pop(&s))
			return 0;
	}
	return 1;
}
int main(void)
{
	char word[MAX_STRING]; 

	printf("Enter a word to check palindrome: ");
	scanf("%s", word);

	if (palindrome(word))
		printf("palindrome 입니다.\n");
	else
		printf("palindrome 이 아닙니다.\n");
} 