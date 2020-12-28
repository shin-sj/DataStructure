//����Ž��Ʈ�� Ȱ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_STRING 100
typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
void inorder(TreeNode* root) { // ���� ��ȸ
	if (root) {
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("\n-------------------------------\n");
		printf("�й�: %d \n", root->data.id);
		printf("�̸�: %s \n", root->data.name);
		printf("��ȭ��ȣ: %s \n", root->data.tel);
		printf("�а�: %s \n", root->data.dept);
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}
//Ž��(��ȯ)
TreeNode* search(TreeNode* node, element key)
{
	if (node == NULL) 
		return NULL;
	if(key.id == node->data.id)
		return node;
	else if (key.id < node->data.id)
		return search(node->left, key);
	else
		return search(node->right, key);
}
TreeNode* insert_node(TreeNode* root, element data)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (root == NULL) 
		return new_node(data);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
	if(data.id < root->data.id)
		root->left = insert_node(root->left, data);
	else if(data.id > root->data.id)
		root->right = insert_node(root->right, data);
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return root;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL) // �� ���� �ܸ� ��带 ã���� ������
		current = current->left;
	return current;
}
// ���� �Լ�
TreeNode* delete_node(TreeNode* root, element data)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (data.id < root->data.id)
		root->left = delete_node(root->left, data);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	if (data.id > root->data.id)
		root->right = delete_node(root->right, data);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		temp = min_value_node(root->right);
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->data = temp->data;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
//����� ������ ��ȯ
int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) +
		get_node_count(node->right);
	return count;
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	char choice = "";
	element newElement;

	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, c<ount>, q<uit> :");
	scanf("%c", &choice);

	while (choice != 'q') {

		switch (choice) {

		case 'i':
			printf("�й� �Է�: ");
			scanf("%d", &newElement.id);
			printf("�̸� �Է�: ");
			scanf("%s", newElement.name);
			printf("��ȭ��ȣ �Է�: ");
			scanf("%s", newElement.tel);
			printf("�а� �Է�: ");
			scanf("%s", newElement.dept);

			root = insert_node(root, newElement);
			break;
		case 'd':
			printf("������ key�� �Է�: ");
			scanf("%d", &newElement.id);
			root = delete_node(root, newElement);
			break;
		case 's':
			printf("Ž���� key�� �Է�: ");
			scanf("%d", &newElement.id);
			if (search(root, newElement) != NULL) {
				printf("-------------------------------\n");
				printf("�й�: %d\n", newElement.id);
				printf("�̸�: %s\n", newElement.name);
				printf("��ȭ��ȣ: %s\n", newElement.tel);
				printf("�а�: %s\n", newElement.dept);
			}
			else
				printf("id�� %d�� �л��� �����ϴ�.\n", &newElement.id);
			break;
		case 'p':
			printf("�л� ���� �й� �� ���\n");
			inorder(root);
			printf("\n");
			break;
		case 'c':
			printf("���� ����� �л��� �� ���� %d\n", get_node_count(root));
			break;
		}
		fflush(stdin);
		printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, c<ount>, q<uit> :");
		scanf(" %c", &choice);
	}
}