// 이중 연결 리스트 역순으로 순회하면서 저장된 데이터 값을 출력하라

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

void printReverseList(ListNode* head) {
    ListNode* current = head;

    // 마지막 노드를 찾기 위해 끝까지 이동
    while (current->next != NULL) {
        current = current->next;
    }

    // 마지막 노드부터 역순으로 출력
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }

    printf("\n");
}

int main() {
    // 이중 연결 리스트 생성 및 데이터 추가
    ListNode* head = NULL;
    ListNode* tail = NULL;

    for (int i = 1; i <= 5; i++) {
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = i;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // 이중 연결 리스트를 역순으로 출력
    printf("Reversed List: ");
    printReverseList(head);

    // 이중 연결 리스트 메모리 해제
    ListNode* current = head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
