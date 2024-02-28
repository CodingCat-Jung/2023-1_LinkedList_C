// 7��. ���� ���� ����Ʈ
// Ư�� ���� Ž���ϴ� �Լ� search() : data�� ������ �ִ� ��带 ��ȯ
// ����� �������� ������ ��ȯ�ϴ� �Լ� get_size() 

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element data;
	struct ListNode* link;
}ListNode;

void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;

	p = head->link;

	do {
		printf("%d-> ", p->data);
		p = p->link;
	} while (p != head->link);
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;

	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head;
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;

	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

// Ư�� ���� Ž���ϴ� �Լ�
ListNode* search(ListNode* L, element data) {
	if (L == NULL) {
		return NULL;
	}

	ListNode* current = L;
	do {
		if (current->data == data) {
			return current;
		}
		current = current->link;
	} while (current != L);

	return NULL;  // �����͸� ã�� ���� ��� NULL ��ȯ
}

int get_size(ListNode* L) {
	if (L == NULL) {
		return 0;
	}

	ListNode* current = L;
	int size = 0;

	do {
		size++;
		current = current->link;
	} while (current != L);

	return size;
}

int main() {
	ListNode* head = NULL;

	head = insert_last(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_last(head, 10);
	print_list(head);

	ListNode* L = NULL; // ���� ���Ḯ��Ʈ �ʱ�ȭ

	// ���� ���Ḯ��Ʈ�� ������ �߰�

	// ������ Ž��
	int searchData = 42;
	ListNode* result = search(L, searchData);
	if (result != NULL) {
		printf("Data %d found in the list.\n", searchData);
	}
	else {
		printf("Data %d not found in the list.\n", searchData);
	}

	printf("\n�������� ���� %d \n", get_size(head));

	return 0;
}