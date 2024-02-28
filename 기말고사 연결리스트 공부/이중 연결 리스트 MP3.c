//////////////////////////////////////////////////
// 교재 236 mp3 재생 프로그램
// 문제 4. 이중 연결 리스트를 이용해 음악을 저장하고 사용자의 명령에 따라 곡을 선택하는 프로그램
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef char element[100];
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

DListNode* current;

void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_dlist(DListNode* phead)
{
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == current)
			printf("<-| #%s# |-> ", p->data);
		else
			printf("<-| %s |-> ", p->data);
	}
	printf("\n");
}

void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));

	strcpy(newnode->data, data);

	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed)
{
	// head 노드는 삭제 불가
	if (removed == head) return;

	// head -> removed -> node
	removed->llink->rlink = removed->rlink; // head -> node
	removed->rlink->llink = removed->llink; // node -> head
											// head <-> node
	free(removed);
}

int main() {

	char ch;
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	dinsert(head, "Mamamia");
	dinsert(head, "Dancing Queen");
	dinsert(head, "Fernando");

	current = head->rlink;
	print_dlist(head);

	do {
		printf("\n명령어를 입력하시오(<, >, q): ");
		ch = getchar();

		if (ch == '<') {
			current = current->llink;
			if (current == head)
				current = current->llink;
		}
		else if (ch == '>') {
			current = current->rlink;
			if (current == head)
				current = current->rlink;
		}

		print_dlist(head);
		getchar();
	} while (ch != 'q');

	free(head);
	return 0;
}