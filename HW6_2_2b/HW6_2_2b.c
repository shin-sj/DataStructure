//너비우선탐색(인접리스트 이용)
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

typedef int element;	// 요소의 타입
typedef struct QueueNode {	// 큐의 노드의 타입 
	element item;
	struct QueueNode* link;
} QueueNode;

typedef struct {		// 큐 ADT 구현
	QueueNode* front, * rear;
} QueueType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node_u, * node_v;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node_u = (GraphNode*)malloc(sizeof(GraphNode));
	node_v = (GraphNode*)malloc(sizeof(GraphNode));
	if (node_u == NULL || node_v == NULL) {
		fprintf(stderr, "메모리 할당 에러!\n"); return;
	}

	node_u->vertex = u;
	node_u->link = g->adj_list[v];
	g->adj_list[v] = node_u;
	node_v->vertex = v;
	node_v->link = g->adj_list[u];
	g->adj_list[u] = node_v;
}
int visited[MAX_VERTICES];

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화 함수
void init(QueueType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == NULL);
}
// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return 0;
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다");
	else {
		temp->item = item; 		// 데이터 저장
		temp->link = NULL; 		// 링크 필드를 NULL
		if (is_empty(q)) { 		// 큐가 공백이면
			q->front = temp;
			q->rear = temp;
		}
		else { 		// 큐가 공백이 아니면
			q->rear->link = temp;  // 순서가 중요
			q->rear = temp;
		}
	}
}

// 삭제 함수
element dequeue(QueueType* q)
{
	QueueNode* temp = q->front;
	element item;
	//	if( is_empty(q) )			// 공백상태
	//		error("큐가 비어 있읍니다");
	//	else {
	item = temp->item; 		// 데이터를 꺼낸다.
	q->front = q->front->link; // front를 다음노드를 가리키도록 한다.
	if (q->front == NULL) 	// 공백 상태
		q->rear = NULL;
	free(temp); 			// 동적메모리 해제
	return item; 			// 데이터 반환
//	}
}

// 너비 우선 탐색(인접 리스트)
// 이 코드에 간선을 출력하기 위한 코드를 삽입
void bfs_list(GraphType* g, int v)
{
	GraphNode* w;
	QueueType q;
	init(&q);    				// 큐 초기 화 
	visited[v] = TRUE;      // 정점 v 방문 표시 
	enqueue(&q, v);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);	// 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) { //인접 정점 탐색
			if (!visited[w->vertex]) {	// 미방문 정점 탐색 
				visited[w->vertex] = TRUE;   // 방문 표시
				printf("<%d %d>\n", v, w->vertex);
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
		}
	}
}

void read_graph(GraphType* g, char* filename)
{
	int number, u, v;
	GraphNode* node;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file open error!\n");
		return;
	}

	fscanf(fp, "%d\n", &number);
	g->n = number;
	while (fscanf(fp, "%d %d\n", &u, &v) != EOF)
		insert_edge(g, u, v);

	fclose(fp);
}
int main(void)
{
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "input.txt");

	printf("Enter 정점:");
	scanf("%d", &v);

	bfs_list(&graph, v);
}