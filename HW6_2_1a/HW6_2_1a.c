//깊이 우선탐색(인접행렬 이용)
#include <stdio.h>
#define MAX_VERTICES 50

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES] = { 0 };

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void read_graph(GraphType* g, char* filename)
{
	int number, u, v;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d\n", &g->n);
	while (fscanf(fp, "%d %d\n", &u, &v) != EOF) {
		g->adj_mat[u][v] = 1;
		g->adj_mat[v][u] = 1;
	}

	fclose(fp);
}

void dfs_mat(GraphType* g, int v)
{
	int w;
	visited[v] = 1;
	for (w = 0; w < g->n; w++)
		if ((g->adj_mat[v][w] == 1) && (visited[w] == 0)) {
			printf("<%d %d>\n", v, w);
			dfs_mat(g, w);
		}
}

int main(void)
{
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "input.txt");

	printf("Enter 정점:");
	scanf("%d", &v);

	dfs_mat(&graph, v);
}