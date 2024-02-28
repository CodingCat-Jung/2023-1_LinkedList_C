// 6�� ��������.
// ����� ���� ���ϱ� get_count()
// ����� ������ �� �ջ� get_sum()
// Ư�� ������ ���� ���� ����� ���� fine_element()
// �� ���� �ܼ� ���Ḯ��Ʈ A, B�� �־��� �ִ� ���, A��B���� ��带 ������ ������ ���ο� ����Ʈ C����� alternate�Լ�
// ���Ḯ��Ʈ C�� �ٸ� ����Ʈ A, B�� split. Ȧ����°�� A, ¦����°�� B�� �и�. C�� �����ϸ� �ȵȴ�. split()

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

int get_count(ListNode* head)
{
	int count = 0;
	ListNode* p = head;
	while (p != NULL) {
		count++;
		p = p->link;
	}
	return count;
}

int get_sum(ListNode* head)
{
	int sum = 0;
	ListNode* p = head;
	while (p != NULL) {
		sum += p->data;
		p = p->link;
	}
	return sum;
}

int find_element(ListNode* head, element item)
{
	ListNode* p = head;
	int count = 0;
	while (p != NULL) {
		if (p->data == item)
			count++;
		p = p->link;
	}
	return count;
}

ListNode* alternate(ListNode* head1, ListNode* head2, ListNode* r)
{
	while (head1 || head2) {
		if (head1 != NULL) {
			r = insert_first(r, head1->data);
			head1 = head1->link;
		}
		if (head2 != NULL) {
			r = insert_first(r, head2->data);
			head2 = head2->link;
		}
	}
	return r;
}


int main() {
	ListNode* head = NULL;

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);
		print_list(head);
	}

	printf("\n");

	printf("���Ḯ��Ʈ ����� ���� %d\n", get_count(head));

	printf("���Ḯ��Ʈ �������� ��: %d\n", get_sum(head));

	printf("���Ḯ��Ʈ���� Ư�� ������ ���� ���� ����� ���� : 1�� %d�� ��Ÿ���ϴ�.\n\n", find_element(head, 1));

	ListNode* head1 = NULL;
	ListNode* head2 = NULL;
	ListNode* r = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);

	head2 = insert_first(head2, 40);
	head2 = insert_first(head2, 50);
	print_list(head2);

	print_list(alternate(head1, head2, r));

	return 0;
}