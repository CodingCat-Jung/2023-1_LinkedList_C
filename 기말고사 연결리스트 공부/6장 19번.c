// �ܼ� ���� ����Ʈ C�� �� ���� �ܼ� ���� ����Ʈ A�� B�� �и��ϴ� �Լ� split�� �ۼ��Ͽ� ����.
// C�� Ȧ�� ��° ������ ���  A�� �̵��ǰ� C�� ¦�� ��° ������ ��� B�� �̵��ȴ�.
// �� �Լ��� C�� �����Ͽ����� �ȵȴ�. 

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
	element data;
	struct ListNode* link;
} ListNode;

void insert_node_back(ListNode** phead, ListNode* new_node) {
	// ù ����� ���
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else {
		new_node->link = NULL;

		ListNode* p = *phead;
		while (p->link != NULL) // ������ ������ �̵�
			p = p->link;

		p->link = new_node; // ������ ����� ��ũ�� new_node�� ����
	}
}

void insert(ListNode** phead, ListNode* p, ListNode* new_p)
{
	// ù ����� ���
	if (*phead == NULL)
	{
		new_p->link = NULL;
		*phead = new_p;
	}
	else
	{
		new_p->link = NULL;

		ListNode* p = *phead;
		while (p->link != NULL)
			p = p->link;

		p->link = new_p;
	}
}

// ���ο� ��� ����
ListNode* create_node(element data)
{
	ListNode* new_p;
	new_p = (ListNode*)malloc(sizeof(new_p));

	new_p->data = data;
	new_p->link = NULL;

	return new_p;
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
}

// C�� Ȧ�� ��° ��带 A�� ��� ����
// C�� ¦�� ��° ��带 B�� ��� ����
void split(ListNode* C, ListNode** A, ListNode** B)
{
	// ���� ����Ʈ C�� ���� x 
	ListNode* r = C;

	while (r != NULL)
	{
		insert_node_back(A, create_node(r->data));
		r = r->link;
		if (r == NULL)
			break;
		insert_node_back(B, create_node(r->data));
		r = r->link;
	}
	return;
}

int main(void)
{
	int n, num;
	ListNode* A = NULL;
	ListNode* B = NULL;
	ListNode* C = NULL;

	printf("����Ʈ C�� ���� : ");
	scanf_s("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		printf("��� #%d ������ : ", i);
		scanf_s("%d", &num);
		insert(&C, C, create_node(num));
	}

	split(C, &A, &B);
	printf("����Ʈ A : ");
	print_list(A);
	printf("\n����Ʈ B : ");
	print_list(B);
	return 0;
}