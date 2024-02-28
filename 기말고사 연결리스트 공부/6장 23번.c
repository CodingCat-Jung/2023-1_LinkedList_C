// 단순 연결 리스트를 이용하여 숫자들을 항상 오름차순으로 정렬된 상태로 유지하는 리스트 SortedList를 구현하여 보라.
// 앞의 문제의 연산들을 구현하면 된다.

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
    int length;
} SortedList;

void initList(SortedList* list) {
    list->head = NULL;
    list->length = 0;
}

ListNode* createNode(element data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(SortedList* list, element item) {
    ListNode* newNode = createNode(item);
    if (newNode == NULL) {
        return;
    }

    ListNode* current = list->head;
    ListNode* previous = NULL;

    // 오름차순으로 정렬된 위치를 찾아 삽입
    while (current != NULL && current->data < item) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        // 리스트가 비어있거나 item이 가장 작은 값인 경우
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        newNode->next = previous->next;
        previous->next = newNode;
    }

    list->length++;
}

void delete(SortedList* list, element item) {
    ListNode* current = list->head;
    ListNode* previous = NULL;

    // 삭제할 노드 탐색
    while (current != NULL && current->data != item) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Item not found in the list\n");
        return;
    }

    if (previous == NULL) {
        // 삭제할 노드가 첫 번째 노드인 경우
        list->head = current->next;
    }
    else {
        previous->next = current->next;
    }

    free(current);
    list->length--;
}

void clear(SortedList* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->length = 0;
}

int is_in_list(SortedList* list, element item) {
    ListNode* current = list->head;
    while (current != NULL) {
        if (current->data == item) {
            return 1;  // item이 리스트 안에 존재함
        }
        current = current->next;
    }
    return 0;  // item이 리스트 안에 존재하지 않음
}

int get_length(SortedList* list) {
    return list->length;
}

int is_empty(SortedList* list) {
    return (list->length == 0);
}

int is_full(SortedList* list) {
    return 0;  // 단순 연결 리스트는 크기 제한이 없으므로 항상 false 반환
}

void display(SortedList* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    SortedList list;
    initList(&list);

    // 리스트에 요소 추가
    insert(&list, 5);
    insert(&list, 2);
    insert(&list, 8);
    insert(&list, 1);
    insert(&list, 4);

    // 리스트 출력
    printf("List: ");
    display(&list);  // 1 2 4 5 8

    // 리스트에서 요소 제거
    delete(&list, 2);
    delete(&list, 5);

    // 리스트 출력
    printf("List: ");
    display(&list);  // 1 4 8

    // 리스트의 길이 출력
    printf("List Length: %d\n", get_length(&list));  // 3

    // 리스트가 비어있는지 검사
    printf("Is Empty: %d\n", is_empty(&list));  // 0 (false)

    // 리스트가 꽉 찼는지 검사
    printf("Is Full: %d\n", is_full(&list));  // 0 (false)

    // 리스트의 모든 요소 제거
    clear(&list);

    // 리스트가 비어있는지 검사
    printf("Is Empty: %d\n", is_empty(&list));  // 1 (true)

    return 0;
}
