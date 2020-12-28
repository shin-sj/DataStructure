//인접행렬이용
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef struct GraphType {
    int n;   // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void init(GraphType* g)
{
    int r, c;

    g->n = 0;

    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
    if (((g->n) + 1) > MAX_VERTICES)
    {
        fprintf(stderr, "그래프: 정점의 개수 초과\n");
        return;
    }

    g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int u, int v)
{
    if (u >= g->n || v >= g->n || u < 0 || v < 0)
    {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }

    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1;
}

void delete_edge(GraphType* g, int u, int v)
{
    if (u >= g->n || v >= g->n || u < 0 || v < 0)
    {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }

    g->adj_mat[u][v] = 0;
    g->adj_mat[v][u] = 0;
}

void read_graph(GraphType* g, char* filename)
{
   int number, u, v;
	FILE *fp = fopen(filename, "rt");
	if (fp == NULL) 
	{
		printf("file %s open error!\n", filename);
		return;
	}
	
	fscanf(fp, "%d", &number);
	g->n = number;
	while (fscanf(fp, "%d %d", &u, &v) != EOF) 
		insert_edge(g, u, v);

	fclose(fp);
}

void write_graph(GraphType* g, char* filename)
{
    int i, j;
    FILE* fp;
    if (filename == NULL) fp = stdout;
    else {
        fp = fopen(filename, "wt");
        if (fp == NULL) {
            printf("file %s open error!\n", filename);
            return;
        }
    }

    fprintf(fp, "%d\n", g->n);
    for (i = 0; i < g->n; i++)
        for (j = i; j < g->n; j++)
            if (g->adj_mat[i][j] == 1)
                fprintf(fp, "%d %d\n", i, j);

    if (filename != NULL) 
        fclose(fp);
}

void main(void)
{
    GraphType g;

    init(&g);

    read_graph(&g, "input.txt");
    write_graph(&g, NULL);   // to stdout

    insert_edge(&g, 1, 3);
    write_graph(&g, NULL);   // to stdout

    delete_edge(&g, 2, 0);
    write_graph(&g, NULL);   // to stdout

    write_graph(&g, "output.txt");
}