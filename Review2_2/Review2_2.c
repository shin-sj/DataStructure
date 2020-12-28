//�ڱ����� ����ü(4���� 1p)
#include <stdio.h>
#include <stdlib.h>
// �ڱ� ���� ����ü�� ����(����)
typedef struct ListNode {//�̽��������� ListNode�� ����ü��
	int number;
	struct ListNode* link;
}ListNode;//����ü Ÿ�� ����

// 6) �ݺ��� �̿��Ͽ� ��帮��Ʈ�� ���
// ��� ��: 1->10->20->30->44->
// ��Ʈ: temp�� head���� �����Ͽ� �����ϸ鼭 temp�� ����Ű�� number�� ���. temp�� NULL�� �ɶ�����.
void displayList1(ListNode* head)
{
	ListNode* temp = head;

	while (temp != NULL)
	{
		printf("%d->", temp->number);
		temp = temp->link;
	}
}
// 7) ��ȯ�� �̿��Ͽ� ��帮��Ʈ�� ���
// ��� ��: 1->10->20->30->44->
void displayList2(ListNode* head)
{
	if (head != NULL) 
	{
		printf("%d->", head->number);
		displayList2(head->link);
	}
}
int main(void)
{
	ListNode* head, * newNode, * temp;
// 1)
// ListNodeŸ���� �޸�(���)�� ������ �� newNode�� ����Ű���ϰ� 10�� NULL�� �־� ��尪�� ä���
// �̸� head�� ����Ű���Ѵ�. �� head�� ��� �ϳ��� ����Ų��.
// ��, head --> 10,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 10;
	newNode->link = NULL;

	head = newNode; // newNode ����

 // 2)
 // ���� ������� newNode�� ����Ű�� �޸�(���)�� �������� 20�� NULL�� �־� ��尪�� ä���
 // �Ʒ�ó�� �ǰ� �Ѵ�, ��, ��帮��Ʈ ���� ���ο� ��带 �����Ѵ�.
 // head --> 10,--> 20,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 20;
	newNode->link = NULL;

	head->link = newNode; // newNode ����
 // 3)
 // �ٽ� newNode�� ����Ű�� �޸�(���)�� �������� 30�� NULL�� �־� ��尪�� ä���
 // �Ʒ�ó�� �ǰ� �Ѵ�. ��, ��帮��Ʈ ���� ���ο� ��带 �����Ѵ�.
 // head --> 10,--> 20,--> 30,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 30;
	newNode->link = NULL;

	head->link->link = newNode;// newNode ����

 // 4)
 // ������ ���� �ǰ� �Ѵ�.
 // head --> 10,--> 20,--> 30,--> 44,NULL
 // ��帮��Ʈ ���� ���ο� ��带 ������ ��,
// temp�����͸� ����Ͽ� head�� ����Ű�� ��帮��Ʈ�� �������� ����Ű�� �� ��
 // �� temp�� ����Ͽ� �����(44,NULL)�� ���� �����غ���.
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;

	temp = head;
	while (temp->link != NULL)
		temp = temp->link;	//�ϳ� ����
	temp->link = newNode;
	// 5)
	// ������ ���� �ǰ� �Ѵ�. �� ��帮��Ʈ�� �տ� 1�� ���� ��带 ����
	// head --> 1,--> 10,--> 20,--> 30,--> 44,NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1;
	newNode->link = NULL;	//���ʿ�

	newNode->link = head;
	head = newNode;

	// 6)7) displayList1, displayList2�� �ϼ��� �� ȣ���غ���
	displayList1(head);
	printf("\n");
	displayList2(head);
	printf("\n");
}