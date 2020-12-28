#define MAX_ELEMENT 200

typedef struct {
	int key;	// 간선의 가중치
	int u;		// 정점 1
	int v;		// 정점 2
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;// 히프의 요소 타입 정의

void init(HeapType* h);
int is_empty(HeapType* h);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType* h);