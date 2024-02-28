// 두개의 다항식이 다음과 같이 주어졌다. 이들을 연결 리스트를 이용하여 나타내고 본문의 프로그램을 이용하여 두 다항식의 합을 구해보시오.
// A(x) = 3x ^ 6 + 7x ^ 3 - 2x ^ 2 - 9, B(x) = -2x ^ 6 - 4x ^ 4 + 6x ^ 2 + 6x + 1

#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode
{
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;

typedef struct ListHeader
{
	int length;
	ListNode* head;
	ListNode* tail;
}ListHeader;

void init(ListHeader* plist)
{
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

// 다항식
void insert_node_last(ListHeader* plist, int coef, int expon)
{
	// 새로운 항 노드 생성 - 차수, 계수
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;

	// 다항식 연결리스트 꼬리에 연결
	if (plist->tail == NULL)
	{
		plist->head = plist->tail = temp;
	}
	else
	{
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->length++;
}

void poly_add(ListHeader* plist1, ListHeader* plist2, ListHeader* plist3)
{
	ListNode* a = plist1->head; // A 다항식
	ListNode* b = plist2->head; // B 다항식
	int sum; // 계수 더한 값 저장할 임시 변수

	while (a && b)
	{
		// 차수가 같을 때
		if (a->expon == b->expon)
		{
			sum = a->coef + b->coef;
			if (sum != 0)
				insert_node_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		// A 다항식의 차수가 높을 때
		else if (a->expon > b->expon)
		{
			insert_node_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else
		{
			insert_node_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	while (a)
	{
		insert_node_last(plist3, a->coef, a->expon);
		a = a->link;
	}
	while (b)
	{
		insert_node_last(plist3, b->coef, b->expon);
		b = b->link;
	}
}

void poly_print(ListHeader* plist)
{
	ListNode* p = plist->head;
	while (p)
	{
		printf("%d %d\n", p->coef, p->expon);
		p = p->link;
	}
}

int main(void)
{
	ListHeader list1, list2, list3;
	init(&list1); init(&list2); init(&list3);

	// A 다항식
	insert_node_last(&list1, 3, 6);
	insert_node_last(&list1, 7, 3);
	insert_node_last(&list1, -2, 2);
	insert_node_last(&list1, -9, 0);

	// B 다항식
	insert_node_last(&list2, -2, 6);
	insert_node_last(&list2, -4, 4);
	insert_node_last(&list2, 6, 2);
	insert_node_last(&list2, 6, 1);
	insert_node_last(&list2, 1, 0);

	poly_add(&list1, &list2, &list3);
	poly_print(&list3);
}