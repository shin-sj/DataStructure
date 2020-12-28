//������ Ȱ��, Palindrome
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
		printf("���� ��ȭ ����\n");
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
	StackType s;	// �迭�� ����� ���, ���Ḯ��Ʈ�� ����ϸ� LinkedStackType s;
	int i;	 // �ʿ��� ������ ����
	
	init(&s);	// ������ �ʱ�ȭ�϶�
	
	for(i = 0; str[i] != 0; i++)	//str �� ���ڵ��� ���ÿ� �ִ´�
	{
		push(&s, str[i]);
	}
	for(i = 0; str[i] != 0; i++)	//���ÿ��� �ϳ��� ���鼭 str �� ���ڵ�� ���ʷ� ��
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
		printf("palindrome �Դϴ�.\n");
	else
		printf("palindrome �� �ƴմϴ�.\n");
} 