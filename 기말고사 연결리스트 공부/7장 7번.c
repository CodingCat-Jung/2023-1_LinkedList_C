// ���� ���� ����Ʈ���� Ư���� ���� Ž���ϴ� �Լ� search()�� �ۼ�
// ���� ���� ����Ʈ L���� data�� ������ �ִ� ��带 ã�Ƽ� ��ȯ

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

    return NULL; // �����͸� ã�� ���� ��� NULL ��ȯ
}

int main() {
    // ���� ���� ����Ʈ ���� �� ������ �߰�
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

    // Ư�� �� Ž���Ͽ� �ش� ��� ��ȯ
    int searchData = 3;
    DListNode* result = search(head, searchData);

    if (result != NULL) {
        printf("Found: %d\n", result->data);
    }
    else {
        printf("Not Found\n");
    }

    // ���� ���� ����Ʈ �޸� ����
    DListNode* current = head;
    while (current != NULL) {
        DListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
