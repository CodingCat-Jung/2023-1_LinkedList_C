// 다항식을 연결 리스트로 표현할 수 있음을 보였다. 다항식이 연결 리스트로 표현되어 있고, p를 다항식을 가리키는 포인터라고 할 때, 
// 어떤 실수 x에 대하여 이 다항식의 값을 계산하는 함수 poly_eval을 작성하라. 
// 즉 다항식이 x^3 + 2x +6이고 x=2이면 2^3 + 2*2 + 6를 계산하는 함수를 작성하여보라.

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

// 다항식 리스트 생성
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// 노드 삽입
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp =
		(ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL) error("메모리 할당 에러");

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

// 다항식 계산
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

	// 다항식 1을 생성 
	insert_last(list, 3, 2);
	insert_last(list, 2, 1);
	insert_last(list, 1, 0);

	poly_print(list);

	printf("미지수 x의 값 : ");
	scanf_s("%d", &x);

	printf("다항식의 값 = %d", poly_eval(list, x));
	free(list);
}

