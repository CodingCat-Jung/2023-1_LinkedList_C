// 14���� �ڷᱸ�� �ǽ� 20204026 ������
// ������ �÷��̸���Ʈ ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// �ִ� �뷮�� 128MB
#define MAX 128
// �� ���� �뷮�� 4MB
#define SONGSIZE 4

#define TRUE 1
#define FALSE 0

#define NORMAL 0
#define FIRST 1

typedef struct ListNode {
	char* title;
	char* singer;
	struct ListNode* next; // rlink
	struct ListNode* previous; // llink
}ListNode;

typedef struct PlayList {
	ListNode* play; // ���� ��� ���� ��
	ListNode* first; // ù ��° �� (== *head)
	int listSize; // ������� ���
}PlayList;

// ���� ���� ����Ʈ �ʱ�ȭ �Լ�
void initList(PlayList* list) 
{
	printf("list init completed\n");

	list->first = NULL;
	list->play = NULL;
	list->listSize = 0;
}

// ����Ʈ ���
void printList(PlayList* list)
{
	ListNode* temp;
	temp = list->first;

	int num = 1;

	if (isEmpty(list)) {
		printf("PlayList is empty!!\n");
		return;
	}
	else {
		printf("Now Playing : %s / %s\n", list->play->singer, list->play->title);

		do {
			printf("--------------------------------------\n");
			printf("%d. %s / %s\n", num, temp->singer, temp->title);
			temp = temp->next;
			num++;
		} while (temp != NULL);
		printf("--------------------------------------\n");
	}
}

// ���� ���� �˻�
int isEmpty(PlayList* list)
{
	if (list->listSize == 0) return TRUE;
	else return FALSE;
}

// ��ȭ ���� �˻�
int isFull(PlayList* list)
{
	if (list->listSize * SONGSIZE >= MAX) return TRUE;
	else return FALSE;
}

void insertMusicSub(PlayList* list, ListNode* node)
{
	if (isFull(list)) {
		printf("iPod is Full!!\n");
		return;
	}
	else {
		// ����Ʈ�� ����ִ� ���, ù ��
		if (isEmpty(list)) {

			list->first = node;
			list->play = node;

			node->next = NULL;
			node->previous = NULL;
		}

		// ����Ʈ�� ���� ���� �� �߰�
		else if (list->play->next == NULL) {

			node->next = NULL;
			node->previous = list->play;
			list->play->next = node;
			// �߰��� ���� ���� ��� ������ �ֽ�ȭ
			// list->play = list->play->next;
		}

		// ����Ʈ�� Ư�� ��ġ�� �� �߰�
		else {
			node->next = list->play->next;
			list->play->next->previous = node;
			list->play->next = node;
			node->previous = list->play;
			// list->play = list->play->next;
		}// end of else

		list->listSize++;

	}//end of else

}

void insertMusicFirstSub(PlayList* list, ListNode* node)
{
	if (isFull(list)) {
		printf("iPod is Full!!\n");
		return;
	}
	else {
		// ����Ʈ�� ����ִ� ���
		if (isEmpty(list)) {
			list->first = node;
			list->play = node;
			node->next = NULL;
			node->previous = NULL;
		}
		else {
			list->first->previous = node;
			node->next = list->first;
			node->previous = NULL;
			list->first = node;
		}

		list->listSize++;
	}
}

// ����� ����
void deleteMusic(PlayList* list)
{
	if (isEmpty(list)) {
		printf("iPod is empty!!\n");
		return;
	}
	else {
		ListNode* deletedSong = list->play;

		// ������ ���� ù ��° ���� ���
		if (list->play == list->first) {
			list->first = list->play->next;
		}

		// ������ ���� ���� ��� ���� �� ����
		if (list->play->previous != NULL) {
			list->play->previous->next = list->play->next;
		}
		if (list->play->next != NULL) {
			list->play->next->previous = list->play->previous;
		}

		// ���� ������ �̵�
		if (list->play->next != NULL) {
			list->play = list->play->next;
		}
		else {
			list->play = list->first;
		}

		free(deletedSong);
		list->listSize--;
	}
}

// mode= = NORMAL(����� ����), FIRST(����Ʈ ó��)
void insertMusic(PlayList* list, int mode)
{
	ListNode* tempNode;
	tempNode = (ListNode*)malloc(sizeof(ListNode));
	tempNode->singer = (char*)malloc(sizeof(char) * 512);
	tempNode->title = (char*)malloc(sizeof(char) * 512);

	printf("������ : ");
	gets(tempNode->singer);
	printf("��� : ");
	gets(tempNode->title);

	if (mode == NORMAL)
		insertMusicSub(list, tempNode);
	else if (mode == FIRST)
		insertMusicFirstSub(list, tempNode);
}


// ���� ������ �̵�
void movePrev(PlayList* list)
{
	if (isEmpty(list)) {
		printf("PlayList is empty!! Can't move previous\n");
		return;
	}
	else {
		// ����Ʈ�� ��尡 1�� �ۿ� ���ų�, ���� ù ���� ���
		if ((list->listSize == 1) || (list->play == list->first)) {
			printf("���� ������ �̵��� �� �����ϴ�.\n");
			return;
		}
		else {
			list->play = list->play->previous;
		}
	}
}

// ���� ������ �̵�
void moveNext(PlayList* list)
{
	if (isEmpty(list)) {
		printf("PlayList is empty!! Can't move next\n");
		return;
	}
	else {
		// ����Ʈ�� ��尡 1�� �ۿ� ���ų�, ���� ������ ���� ���
		if ((list->listSize == 1) || (list->play->next == NULL)) {
			printf("���� ������ �̵��� �� �����ϴ�.\n");
			return;
		}
		else {
			list->play = list->play->next;
		}
	}
}

int main() {

	PlayList list; // �÷��̸���Ʈ
	char cmd; // ����� ��ɾ�

	initList(&list);

	do {
		printf("\n");
		printf("+ : MP3 ����� ������ �߰� \n");
		printf("s : MP3 ����Ʈ ó���� �߰� \n");
		printf("- : MP3 ����� ���� \n");
		printf("p : ������ \n");
		printf("n : ������ \n");
		printf("f : �뷮üũ \n");
		printf("e : ����Ʈ ����ִ��� üũ \n");
		printf("q : ���� \n\n");

		// ����Ʈ ���
		printList(&list);

		printf("��ɾ� �Է� : ");
		cmd = getchar();
		getchar(); // newline handing

		switch (cmd)
		{
		case'+':
			insertMusic(&list, NORMAL);
			break;

		case '-':
			deleteMusic(&list);
			break;

		case's':
		case'S':
			insertMusic(&list, FIRST);
			break;

		case'p':
		case'P':
			movePrev(&list);
			break;

		case'n':
		case'N':
			moveNext(&list);
			break;

		case'f':
		case'F':
			if (isFull(&list)) {
				printf("iPod is FULL!!\n");
			}
			else {
				printf("�뷮 : %d\n", list.listSize);
			}
			break;

		case'e':
		case'E':
			if (isEmpty(&list))
				printf("iPod is EMPTY!!\n");
			else
				printf("�뷮 : %d\n", list.listSize);
			break;

		case'q':
		case'Q':
			break;

		default:
			printf("��ɾ� ����\n");
		}

	} while (cmd != 'Q');

	return 0;
}