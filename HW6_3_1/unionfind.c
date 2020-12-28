#include <stdio.h>
#include "unionfind.h"

#define MAX_VERTICES 100

int parent[MAX_VERTICES];		// 부모 노드의 index를 저장; 집합의 대표 원소에 대해서는 -(그 집합에 속한 원소의 갯수)를 저장한다.
int num[MAX_VERTICES];		// 각 집합의 크기 ==> 필요 없음

// 초기화
void set_init(int n)	//독립적인 집합을 만든다.
{
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}

int set_find(int vertex)	//대표정점을 반환
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p);// 루트 노드까지 반복
		
	s = i;			// 집합의 대표 원소
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;	// 집합의 모든 원소들의 부모를 p로 설정
	return s;
}
// 두개의 원소가 속한 집합을 합친다.
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