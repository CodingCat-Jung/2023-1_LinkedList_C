// �ڷᱸ�� �߰���� 1������ �ذ� �ڵ�
// ������ ���Ͽ� �ִ� ���� ��ǥ�� �о�ͼ� ��и� ����ϴ� ���α׷�
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

// Point p�� ����Ͽ� ��и� ��ġ ��� �Լ�
void print_quadrant(Point p) {
    if (p.x > 0 && p.y > 0)
        printf("Point (%d, %d) 1��и鿡 ��ġ��.\n", p.x, p.y);
    else if (p.x < 0 && p.y > 0)
        printf("Point (%d, %d) 2��и鿡 ��ġ��.\n", p.x, p.y);
    else if (p.x < 0 && p.y < 0)
        printf("Point (%d, %d) 3��и鿡 ��ġ��.\n", p.x, p.y);
    else if (p.x > 0 && p.y < 0)
        printf("Point (%d, %d) 4��и鿡 ��ġ��.\n", p.x, p.y);
    else if (p.x == 0 && p.y != 0)
        printf("Point (%d, %d) y�� ���� ��ġ��.\n", p.x, p.y);
    else if (p.y == 0 && p.x != 0)
        printf("Point (%d, %d) x�� ���� ��ġ��.\n", p.x, p.y);
    else
        printf("Point (%d, %d) ����.\n", p.x, p.y);
}

int main() {
    // 1. ���� �б�
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file\n");
        return -1;
    }

    // 2. ����ü ���� �����ϰ� ���� �о�鿩 ����ü�� ���� ���� / ���
    Point p;
    while (fscanf(file, "%d %d", &p.x, &p.y) != EOF) {
        print_quadrant(p);
    }

    fclose(file);
    return 0;
}



//////////////////////////////////////////////////////
// �ڷᱸ�� �߰���� 1������ �� �ڵ� ������
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} dot;

int check(dot* d)
{
    if (d->x > 0) {
        if (d->y > 0)
            return 1;
        else
            return 4;
    }
    if (d->x < 0) {
        if (d->y > 0)
            return 2;
        else
            return 3;
    }
    return 0;
}

int main() {
    // 1. ���� ����
    FILE* fp = fopen("data.txt", "r");
    if (fp == NULL) return;

    int count = 0;
    dot arr[1024]; // ��ǥ�� ������ ����ü �迭 ����

    // ������ ������ �ݺ��ؼ� ���� �ȿ� �� ���� ������ �ִ��� ������ ���� �ľ�
    while (fscanf(fp, "%d %d", &arr[count].x, &arr[count].y) != EOF) {
        count++;
    }

    // ������ ������ŭ �ݺ��ؼ� ��ǥ ��и� ���
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)�� %d��и�\n", arr[i].x, arr[i].y, check(&arr[i]));
    }

    fclose(fp);
    return 0;
}



//////////////////////////////////////////////////////
// ������ ���Ͽ� ����Ǿ� �ִ� �й�, �̸�, ������ �о�ͼ� ����ϴ� ���α׷�

#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

int main() {
    // 1. ���� �б�
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) return;

    // 2. ����ü ���� �����ϰ� , ���� �����鼭 ����ü�� ���� �����԰� ���ÿ� ���� ���
    Student s;
    while (fscanf(file, "%d %s %f", &s.id, s.name, &s.grade) != EOF) {
        printf("%d %s %.2f\n", s.id, s.name, s.grade);
    }

    fclose(file);
    return 0;
}



//////////////////////////////////////////////////////
// �ڷᱸ�� 5���� queue4.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int nNum;
    char name[100];
}QueueObject;

// ���������� ����ü �迭 ����
QueueObject queue[MAX_QUEUE_SIZE];

// ���������� front�� rear �ʱ�ȭ
int front, rear;

void initilize()
{
    front = rear = 0; // ����ť �ʱ�ȭ
}

int isEmpty()
{
    return(front == rear);
}

int isFull()
{
    return((rear + 1) % MAX_QUEUE_SIZE == front);
}

// ť�� ������ ���� �Լ�
void addq(QueueObject item)
{
    if (isFull()) {
        printf("queue is full\n");
    }

    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

// ť���� ���� �����ϰ� ��ȯ �Լ�
QueueObject deleteq()
{
    if (isEmpty()) {
        printf("queue is empty\n");
    }

    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

// ť�� �����ϴ� ����� ���� ��ȯ �Լ�
void get_count(QueueObject item)
{
    int count = 0;

    if (front <= rear) {
        for (int i = front + 1; i <= rear; i++) {
            count++;
        }
    }

    printf("����ť�� �����ϴ� ��� ������ %d\n", count);
}

void main() {
    FILE* fp;

    int nCount;  // ���Ͽ� ������ �� �� �ִ��� �����ϱ� ���� ����
    QueueObject temp;

    // ���� ����
    fp = fopen("data2.txt", "r");
    if (fp == NULL) {
        printf("error\n");
        exit(0);
    }
 
    nCount = 0;

    // ���� �о�鿩�� ������ ť�� ����
    while (!feof(fp)) {

        // ���� �о temp�� �ӽ� ����
        fscanf(fp, "%d%s", &temp.nNum, temp.name);

        // ť�� ����
        addq(temp);

        nCount++;
    }

    printf("front = %d, rear = %d\n", front, rear);

    // ť�� ������ �͵� ���
    for (int i = 0; i < nCount; i++) {

        // ����� ���� ���
        get_count(temp);

        // ť���� ������ temp�� �ӽ� ����
        temp = deleteq();

        // temp ���� ���
        printf("%d | %s\n", temp.nNum, temp.name);
    }

    printf("front = %d, rear = %d\n", front, rear);

    fclose(fp);
}