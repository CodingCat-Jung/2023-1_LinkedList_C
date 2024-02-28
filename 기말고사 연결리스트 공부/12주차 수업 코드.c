// ���� ���Ḯ��Ʈ�� 20,30,40,10 ������� ���� �� 10,20,30,40 ���
// ��Ƽ �÷��̾� ���� ���� ���� ������ ���
// ���� ���Ḯ��Ʈ�� �̿��� 0,1,2,3,4 �߰��ϰ� ����
// MP3 �÷��̾�

// ���� p225 ���� ���� ����Ʈ �׽�Ʈ ���α׷�
// ���� 1. ���� ����Ʈ�� �̿��� ����Ʈ�� 20,30,40,10�� ������� �����ϰ� ����Ʈ�� ����ϴ� ���α׷�
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
		
	// ��������Ʈ���� �׻� ��������ʹ� �׻� ������ ��带 ����Ų��.
	ListNode* head = NULL;

	head = insert_last(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_first(head, 10);

	print_list(head);
	return 0;
}



//////////////////////////////////////////////////
// ���� 228 ��Ƽ �÷��̾� ����
// ���� 2. 5���� �÷��̾ ������ �Ѵ�. ���ӿ� ������ ���� �������� ���� �� �ִ�. ���� ����Ʈ�� �̿��Ͽ� ���α׷��� �ۼ��� ���� ���� �������� ���
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
		printf("���� ���� = %s \n", p->data);
		p = p->link;
	}
	return 0;
}



//////////////////////////////////////////////////
// ���� 234 ���� ���� ����Ʈ������ �����Լ�
// ���� 3. ���� ���Ḯ��Ʈ�� �̿��Ͽ� 0,1,2,3,4 �Է��ϰ� 4,3,2,1,0 �����ϰ� �� �ܰ躰 ����Ʈ ���
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

	printf("�߰� �ܰ�\n");
	for (int i = 0; i < 5; i++) {
		dinsert(head, i);
		print_dlist(head);
	}
	printf("\n");
	printf("���� �ܰ�\n");
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}

	free(head);
	return 0;
}



