#include <stdio.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100	//����Ǽ�
#define INF 9999			//���� ��(������ ���� ���)

int distance[MAX_VERTICES];	//���۳��κ����� �ִܰ�ΰŸ�
int previous[MAX_VERTICES];	//�߰� : ������� 
int found[MAX_VERTICES];	//�湮�� ��� ǥ��

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int r, c;

	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = INF;
		}
	}

	for (r = 0; r < MAX_VERTICES; r++)
		g->adj_mat[r][r] = 0;
}

void read_graph(GraphType* g, char* filename)
{
	int n, u, v;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "���� %s�� �� �� ���� \n", filename); return;
	}
	fscanf(fp, "%d\n", &n);
	g->n = n;
	while (fscanf(fp, "%d %d", &u, &v) != EOF) {
		fscanf(fp, "%d\n", &g->adj_mat[u][v]);
		g->adj_mat[v][u] = g->adj_mat[u][v];
	}
	fclose(fp);
}

int choose(int distance[], int n, int found[])
{
	int i;
	int m = -1;
	int min = INT_MAX;

	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			m = i;
		}
	}
	return m;
}

void print_path(int start, int end)
{
	if (start == end)
		printf("%d -> ", start);
	else {
		print_path(start, previous[end]);
		printf("%d -> ", end);
	}
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;

	for (i = 0; i < g->n; i++)
	{
		distance[i] = g->adj_mat[start][i];
		previous[i] = start;	//�ʱ�ȭ
		found[i] = FALSE;
	}

	found[start] = TRUE;		//���۳�� �湮 ǥ��
	distance[start] = 0;

	for (i = 0; i < (g->n) - 1; i++) {
		u = choose(distance, g->n, found);	//�湮���� ���� ����� distance���� ������
		found[u] = TRUE;

		print_path(start, u);	//���� ��� ���
		printf("(%d)\n", distance[u]);

		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->adj_mat[u][w] < distance[w]) {
					distance[w] = distance[u] + g->adj_mat[u][w];
					previous[w] = u;	//������� ����
				}
			}
		}
	}
}

void main(void)
{
	GraphType g;

	graph_init(&g);
	read_graph(&g, "input.txt");
	shortest_path(&g, 0);
}