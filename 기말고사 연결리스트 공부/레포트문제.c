// �ڷᱸ�� 13���� �̷� ����Ʈ ����
// 20204026 ������ 

// ���� ���� ����� ���� ���Ḯ��Ʈ�� ������ ����Ʈ�� �й�(����),�̸�(���ڿ�),����(����)
// ����(����),����(����),����(����),���(�Ǽ�)�� ���� �����ϰ� ����� �� �ְ� �Ͽ���
// ���� �ְ������� ã�� ����� �� �ֵ��� �϶�.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#pragma warning (disable :4996)

// ���� ������ ����ü
typedef struct {
	int num; // �й�
	char name[50]; // �̸�
	int korea; // ���� ����
	int english; // ���� ����
	int math; // ���� ����
	int total; // ����
	float average; // ���
}stu;

// �ܼ� ���Ḯ��Ʈ ����ü ���� (�ڱ� ���� ����ü)
typedef struct {
	stu data; // data �ʵ� (stu ����ü�� ����)
	struct ListNode* link; // link �ʵ� (�ڱ� �ڽ��� �����ϴ� ������ : ListNode�� ����Ű�� �����ͷμ� ���� ����� �ּҰ� ����)
}ListNode;

// ���Ḯ��Ʈ ���� �Լ�
// stu ����ü data�� �Ű������� �޾� p��忡 �����ϰ� p��带 head�տ� �����ϰ� head�� p�� ����
ListNode* insert(ListNode* head, stu data)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //���� �޸� �Ҵ��� �̿��ؼ� ���ο� ��� p�� ����

	p->data.num = data.num;
	strcpy(p->data.name, data.name);
	p->data.korea = data.korea;
	p->data.english = data.english;
	p->data.math = data.math;
	p->data.total = data.total;
	p->data.average = data.average;

	p->link = head; // p�� link�� head�� ���� (head�տ� p�� ����)
	head = p; //��� ������ ����
	return head;
}

void print_list(ListNode* head)
{
	printf(":========:======:====:====:====:=====:======:\n");
	printf(":  �й�  : �̸� :����:����:����: ����: ��� :\n");
	printf(":========:======:====:====:====:=====:======:\n");

	for (ListNode* p = head; p != NULL; p = p->link) {
		printf(":%d:%s:%d:%d:%d:%d:%f:\n", p->data.num, p->data.name, p->data.korea, p->data.english,
			p->data.math, p->data.total, p->data.average);
	}
	printf(":========:======:====:====:====:=====:======:\n\n");
}

void total_max(ListNode* head) {

	stu temp; // �� �������� �� ū ������ �ӽ� ���� ���

	for (ListNode* p = head; p->link != NULL; p = p->link)
	{
		for (ListNode* q = p->link; q != NULL; q = q->link) //p->link�� null�� �ƴϾ����
		{
			// p ����� stu �������� ������ q ��庸�� Ŭ ���
			if (p->data.total > q->data.total)
			{
				// stu ����ü temp�� p�� toal ����
				temp.total = p->data.total;

				// stu ����ü temp�� p�� �й� ����
				temp.num = p->data.num;

				// stu ����ü temp�� p�� �̸� ����
				strcpy(temp.name, p->data.name);

				// stu ����ü temp�� p�� �������� ����
				temp.korea = p->data.korea;

				// stu ����ü temp�� p�� �������� ����
				temp.english = p->data.english;

				// stu ����ü temp�� p�� �������� ����
				temp.math = p->data.math;

				// stu ����ü temp�� p�� ��� ����
				temp.average = p->data.average;

			}
		}
	}
	printf(":========:======:====:====:====:=====:======:\n");
	printf(":  �й�  : �̸� :����:����:����: ����: ��� :\n");
	printf(":========:======:====:====:====:=====:======:\n");

	printf(":%d:%s: %d : %d : %d :  %d: %.2f:\n", temp.num, temp.name, temp.korea, temp.english,
		temp.math, temp.total, temp.average);
	printf(":========:======:====:====:====:=====:======:\n\n");
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;

	removed = head; // ��� ������ ���� removed�� ����
	head = removed->link; // ��� ������ ���� head->link������ ���� (head ���� ����� ��)
	free(removed); // removed ����
	return head;
}

int main() {
	// 1. ���� ����
	FILE* fp = fopen("data.txt", "r"); // ���� ������ fp�� �̿��� data.txt ������ �б� ���� ����
	if (fp == NULL) return;

	// 2. ���Ḯ��Ʈ�� ������ ����Ʈ�� ���� �о�鿩 ����
	ListNode* head = NULL; // ��� ������ ���� (���Ḯ��Ʈ ����)

	char tem_name[50]; // �̸� �޾� ���� �迭 ����
	stu tem; // stu ����ü Ÿ���� tem ����

	printf(":========:======:====:====:====:=====:======:\n");
	printf(":  �й�  : �̸� :����:����:����: ����: ��� :\n");
	printf(":========:======:====:====:====:=====:======:\n");

	while (!feof(fp)) {
		fscanf(fp, "%d %s %d %d %d", &tem.num, tem_name, &tem.korea, &tem.english, &tem.math);
		strcpy(tem.name, tem_name);

		// 3. ����, ��� �� ���ؼ� ����
		tem.total = tem.korea + tem.english + tem.math;
		tem.average = (float)tem.total / 3.0;

		head = insert(head, tem); // ���Ḯ��Ʈ head�� stu ����ü tem�� �����س��� ����� ����

		// 4. ��� - ���� tem�� ������ ����� 
		printf(":%d:%s: %d : %d : %d :  %d: %.2f:\n", tem.num, tem.name, tem.korea, tem.english,
			tem.math, tem.total, tem.average);
	}
	printf(":========:======:====:====:====:=====:======:\n\n");

	// 5. �ְ����� ���ؼ� ���
	printf("�ְ�������?\n");
	total_max(head);

	// 6. ���� �� ���
	printf("������ �� ���\n");
	delete_first(head);
	head = NULL;
	print_list(head);

	fclose(fp);
	return 0;
}