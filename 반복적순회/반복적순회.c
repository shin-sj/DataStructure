//ppt 93p
//�ݺ����� ��ȸ���� ������ ���� program 7.9(p241)�� �̿��ؼ� Ǯ ��
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;
//������ ���� Ÿ�� ����
typedef TreeNode* element;
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;
typedef struct {
	StackNode* top;
} LinkedStackType;
//�����Լ� ����
void init(LinkedStackType* s)
{
	s->top = NULL;
}
int is_empty(LinkedStackType* s)
{
	return s->top == NULL;
}
void push(LinkedStackType* s, TreeNode* p)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "�޸��Ҵ翡��\n");
		return;
	}
	else {
		temp->item = p;
		temp->link = s->top;
		s->top = temp;
	}
}
TreeNode* pop(LinkedStackType* s)
{
	StackNode* temp;
	TreeNode* p;

	if (is_empty(s)) {
		fprintf(stderr, "�����̺������\n");
		exit(1);
	}
	else {
		temp = s->top;
		p = temp->item;
		s->top = s->top->link;
		free(temp);
		return p;
	}
}
//�ݺ��� �̿��� ���� ��ȸ
void inorder_iter(TreeNode* root)
{
	LinkedStackType* s;
	init(&s);

	while (1) {
		for (; root; root = root->left)
			push(&s, root);
		if (is_empty(&s))
			break;
		else
			root = pop(&s);

		printf("[%d] ", root->data);
		root = root->right;
	}
}

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

int main(void)
{
	printf("���� ��ȸ=");
	inorder_iter(root);
	printf("\n");
	return 0;
}