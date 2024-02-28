// 14주차 자료구조 실습 20204026 정명훈
// 아이팟 플레이리스트 구현

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 최대 용량은 128MB
#define MAX 128
// 한 곡의 용량은 4MB
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
	ListNode* play; // 현재 재생 중인 곡
	ListNode* first; // 첫 번째 곡 (== *head)
	int listSize; // 사용중인 곡수
}PlayList;

// 이중 연결 리스트 초기화 함수
void initList(PlayList* list) 
{
	printf("list init completed\n");

	list->first = NULL;
	list->play = NULL;
	list->listSize = 0;
}

// 리스트 출력
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

// 공백 상태 검사
int isEmpty(PlayList* list)
{
	if (list->listSize == 0) return TRUE;
	else return FALSE;
}

// 포화 상태 검사
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
		// 리스트가 비어있는 경우, 첫 곡
		if (isEmpty(list)) {

			list->first = node;
			list->play = node;

			node->next = NULL;
			node->previous = NULL;
		}

		// 리스트의 가장 끝에 곡 추가
		else if (list->play->next == NULL) {

			node->next = NULL;
			node->previous = list->play;
			list->play->next = node;
			// 추가한 곡을 현재 재생 곡으로 최신화
			// list->play = list->play->next;
		}

		// 리스트의 특정 위치에 곡 추가
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
		// 리스트가 비어있는 경우
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

// 현재곡 삭제
void deleteMusic(PlayList* list)
{
	if (isEmpty(list)) {
		printf("iPod is empty!!\n");
		return;
	}
	else {
		ListNode* deletedSong = list->play;

		// 삭제할 곡이 첫 번째 곡인 경우
		if (list->play == list->first) {
			list->first = list->play->next;
		}

		// 삭제할 곡의 이전 곡과 다음 곡 연결
		if (list->play->previous != NULL) {
			list->play->previous->next = list->play->next;
		}
		if (list->play->next != NULL) {
			list->play->next->previous = list->play->previous;
		}

		// 다음 곡으로 이동
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

// mode= = NORMAL(현재곡 다음), FIRST(리스트 처음)
void insertMusic(PlayList* list, int mode)
{
	ListNode* tempNode;
	tempNode = (ListNode*)malloc(sizeof(ListNode));
	tempNode->singer = (char*)malloc(sizeof(char) * 512);
	tempNode->title = (char*)malloc(sizeof(char) * 512);

	printf("가수명 : ");
	gets(tempNode->singer);
	printf("곡명 : ");
	gets(tempNode->title);

	if (mode == NORMAL)
		insertMusicSub(list, tempNode);
	else if (mode == FIRST)
		insertMusicFirstSub(list, tempNode);
}


// 이전 곡으로 이동
void movePrev(PlayList* list)
{
	if (isEmpty(list)) {
		printf("PlayList is empty!! Can't move previous\n");
		return;
	}
	else {
		// 리스트에 노드가 1개 밖에 없거나, 가장 첫 곡인 경우
		if ((list->listSize == 1) || (list->play == list->first)) {
			printf("이전 곡으로 이동할 수 없습니다.\n");
			return;
		}
		else {
			list->play = list->play->previous;
		}
	}
}

// 다음 곡으로 이동
void moveNext(PlayList* list)
{
	if (isEmpty(list)) {
		printf("PlayList is empty!! Can't move next\n");
		return;
	}
	else {
		// 리스트에 노드가 1개 밖에 없거나, 가장 마지막 곡인 경우
		if ((list->listSize == 1) || (list->play->next == NULL)) {
			printf("다음 곡으로 이동할 수 없습니다.\n");
			return;
		}
		else {
			list->play = list->play->next;
		}
	}
}

int main() {

	PlayList list; // 플레이리스트
	char cmd; // 사용자 명령어

	initList(&list);

	do {
		printf("\n");
		printf("+ : MP3 현재곡 다음에 추가 \n");
		printf("s : MP3 리스트 처음에 추가 \n");
		printf("- : MP3 현재곡 삭제 \n");
		printf("p : 이전곡 \n");
		printf("n : 다음곡 \n");
		printf("f : 용량체크 \n");
		printf("e : 리스트 비어있는지 체크 \n");
		printf("q : 종료 \n\n");

		// 리스트 출력
		printList(&list);

		printf("명령어 입력 : ");
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
				printf("용량 : %d\n", list.listSize);
			}
			break;

		case'e':
		case'E':
			if (isEmpty(&list))
				printf("iPod is EMPTY!!\n");
			else
				printf("용량 : %d\n", list.listSize);
			break;

		case'q':
		case'Q':
			break;

		default:
			printf("명령어 오류\n");
		}

	} while (cmd != 'Q');

	return 0;
}