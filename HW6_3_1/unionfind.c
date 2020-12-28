#include <stdio.h>
#include "unionfind.h"

#define MAX_VERTICES 100

int parent[MAX_VERTICES];		// �θ� ����� index�� ����; ������ ��ǥ ���ҿ� ���ؼ��� -(�� ���տ� ���� ������ ����)�� �����Ѵ�.
int num[MAX_VERTICES];		// �� ������ ũ�� ==> �ʿ� ����

// �ʱ�ȭ
void set_init(int n)	//�������� ������ �����.
{
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}

int set_find(int vertex)	//��ǥ������ ��ȯ
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p);// ��Ʈ ������ �ݺ�
		
	s = i;			// ������ ��ǥ ����
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;	// ������ ��� ���ҵ��� �θ� p�� ����
	return s;
}
// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int s1, int s2)
{
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}