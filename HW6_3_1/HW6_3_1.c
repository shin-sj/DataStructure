#include <stdio.h>
#include "minheap.h"
#include "unionfind.h"

#define MAX_VERTICES 100
#define INF 9999

typedef struct GraphType {
	int n;					// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;
}

/*  */
void read_graph(GraphType* g, char* filename)
{
	int number, u, v, weight;
	char ch;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d\n", &number);
	g->n = number;
	while (fscanf(fp, "%d %d %d\n", &u, &v, &weight) != EOF)
	{
		g->adj_mat[u][v] = weight;
		g->adj_mat[v][u] = weight;
	}

	fclose(fp);
}

/*  */
void write_graph(GraphType* g, char* filename)
{
	int i, j;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL)
		{
			printf("file %s open error!\n", filename);
			return;
		}
	}

	fprintf(fp, "%d\n", g->n);//제일 첫줄 : 정점의 개수
	/*  대각선 윗부분만 출력 : j=i 
		전체출력 : j=0
	*/
	for (i = 0; i < g->n; i++)
		for (j = i; j < g->n; j++)
			if (g->adj_mat[i][j] != INF)
				fprintf(fp, "%d %d %d\n", i, j, g->adj_mat[i][j]);

	if (filename != NULL) fclose(fp);
}

// 인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입 
// 현재는 예제 그래프의 간선들을 삽입한다.
void insert_all_edges(HeapType* h, GraphType* g)
{
	int i, j;
	element e;

	for (i = 0; i < g->n; i++)
		for (j = i; j < g->n; j++)
			if (g->adj_mat[i][j] != INF) {
				e.u = i;
				e.v = j;
				e.key = g->adj_mat[i][j];
				insert_min_heap(h, e);
			}
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g, GraphType* t) //g: 주어진 그래프 t: 그래프안에서 mst만드는
{
	int edge_accepted = 0;
	HeapType h;
	int uset, vset;
	element e;
	int n = g->n;

	init(&h);
	insert_all_edges(&h, g);
	set_init(n);
	while (edge_accepted < (n - 1)) 
	{
		e = delete_min_heap(&h);
		uset = set_find(e.u);			//대표정점을 반환
		vset = set_find(e.v);
		if (uset != vset) {				//사이클이 아니면
			printf("(%d %d) %d\n", e.u, e.v, e.key);
			t->adj_mat[e.u][e.v] = e.key;
			edge_accepted++;
			set_union(uset, vset);		
		}
	}
}

void main()
{
	GraphType g, t;		// 입력 그래프, 결과 트리

	graph_init(&g);
	read_graph(&g, "input.txt");

	graph_init(&t);
	t.n = g.n;

	printf("선택된 간선(순서대로):\n");
	kruskal(&g, &t);
	printf("\n");

	printf("파일로 출력:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}