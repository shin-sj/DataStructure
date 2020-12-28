//이진탐색트리 연습
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
} TreeNode;
TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
void inorder(TreeNode* root) { // 중위 순회
	if (root) {
		inorder(root->left);// 왼쪽서브트리 순회
		printf("[%d] ", root->key); // 노드 방문
		inorder(root->right);// 오른쪽서브트리 순회
	}
}
//탐색(순환)
TreeNode* search(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}
TreeNode* insert_node(TreeNode* root, int key)
{
	// 트리가 공백이면 새로운 노드를 반환한다.
	if (root == NULL) return new_node(key);
	// 그렇지 않으면 순환적으로 트리를 내려간다.
	if (key < root->key)
		root->left = insert_node(root->left, key);
	else if (key > root->key)
		root->right = insert_node(root->right, key);
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
TreeNode* delete_node(TreeNode* root, int key)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = delete_node(root->right, key);
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
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다.
		root->right = delete_node(root->right, temp->key);
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
//트리의 높이를 반환
int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
//가장 큰값을 출력
//이진탐색트리에서 가장 큰 수는 가장 오른쪽에 있음
int get_maximum(TreeNode* root)
{
	while (root->right != NULL) 
		root = root->right;
	return root->key;
}
//가장 작은값을 출력
//이진탐색트리에서 가장 작은 수는 가장 왼쪽에 있음
int get_minimum(TreeNode* root)
{
	while (root->left != NULL)
		root = root->left;
	return root->key;
}
//print
void preorder(TreeNode* root) 
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	char choice = "";
	int key;

	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, h<eight>, c<ount>, m<ax>, n<min>, q<uit> :");
	scanf("%c", &choice);

	while(choice != 'q') {

		switch (choice) {

			case 'i':
				printf("삽입할 key값 입력: ");
				scanf("%d", &key);
				root = insert_node(root, key);
				break;
			case 'd':
				printf("삭제할 key값 입력: ");
				scanf("%d", &key);
				root = delete_node(root, key);
				break;
			case 's':
				printf("탐색할 key값 입력: ");
				scanf("%d", &key);
				if (search(root, key) != NULL)
					printf("있음\n");
				else
					printf("없음\n");
				break;
			case 'p':
				preorder(root);
				printf("\n");
				break;
			case 'h':
				printf("트리의 높이는 %d\n", get_height(root));
				break;
			case 'c':
				printf("노드의 개수는 %d\n", get_node_count(root));
				break;
			case 'm':
				printf("가장 큰 값은 %d\n", get_maximum(root));
				break;
			case 'n':
				printf("가장 작은 값은 %d\n", get_minimum(root));
				break;
		}
		printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, h<eight>, c<ount>, m<ax>, n<min>, q<uit> :");
		scanf(" %c", &choice);

	}	
}