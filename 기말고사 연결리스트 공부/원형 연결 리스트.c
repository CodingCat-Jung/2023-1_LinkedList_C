// 7장. 원형 연결 리스트
// 특정 값을 탐색하는 함수 search() : data를 가지고 있는 노드를 반환
// 저장된 데이터의 개수를 반환하는 함수 get_size() 

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

// 특정 값을 탐색하는 함수
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

	return NULL;  // 데이터를 찾지 못한 경우 NULL 반환
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

	ListNode* L = NULL; // 원형 연결리스트 초기화

	// 원형 연결리스트에 데이터 추가

	// 데이터 탐색
	int searchData = 42;
	ListNode* result = search(L, searchData);
	if (result != NULL) {
		printf("Data %d found in the list.\n", searchData);
	}
	else {
		printf("Data %d not found in the list.\n", searchData);
	}

	printf("\n데이터의 개수 %d \n", get_size(head));

	return 0;
}