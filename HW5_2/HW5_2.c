//�迭�� ������ Heap Ʈ��, ��������� ó�� ����
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#define TRUE 1
#define FALSE 0

FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);
int fscanf(FILE* stream, const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);

typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;
// ���� �Լ�: ���� ����� ������ heap_size �� ���� h �� item �� �����Ѵ�.
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // ���ο� ��带 ����
}
// ���� �Լ�
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void read_heap(HeapType* h, char* filename)// - ���Ͽ��� �о max Heap �� �����Ѵ�.
{
	FILE* fp = fopen(filename, "r");
	int number;

	if (fp == NULL) {
		fprintf(stderr, "���� %s�� �� �� ����!\n", filename);
		return;
	}

	while (fscanf(fp, "%d\n", &h) != EOF) //�����б�
		scanf(fp, "%d\n", &h);
	
	fclose(fp);

}
void write_heap_array(HeapType* h, char* filename) //- max Heap �� ����� ������ �迭�� ǥ�� �״�� ���Ͽ� ����Ѵ�.
{
	FILE* fp = fopen(filename, "r");
	int i;

	if (filename == NULL)
		fp = stdout;
	else {
		fp = fopen(filename, "w");
		if (fp == NULL) {
			fprintf(stderr, "���� %s�� �� �� ����!\n", filename);
			return;
		}
	}

	for (i = 0; i < h->heap_size; i++)
		fprintf(fp, "%d\n", h->heap[i]);

	fclose(fp);
}
void write_descending_order(HeapType* h, char* filename)// - max Heap �� ����� ������ ������������ ���Ͽ� ����Ѵ�.
{
	int i;
	FILE* fp = fopen(filename, "r");
	element a[100];
	HeapType heap;
	int size = heap.heap_size;

	for (i = (size - 1); i >= 0; i--) {
		a[i] = delete_max_heap(&heap);
		fprintf(filename, "%d\n", a[i]);
	}

	fclose(fp);
}

int main(void)
{
	HeapType heap;
	element e1 = { 20 }, e2 = { 40 };
	init(&heap);
	read_heap(&heap, "input.txt");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	write_heap_array(&heap, "heapArray.txt");
	write_descending_order(&heap, "sorted.txt");
}
