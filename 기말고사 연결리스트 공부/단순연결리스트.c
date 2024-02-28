// 6장. 단순 연결리스트

// 0부터4까지 삽입 후 삭제
// 특정 값 탐색 search_list()
// 두개의 리스트를 하나로 합치는 함수 concat_list() 
// 리스트를 역순으로 만드는 함수 reverse()

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("%d-> ", p->data);
	}
	printf("NULL \n");
}

ListNode* search_list(ListNode* head, element x)
{
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == x) return p;
		p = p->link;
	}

	return NULL;
}

ListNode* concat_list(ListNode* head1, ListNode* head2)
{
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		ListNode* p;
		p = head1;

		while (p->link != NULL) {
			p = p->link;
			p->link = head2;
			return head1;
		}
	}
}

ListNode* reverse(ListNode* head)
{
	ListNode* p, * q, * r;

	p = head;
	q = NULL;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

int main() {

	// 0부터4까지 넣어주고 출력 후 삭제
	ListNode* head = NULL;

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);
		print_list(head);
	}

	for (int i = 0; i < 5; i++) {
		head = delete_first(head);
		print_list(head);
	}

	printf("\n\n");

	// 특정한 값 탐색
	if (search_list(head, 3) != NULL)
		printf("리스트에서 3을 찾았습니다.\n");
	else
		printf("찾지 못함.\n");

	printf("\n\n");

	// 두개의 리스트를 하나로 합치기
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);

	head2 = insert_first(head2, 40);
	head2 = insert_first(head2, 50);
	print_list(head2);

	ListNode* total = concat_list(head1, head2);
	print_list(total);

	printf("\n\n");

	// 리스트를 역순으로 만들기
	ListNode* head3 = NULL;
	head3 = reverse(head1);
	print_list(head3);


	return 0;
}


// 단어들을 저장하는 연결 리스트
/*

typedef struct {
	char name[100];
}element;

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("%s-> ", p->data.name);
	}
	printf("NULL \n");
}
*/