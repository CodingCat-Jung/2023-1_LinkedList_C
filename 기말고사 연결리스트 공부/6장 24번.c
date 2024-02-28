// 희소행렬이 많은 항들이 0인 행렬이다.
// 연결리스트를 이용하여 희소 행렬을 표현하는 방법

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int row;
    int col;
    int value;
    struct ListNode* next;
} ListNode;

typedef struct {
    int rows;
    int cols;
    ListNode* head;
} SparseMatrix;

void initMatrix(SparseMatrix* matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->head = NULL;
}

ListNode* createNode(int row, int col, int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertElement(SparseMatrix* matrix, int row, int col, int value) {
    if (value == 0) {
        return;  // 0인 값은 저장하지 않음
    }

    ListNode* newNode = createNode(row, col, value);
    if (newNode == NULL) {
        return;
    }

    if (matrix->head == NULL) {
        matrix->head = newNode;
    }
    else {
        ListNode* current = matrix->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void displayMatrix(SparseMatrix* matrix) {
    ListNode* current = matrix->head;
    for (int row = 0; row < matrix->rows; row++) {
        for (int col = 0; col < matrix->cols; col++) {
            if (current != NULL && current->row == row && current->col == col) {
                printf("%d ", current->value);
                current = current->next;
            }
            else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void freeMatrix(SparseMatrix* matrix) {
    ListNode* current = matrix->head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
    matrix->head = NULL;
}

int main() {
    SparseMatrix matrix;
    int rows, cols;
    int numElements;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    printf("Enter number of non-zero elements: ");
    scanf("%d", &numElements);

    initMatrix(&matrix, rows, cols);

    for (int i = 0; i < numElements; i++) {
        int row, col, value;
        printf("Enter row, column, and value of element %d: ", i + 1);
        scanf("%d %d %d", &row, &col, &value);
        insertElement(&matrix, row, col, value);
    }

    printf("\nSparse Matrix:\n");
    displayMatrix(&matrix);

    freeMatrix(&matrix);

    return 0;
}
