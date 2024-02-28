// ���� ���� ����Ʈ �������� ��ȸ�ϸ鼭 ����� ������ ���� ����϶�

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

    // ������ ��带 ã�� ���� ������ �̵�
    while (current->next != NULL) {
        current = current->next;
    }

    // ������ ������ �������� ���
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }

    printf("\n");
}

int main() {
    // ���� ���� ����Ʈ ���� �� ������ �߰�
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

    // ���� ���� ����Ʈ�� �������� ���
    printf("Reversed List: ");
    printReverseList(head);

    // ���� ���� ����Ʈ �޸� ����
    ListNode* current = head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
