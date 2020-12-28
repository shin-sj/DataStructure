//이진탐색트리 활용
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
void inorder(TreeNode* root) { // 중위 순회
	if (root) {
		inorder(root->left);// 왼쪽서브트리 순회
		printf("\n-------------------------------\n");
		printf("학번: %d \n", root->data.id);
		printf("이름: %s \n", root->data.name);
		printf("전화번호: %s \n", root->data.tel);
		printf("학과: %s \n", root->data.dept);
		inorder(root->right);// 오른쪽서브트리 순회
	}
}
//탐색(순환)
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
	// 트리가 공백이면 새로운 노드를 반환한다.
	if (root == NULL) 
		return new_node(data);
	// 그렇지 않으면 순환적으로 트리를 내려간다.
	if(data.id < root->data.id)
		root->left = insert_node(root->left, data);
	else if(data.id > root->data.id)
		root->right = insert_node(root->right, data);
	// 변경된 루트 포인터를 반환한다.
	return root;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL) // 맨 왼쪽 단말 노드를 찾으러 내려감
		current = current->left;
	return current;
}
// 삭제 함수
TreeNode* delete_node(TreeNode* root, element data)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (data.id < root->data.id)
		root->left = delete_node(root->left, data);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	if (data.id > root->data.id)
		root->right = delete_node(root->right, data);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
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
		// 세 번째 경우
		temp = min_value_node(root->right);
		// 중외 순회시 후계 노드를 복사한다.
		root->data = temp->data;
		// 중외 순회시 후계 노드를 삭제한다.
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
//노드의 개수를 반환
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
			printf("학번 입력: ");
			scanf("%d", &newElement.id);
			printf("이름 입력: ");
			scanf("%s", newElement.name);
			printf("전화번호 입력: ");
			scanf("%s", newElement.tel);
			printf("학과 입력: ");
			scanf("%s", newElement.dept);

			root = insert_node(root, newElement);
			break;
		case 'd':
			printf("삭제할 key값 입력: ");
			scanf("%d", &newElement.id);
			root = delete_node(root, newElement);
			break;
		case 's':
			printf("탐색할 key값 입력: ");
			scanf("%d", &newElement.id);
			if (search(root, newElement) != NULL) {
				printf("-------------------------------\n");
				printf("학번: %d\n", newElement.id);
				printf("이름: %s\n", newElement.name);
				printf("전화번호: %s\n", newElement.tel);
				printf("학과: %s\n", newElement.dept);
			}
			else
				printf("id가 %d인 학생은 없습니다.\n", &newElement.id);
			break;
		case 'p':
			printf("학생 정보 학번 순 출력\n");
			inorder(root);
			printf("\n");
			break;
		case 'c':
			printf("현재 저장된 학생의 총 수는 %d\n", get_node_count(root));
			break;
		}
		fflush(stdin);
		printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, c<ount>, q<uit> :");
		scanf(" %c", &choice);
	}
}