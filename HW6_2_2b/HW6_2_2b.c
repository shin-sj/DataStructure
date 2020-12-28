//�ʺ�켱Ž��(��������Ʈ �̿�)
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
	int n;	// ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

typedef int element;	// ����� Ÿ��
typedef struct QueueNode {	// ť�� ����� Ÿ�� 
	element item;
	struct QueueNode* link;
} QueueNode;

typedef struct {		// ť ADT ����
	QueueNode* front, * rear;
} QueueType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node_u, * node_v;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node_u = (GraphNode*)malloc(sizeof(GraphNode));
	node_v = (GraphNode*)malloc(sizeof(GraphNode));
	if (node_u == NULL || node_v == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����!\n"); return;
	}

	node_u->vertex = u;
	node_u->link = g->adj_list[v];
	g->adj_list[v] = node_u;
	node_v->vertex = v;
	node_v->link = g->adj_list[u];
	g->adj_list[u] = node_v;
}
int visited[MAX_VERTICES];

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return 0;
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else {
		temp->item = item; 		// ������ ����
		temp->link = NULL; 		// ��ũ �ʵ带 NULL
		if (is_empty(q)) { 		// ť�� �����̸�
			q->front = temp;
			q->rear = temp;
		}
		else { 		// ť�� ������ �ƴϸ�
			q->rear->link = temp;  // ������ �߿�
			q->rear = temp;
		}
	}
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	QueueNode* temp = q->front;
	element item;
	//	if( is_empty(q) )			// �������
	//		error("ť�� ��� �����ϴ�");
	//	else {
	item = temp->item; 		// �����͸� ������.
	q->front = q->front->link; // front�� ������带 ����Ű���� �Ѵ�.
	if (q->front == NULL) 	// ���� ����
		q->rear = NULL;
	free(temp); 			// �����޸� ����
	return item; 			// ������ ��ȯ
//	}
}

// �ʺ� �켱 Ž��(���� ����Ʈ)
// �� �ڵ忡 ������ ����ϱ� ���� �ڵ带 ����
void bfs_list(GraphType* g, int v)
{
	GraphNode* w;
	QueueType q;
	init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� v �湮 ǥ�� 
	enqueue(&q, v);			// ���������� ť�� ���� 
	while (!is_empty(&q)) {
		v = dequeue(&q);	// ť�� ����� ���� ���� 
		for (w = g->adj_list[v]; w; w = w->link) { //���� ���� Ž��
			if (!visited[w->vertex]) {	// �̹湮 ���� Ž�� 
				visited[w->vertex] = TRUE;   // �湮 ǥ��
				printf("<%d %d>\n", v, w->vertex);
				enqueue(&q, w->vertex);	//������ ť�� ����
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

	printf("Enter ����:");
	scanf("%d", &v);

	bfs_list(&graph, v);
}