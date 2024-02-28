// 단순 연결 리스트 C를 두 개의 단순 연결 리스트 A와 B로 분리하는 함수 split를 작성하여 보자.
// C의 홀수 번째 노드들을 모두  A로 이동되고 C의 짝수 번째 노드들은 모두 B로 이동된다.
// 이 함수가 C를 변경하여서는 안된다. 

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
	element data;
	struct ListNode* link;
} ListNode;

void insert_node_back(ListNode** phead, ListNode* new_node) {
	// 첫 노드일 경우
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else {
		new_node->link = NULL;

		ListNode* p = *phead;
		while (p->link != NULL) // 마지막 노드까지 이동
			p = p->link;

		p->link = new_node; // 마지막 노드의 링크를 new_node에 연결
	}
}

void insert(ListNode** phead, ListNode* p, ListNode* new_p)
{
	// 첫 노드일 경우
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

// 새로운 노드 생성
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

// C의 홀수 번째 노드를 A로 모두 복사
// C의 짝수 번째 노드를 B로 모두 복사
void split(ListNode* C, ListNode** A, ListNode** B)
{
	// 연결 리스트 C는 변경 x 
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

	printf("리스트 C의 개수 : ");
	scanf_s("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		printf("노드 #%d 데이터 : ", i);
		scanf_s("%d", &num);
		insert(&C, C, create_node(num));
	}

	split(C, &A, &B);
	printf("리스트 A : ");
	print_list(A);
	printf("\n리스트 B : ");
	print_list(B);
	return 0;
}