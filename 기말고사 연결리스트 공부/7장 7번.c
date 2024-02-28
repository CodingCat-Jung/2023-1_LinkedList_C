// 이중 연결 리스트에서 특정한 값을 탐색하는 함수 search()를 작성
// 이중 연결 리스트 L에서 data를 가지고 있는 노드를 찾아서 반환

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DListNode {
    element data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

DListNode* search(DListNode* L, element data) {
    DListNode* current = L;

    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }

    return NULL; // 데이터를 찾지 못한 경우 NULL 반환
}

int main() {
    // 이중 연결 리스트 생성 및 데이터 추가
    DListNode* head = NULL;
    DListNode* tail = NULL;

    for (int i = 1; i <= 5; i++) {
        DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
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

    // 특정 값 탐색하여 해당 노드 반환
    int searchData = 3;
    DListNode* result = search(head, searchData);

    if (result != NULL) {
        printf("Found: %d\n", result->data);
    }
    else {
        printf("Not Found\n");
    }

    // 이중 연결 리스트 메모리 해제
    DListNode* current = head;
    while (current != NULL) {
        DListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
