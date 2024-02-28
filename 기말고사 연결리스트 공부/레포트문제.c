// 자료구조 13주차 이론 리포트 문제
// 20204026 정명훈 

// 다음 실행 결과와 같이 연결리스트로 구현된 리스트에 학번(정수),이름(문자열),국어(정수)
// 영어(정수),수학(정수),총점(정수),평균(실수)의 값을 저장하고 출력할 수 있게 하여라
// 또한 최고점수를 찾아 출력할 수 있도록 하라.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#pragma warning (disable :4996)

// 정보 저장할 구조체
typedef struct {
	int num; // 학번
	char name[50]; // 이름
	int korea; // 국어 점수
	int english; // 영어 점수
	int math; // 수학 점수
	int total; // 총점
	float average; // 평균
}stu;

// 단순 연결리스트 구조체 선언 (자기 참조 구조체)
typedef struct {
	stu data; // data 필드 (stu 구조체를 저장)
	struct ListNode* link; // link 필드 (자기 자신을 참조하는 포인터 : ListNode를 가리키는 포인터로서 다음 노드의 주소가 저장)
}ListNode;

// 연결리스트 삽입 함수
// stu 구조체 data를 매개변수로 받아 p노드에 저장하고 p노드를 head앞에 연결하고 head를 p로 변경
ListNode* insert(ListNode* head, stu data)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //동적 메모리 할당을 이용해서 새로운 노드 p를 생성

	p->data.num = data.num;
	strcpy(p->data.name, data.name);
	p->data.korea = data.korea;
	p->data.english = data.english;
	p->data.math = data.math;
	p->data.total = data.total;
	p->data.average = data.average;

	p->link = head; // p의 link를 head에 연결 (head앞에 p를 생성)
	head = p; //헤드 포인터 변경
	return head;
}

void print_list(ListNode* head)
{
	printf(":========:======:====:====:====:=====:======:\n");
	printf(":  학번  : 이름 :국어:영어:수학: 총점: 평균 :\n");
	printf(":========:======:====:====:====:=====:======:\n");

	for (ListNode* p = head; p != NULL; p = p->link) {
		printf(":%d:%s:%d:%d:%d:%d:%f:\n", p->data.num, p->data.name, p->data.korea, p->data.english,
			p->data.math, p->data.total, p->data.average);
	}
	printf(":========:======:====:====:====:=====:======:\n\n");
}

void total_max(ListNode* head) {

	stu temp; // 비교 과정에서 더 큰 데이터 임시 보관 장소

	for (ListNode* p = head; p->link != NULL; p = p->link)
	{
		for (ListNode* q = p->link; q != NULL; q = q->link) //p->link가 null이 아니어야함
		{
			// p 노드의 stu 데이터의 총점이 q 노드보다 클 경우
			if (p->data.total > q->data.total)
			{
				// stu 구조체 temp에 p의 toal 저장
				temp.total = p->data.total;

				// stu 구조체 temp에 p의 학번 저장
				temp.num = p->data.num;

				// stu 구조체 temp에 p의 이름 저장
				strcpy(temp.name, p->data.name);

				// stu 구조체 temp에 p의 국어점수 저장
				temp.korea = p->data.korea;

				// stu 구조체 temp에 p의 영어점수 저장
				temp.english = p->data.english;

				// stu 구조체 temp에 p의 수학점수 저장
				temp.math = p->data.math;

				// stu 구조체 temp에 p의 평균 저장
				temp.average = p->data.average;

			}
		}
	}
	printf(":========:======:====:====:====:=====:======:\n");
	printf(":  학번  : 이름 :국어:영어:수학: 총점: 평균 :\n");
	printf(":========:======:====:====:====:=====:======:\n");

	printf(":%d:%s: %d : %d : %d :  %d: %.2f:\n", temp.num, temp.name, temp.korea, temp.english,
		temp.math, temp.total, temp.average);
	printf(":========:======:====:====:====:=====:======:\n\n");
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;

	removed = head; // 헤드 포인터 값을 removed에 복사
	head = removed->link; // 헤드 포인터 값을 head->link값으로 변경 (head 다음 노드의 값)
	free(removed); // removed 제거
	return head;
}

int main() {
	// 1. 파일 오픈
	FILE* fp = fopen("data.txt", "r"); // 파일 포인터 fp를 이용해 data.txt 파일을 읽기 모드로 오픈
	if (fp == NULL) return;

	// 2. 연결리스트로 구현된 리스트에 정보 읽어들여 저장
	ListNode* head = NULL; // 헤드 포인터 정의 (연결리스트 생성)

	char tem_name[50]; // 이름 받아 놓을 배열 선언
	stu tem; // stu 구조체 타입의 tem 선언

	printf(":========:======:====:====:====:=====:======:\n");
	printf(":  학번  : 이름 :국어:영어:수학: 총점: 평균 :\n");
	printf(":========:======:====:====:====:=====:======:\n");

	while (!feof(fp)) {
		fscanf(fp, "%d %s %d %d %d", &tem.num, tem_name, &tem.korea, &tem.english, &tem.math);
		strcpy(tem.name, tem_name);

		// 3. 총점, 평균 값 구해서 저장
		tem.total = tem.korea + tem.english + tem.math;
		tem.average = (float)tem.total / 3.0;

		head = insert(head, tem); // 연결리스트 head에 stu 구조체 tem에 저장해놓은 내용들 전달

		// 4. 출력 - 현재 tem에 저장한 내용들 
		printf(":%d:%s: %d : %d : %d :  %d: %.2f:\n", tem.num, tem.name, tem.korea, tem.english,
			tem.math, tem.total, tem.average);
	}
	printf(":========:======:====:====:====:=====:======:\n\n");

	// 5. 최고점수 구해서 출력
	printf("최고점수는?\n");
	total_max(head);

	// 6. 삭제 후 출력
	printf("삭제된 후 출력\n");
	delete_first(head);
	head = NULL;
	print_list(head);

	fclose(fp);
	return 0;
}