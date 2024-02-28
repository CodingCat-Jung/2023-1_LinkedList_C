// 원형 연결리스트에 20,30,40,10 순서대로 삽입 후 10,20,30,40 출력
// 멀티 플레이어 게임 현재 순서 누군지 출력
// 이중 연결리스트를 이용해 0,1,2,3,4 추가하고 삭제
// MP3 플레이어

// 교재 p225 원형 연결 리스트 테스트 프로그램
// 문제 1. 원형 리스트를 이용해 리스트에 20,30,40,10을 순서대로 삽입하고 리스트를 출력하는 프로그램
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;

	p = head->link;

	do {
		printf("%d->", p->data);
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

int main() {
		
	// 원형리스트에서 항상 헤드포인터는 항상 마지막 노드를 가리킨다.
	ListNode* head = NULL;

	head = insert_last(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_first(head, 10);

	print_list(head);
	return 0;
}



//////////////////////////////////////////////////
// 교재 228 멀티 플레이어 게임
// 문제 2. 5명의 플레이어가 게임을 한다. 게임에 빠지면 누구 순서인지 잊을 수 있다. 원형 리스트를 이용하여 프로그램을 작성해 현재 누구 순서인지 출력
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef char element[100];
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	strcpy(node->data, data);

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

int main() {
	ListNode* head = NULL;

	head = insert_first(head, "KIM");
	head = insert_first(head, "PARK");
	head = insert_first(head, "CHOI");
	head = insert_first(head, "LEE");
	head = insert_first(head, "MIN");

	ListNode* p = head;

	for (int i = 0; i < 10; i++) {
		printf("현재 차례 = %s \n", p->data);
		p = p->link;
	}
	return 0;
}



//////////////////////////////////////////////////
// 교재 234 이중 연결 리스트에서의 삭제함수
// 문제 3. 이중 연결리스트를 이용하여 0,1,2,3,4 입력하고 4,3,2,1,0 삭제하고 각 단계별 리스트 출력
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_dlist(DListNode* phead)
{
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));

	newnode->data = data;

	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

int main() {

	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	printf("추가 단계\n");
	for (int i = 0; i < 5; i++) {
		dinsert(head, i);
		print_dlist(head);
	}
	printf("\n");
	printf("삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}

	free(head);
	return 0;
}



