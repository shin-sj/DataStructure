#define MAX_ELEMENT 200

typedef struct {
	int key;	// ������ ����ġ
	int u;		// ���� 1
	int v;		// ���� 2
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;// ������ ��� Ÿ�� ����

void init(HeapType* h);
int is_empty(HeapType* h);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType* h);