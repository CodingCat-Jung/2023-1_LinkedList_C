// ���׽��� ���� ����Ʈ�� ǥ���� �� ������ ������. ���׽��� ���� ����Ʈ�� ǥ���Ǿ� �ְ�, p�� ���׽��� ����Ű�� �����Ͷ�� �� ��, 
// � �Ǽ� x�� ���Ͽ� �� ���׽��� ���� ����ϴ� �Լ� poly_eval�� �ۼ��϶�. 
// �� ���׽��� x^3 + 2x +6�̰� x=2�̸� 2^3 + 2*2 + 6�� ����ϴ� �Լ��� �ۼ��Ͽ�����.

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;


typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;

void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���׽� ����Ʈ ����
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// ��� ����
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp =
		(ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL) error("�޸� �Ҵ� ����");

	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;

	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}


void poly_print(ListType* plist)
{
	ListNode* p = plist->head;

	printf("polynomial = ");
	for (; p; p = p->link) {
		printf("%d*x^%d + ", p->coef, p->expon);
	}
	printf("\n");
}

// ���׽� ���
int poly_eval(ListType* plist, int x)
{
	ListNode* p = plist->head;
	int result, eval = 0;
	for (; p; p = p->link)
	{
		result = 1;
		for (int i = 0; i < p->expon; i++)
			result *= x;
		result = p->coef * result;
		eval += result;
	}
	return eval;
}

int main(void)
{
	ListType* list;
	int x = 0;
	list = create();

	// ���׽� 1�� ���� 
	insert_last(list, 3, 2);
	insert_last(list, 2, 1);
	insert_last(list, 1, 0);

	poly_print(list);

	printf("������ x�� �� : ");
	scanf_s("%d", &x);

	printf("���׽��� �� = %d", poly_eval(list, x));
	free(list);
}

