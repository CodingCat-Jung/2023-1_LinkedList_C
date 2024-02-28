// �Է¹��� ���ڰ� ���Ḯ��Ʈ�� �� �� �����ϴ���
// ¦�� ��° �ε��� ����
// ���Ḯ��Ʈ �� �ִ�, �ּڰ�

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

////////////////////////////////////////////////////////////////////////////////
////////////////////////// �ܼ����Ḯ��Ʈ �ڵ� /////////////////////////////////
typedef int element;

typedef struct ListNode {
	element data; 
	struct ListNode* link; 
} ListNode;

typedef struct {
	// ù ��° ��带 ����Ű�� ������. ù ��° ��尡 ���� ��� null ���� ������
	// ListNode* Ÿ������ ����Ǿ� ù ��° ����� �ּҸ� ����
	ListNode* head; 

	// ���Ḯ��Ʈ�� ����(����� ����)�� ��Ÿ���� ���� ��
	// ���Ḯ��Ʈ�� ����� ����� ������ �����ϱ� ���� ���
	int length;
} ListType;
// �̷��� ����ü�� ����ϸ� ���Ḯ��Ʈ�� �� �� ȿ�������� ������ �� �ֽ��ϴ�.
// head �ʵ带 ���� ����Ʈ�� ù ��° ��忡 ���� ������ �� ������, 
// length �ʵ带 ���� ����Ʈ�� ���̸� ������ �� �� �ֽ��ϴ�.


// ����Ʈ�� �ʱ�ȭ
void init(ListType* list)
{
	if (list == NULL)
		return;

	list->head = NULL;
	list->length = 0;
}

// ����Ʈ�� ����(����� ����) ��ȯ
int get_length(ListType* list)
{
	return list->length;
}

// ������ ��ġ�� ��� ������ ��ȯ
ListNode* get_node_at(ListType* list, int pos)
{
	int i;
	ListNode* tmp_node = list->head;

	// ���� ��ġ
	if (pos < 0)
		return NULL;

	// ���Ḯ��Ʈ�� pos���� �̵�
	for (int i = 0; i < pos; i++) {
		tmp_node = tmp_node->link;
	}

	return tmp_node;
}

// phead : ����Ʈ�� ��� �������� ������
// p : ���� ���
// new_node : ������ ���
void insert_node(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) {		// ���鸮��Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {		// �����尡 NULL�� ��쿡 ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {								// p ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}

// ������ ��ġ�� �����͸� ���� ��带 �߰�
void add(ListType* list, int position, element data)
{
	// �߰��� �ű� ���  �տ� �ִ� ����� ������
	ListNode* p;

	// ������ġ�� ��ȿ�� �˻�
	if ((position >= 0) && (position <= list->length)) {

		// �޸� �����Ҵ� �� ��ȿ�� üũ
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) {
			printf("memory allocation failture\n");
			return;
		}

		node->data = data;

		// �ű� ��尡 �߰��� �ٷ� �տ� ��ġ�� ��� �����͸� ���´�.
		p = get_node_at(list, position - 1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}

// ����Ʈ�� �� ���� �����͸� ���� ��带 �߰�
void add_last(ListType* list, element data)
{
	add(list, get_length(list), data);
}

// ����Ʈ�� �� �տ� �����͸� ���� ��带 �߰�
void add_first(ListType* list, element data)
{
	add(list, 0, data);
}

// ����Ʈ�� ����ִ��� Ȯ��
int is_empty(ListType* list)
{
	if (list->head == NULL)
		return TRUE;
	else
		return FALSE;
}

// phead : ��������Ϳ� ���� ������
// p : ������ ����� ���� ���
// removed : ������ ���
void remove_node(ListNode** phead, ListNode* p, ListNode* removed)
{
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;

	free(removed);
}

// ������ ��ġ�� ��带 ����
void deleteNode(ListType* list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {

		ListNode* p = get_node_at(list, pos - 1);

		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}

// ����Ʈ�� ������ ���
void display(ListType* list)
{
	int i;
	ListNode* node = list->head;

	for (i = 0; i < list->length; i++) {
		printf("%d ", node->data);
		node = node->link;
	}

	printf("\n\n");
}

// ����Ʈ�� ��� ��带 ����
void clear(ListType* list)
{
	int i;
	for (i = 0; i < list->length; i++) {
		deleteNode(list, i);
	}
}

// ����Ʈ���� �Ű������� ���� item�� ������ ã��
int search_list(ListType* list, element item)
{
	int nCount = 0;
	ListNode* p;

	p = list->head;

	while (p != NULL) {
		if (p->data == item)
			nCount++;
		p = p->link;
	}

	return nCount;
}

// ¦�� ��° ��ġ�� �ִ� ��带 ����
void delete_even(ListType* list)
{
	int i;
	for (i = 0; i < list->length; i += 2) {
		deleteNode(list, i);
	}
}

// ����Ʈ���� ���� ū ���� ��ȯ
element listMax(ListType* list)
{
	int max;
	ListNode* p;
	p = list->head;

	// ù��° ����� ������ ������ max ����
	if (p != NULL) {
		max = p->data;
		p = p->link;
	}

	while (p != NULL) {
		if (max < p->data)
			max = p->data;
		p = p->link;
	}
	return max;
}

// ����Ʈ���� ���� ���� ���� ��ȯ
element listMin(ListType* list)
{
	int min;
	ListNode* p;
	p = list->head;

	// ù��° ����� ������ ������ min ����
	if (p != NULL) {
		min = p->data;
		p = p->link;
	}

	while (p != NULL) {
		if (min > p->data)
			min = p->data;
		p = p->link;
	}
	return min;
}
////////////////////////// �ܼ����Ḯ��Ʈ �ڵ� /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void main()
{
	FILE* fp;
	int nTemp;
	ListType list; // ���Ḯ��Ʈ�� ��������� ����

	init(&list); //  ���Ḯ��Ʈ �ʱ�ȭ

	fp = fopen("data1.txt", "r");
	if (fp == NULL) {
		printf("file not open\n");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &nTemp);

		add_last(&list, nTemp);
	}

	fclose(fp);

	display(&list);

	// 2. ����ڰ� �Է��� ���ڰ� �� �� �ִ��� ���
	int nCount = 0;

	while (1) {
		printf("���� �Է��ϼ���<0:����> : ");
		scanf("%d", &nTemp);

		if (nTemp == 0) break;

		nCount = search_list(&list, nTemp);

		printf("%d�� ����Ʈ�� %d�� �ֽ��ϴ�.\n", nTemp, nCount);
	}
	printf("\n");

	// 3. �ε����� ¦�� ��° ��ġ�� �����ϴ� �Լ� �߰�
	delete_even(&list);
	display(&list);
	printf("\n");

	// 4. ���Ḯ��Ʈ ������ �ּڰ�, �ִ�
	nTemp = listMax(&list);
	printf("�ִ밪�� %d�Դϵ�.\n", nTemp);


	nTemp = listMin(&list);
	printf("�ּҰ��� %d�Դϵ�.\n", nTemp);

	clear(&list);
}