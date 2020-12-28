#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100

#define VERTICES 6
#define INF 1000L

typedef struct GraphType {
	int n;	//������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;
int selected[MAX_VERTICES]; // 0���� �ʱ�ȭ, �� ���õ� <����Ʈ������>�� ���������� ����
int distance[MAX_VERTICES]; // <����Ʈ������>���� �������� �ּҰŸ�
int connectedVertex[MAX_VERTICES];//�߰�

// for all v such as selected[v] == FALSE, dist[v]�� �ּҰ��� v�� ��ȯ
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v);
}

void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		connectedVertex[u] = s;		//�ʱ�ȭ
	}
	distance[s] = 0;

	for (i = 0; i < g->n; i++)
	{
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (distance[u] == INF) return;

		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
					connectedVertex[v] = u;		//
				}

	//	printf("<%d %d> %d\n", connectedVertex[u], u, g->weight[connectedVertex[u]][u]);
		printf("\n<%d %d> %d\n", connectedVertex[u], u, distance[u]);
		printf("selected[] = \t");
		for (u = 0; u < g->n; u++)
			printf("%6d", selected[u]);
		printf("\ndist[] = \t");
		for (u = 0; u < g->n; u++)
			printf("%6d", distance[u]);
		printf("\n");
	}
}

int main(void)
{
	GraphType g = { 6,
	{{ 0, 10, INF, 20, 70, INF},
	{ 10,  0, 50, 30, 60, INF},
	{ INF, 50, 0, INF, 40, 90},
	{ 20, 30, INF, 0, INF, 80},
	{ 70, 60, 40, INF, 0, INF},
	{ INF, INF, 90, 80, INF, 0}}
	};


	prim(&g, 0);

	return 0;

	//prim(0, VERTICES);
}