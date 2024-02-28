// �ܼ� ���� ����Ʈ�� �̿��Ͽ� ���ڵ��� �׻� ������������ ���ĵ� ���·� �����ϴ� ����Ʈ SortedList�� �����Ͽ� ����.
// ���� ������ ������� �����ϸ� �ȴ�.

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

    // ������������ ���ĵ� ��ġ�� ã�� ����
    while (current != NULL && current->data < item) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        // ����Ʈ�� ����ְų� item�� ���� ���� ���� ���
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

    // ������ ��� Ž��
    while (current != NULL && current->data != item) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Item not found in the list\n");
        return;
    }

    if (previous == NULL) {
        // ������ ��尡 ù ��° ����� ���
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
            return 1;  // item�� ����Ʈ �ȿ� ������
        }
        current = current->next;
    }
    return 0;  // item�� ����Ʈ �ȿ� �������� ����
}

int get_length(SortedList* list) {
    return list->length;
}

int is_empty(SortedList* list) {
    return (list->length == 0);
}

int is_full(SortedList* list) {
    return 0;  // �ܼ� ���� ����Ʈ�� ũ�� ������ �����Ƿ� �׻� false ��ȯ
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

    // ����Ʈ�� ��� �߰�
    insert(&list, 5);
    insert(&list, 2);
    insert(&list, 8);
    insert(&list, 1);
    insert(&list, 4);

    // ����Ʈ ���
    printf("List: ");
    display(&list);  // 1 2 4 5 8

    // ����Ʈ���� ��� ����
    delete(&list, 2);
    delete(&list, 5);

    // ����Ʈ ���
    printf("List: ");
    display(&list);  // 1 4 8

    // ����Ʈ�� ���� ���
    printf("List Length: %d\n", get_length(&list));  // 3

    // ����Ʈ�� ����ִ��� �˻�
    printf("Is Empty: %d\n", is_empty(&list));  // 0 (false)

    // ����Ʈ�� �� á���� �˻�
    printf("Is Full: %d\n", is_full(&list));  // 0 (false)

    // ����Ʈ�� ��� ��� ����
    clear(&list);

    // ����Ʈ�� ����ִ��� �˻�
    printf("Is Empty: %d\n", is_empty(&list));  // 1 (true)

    return 0;
}
