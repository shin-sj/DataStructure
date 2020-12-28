//��������Ʈ�̿�
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef int element;
typedef struct GraphNode
{
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;	// ������ ����
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
    int v;
    g->n = 0;
    for (v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int u, int v)
{
    GraphNode* node_u, * node_v, *node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    node_u = (GraphNode*)malloc(sizeof(GraphNode));
    if (node_u == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����!\n"); return;
    }

    // u �� v �� �Ŵܴ�
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
    // v �� u �� �Ŵܴ�
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = u;
    node->link = g->adj_list[v];
    g->adj_list[v] = node;
 
}

void remove_node(GraphNode** phead, element item) { // 4�� ����Ʈ���� �н��� �Լ����� ListNode --> GraphNode�� ��������
    GraphNode* p, * prevp;

    if (*phead == NULL)
        printf("����Ʈ�� ����ֽ��ϴ�.\n");
    else if ((*phead)->vertex == item) {
        p = *phead;
        *phead = (*phead)->link;
        free(p);
    }
    else {
        p = *phead;
        do {
            prevp = p;
            p = p->link;
        } while (p != NULL && p->vertex != item);
        if (p != NULL) {
            prevp->link = p->link;
            free(p);
        }
        else
            printf("%d�� ����Ʈ�� ����\n", item);
    }
}
// ���� ���� ����, v�� u�� ���� ����Ʈ���� �����Ѵ�.
void delete_edge(GraphType* g, int u, int v)
{
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    
    // (u, v)�� �����Ѵ�. remove_node�� ���. 
    remove_node(&g->adj_list[u], v);
    remove_node(&g->adj_list[v], u);
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
void write_graph(GraphType* g, char* filename)
{
    int u;
    FILE* fp;
    GraphNode* ptr;

    if (filename == NULL) fp = stdout;
    else {
        fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("file %s open error!\n", filename);
            return;
        }
    }

    fprintf(fp, "%d\n", g->n);
    for (u = 0; u < g->n; u++)
        for (ptr = g->adj_list[u]; ptr != NULL; ptr = ptr->link)
            fprintf(fp, "%d %d\n", u, ptr->vertex);

    if (filename != NULL)
        fclose(fp);
}

int main(void)
{
    GraphType g;
    graph_init(&g);

    read_graph(&g, "input.txt");
    write_graph(&g, NULL);	// to stdout

    insert_edge(&g, 1, 3);
    write_graph(&g, NULL);	// to stdout

    delete_edge(&g, 2, 0);
    write_graph(&g, NULL);	// to stdout

    write_graph(&g, "output.txt");
}
