// 자료구조 중간고사 1번문제 해결 코드
// 데이터 파일에 있는 점의 좌표를 읽어와서 사분면 출력하는 프로그램
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

// Point p를 사용하여 사분면 위치 출력 함수
void print_quadrant(Point p) {
    if (p.x > 0 && p.y > 0)
        printf("Point (%d, %d) 1사분면에 위치함.\n", p.x, p.y);
    else if (p.x < 0 && p.y > 0)
        printf("Point (%d, %d) 2사분면에 위치함.\n", p.x, p.y);
    else if (p.x < 0 && p.y < 0)
        printf("Point (%d, %d) 3사분면에 위치함.\n", p.x, p.y);
    else if (p.x > 0 && p.y < 0)
        printf("Point (%d, %d) 4사분면에 위치함.\n", p.x, p.y);
    else if (p.x == 0 && p.y != 0)
        printf("Point (%d, %d) y선 위에 위치함.\n", p.x, p.y);
    else if (p.y == 0 && p.x != 0)
        printf("Point (%d, %d) x선 위에 위치함.\n", p.x, p.y);
    else
        printf("Point (%d, %d) 원점.\n", p.x, p.y);
}

int main() {
    // 1. 파일 읽기
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file\n");
        return -1;
    }

    // 2. 구조체 변수 선언하고 파일 읽어들여 구조체에 내용 저장 / 출력
    Point p;
    while (fscanf(file, "%d %d", &p.x, &p.y) != EOF) {
        print_quadrant(p);
    }

    fclose(file);
    return 0;
}



//////////////////////////////////////////////////////
// 자료구조 중간고사 1번문제 내 코드 수정본
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
    // 1. 파일 오픈
    FILE* fp = fopen("data.txt", "r");
    if (fp == NULL) return;

    int count = 0;
    dot arr[1024]; // 좌표값 저장할 구조체 배열 선언

    // 파일의 끝까지 반복해서 파일 안에 몇 개의 정보가 있는지 정보의 개수 파악
    while (fscanf(fp, "%d %d", &arr[count].x, &arr[count].y) != EOF) {
        count++;
    }

    // 정보의 개수만큼 반복해서 좌표 사분면 출력
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)는 %d사분면\n", arr[i].x, arr[i].y, check(&arr[i]));
    }

    fclose(fp);
    return 0;
}



//////////////////////////////////////////////////////
// 데이터 파일에 저장되어 있는 학번, 이름, 학점을 읽어와서 출력하는 프로그램

#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

int main() {
    // 1. 파일 읽기
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) return;

    // 2. 구조체 변수 선언하고 , 파일 읽으면서 구조체에 내용 저장함과 동시에 내용 출력
    Student s;
    while (fscanf(file, "%d %s %f", &s.id, s.name, &s.grade) != EOF) {
        printf("%d %s %.2f\n", s.id, s.name, s.grade);
    }

    fclose(file);
    return 0;
}



//////////////////////////////////////////////////////
// 자료구조 5주차 queue4.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int nNum;
    char name[100];
}QueueObject;

// 전역변수로 구조체 배열 선언
QueueObject queue[MAX_QUEUE_SIZE];

// 전역변수로 front와 rear 초기화
int front, rear;

void initilize()
{
    front = rear = 0; // 원형큐 초기화
}

int isEmpty()
{
    return(front == rear);
}

int isFull()
{
    return((rear + 1) % MAX_QUEUE_SIZE == front);
}

// 큐에 내용을 삽입 함수
void addq(QueueObject item)
{
    if (isFull()) {
        printf("queue is full\n");
    }

    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

// 큐에서 내용 삭제하고 반환 함수
QueueObject deleteq()
{
    if (isEmpty()) {
        printf("queue is empty\n");
    }

    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

// 큐에 존재하는 요소의 개수 반환 함수
void get_count(QueueObject item)
{
    int count = 0;

    if (front <= rear) {
        for (int i = front + 1; i <= rear; i++) {
            count++;
        }
    }

    printf("원형큐에 존재하는 요소 개수는 %d\n", count);
}

void main() {
    FILE* fp;

    int nCount;  // 파일에 정보가 몇 개 있는지 저장하기 위한 변수
    QueueObject temp;

    // 파일 오픈
    fp = fopen("data2.txt", "r");
    if (fp == NULL) {
        printf("error\n");
        exit(0);
    }
 
    nCount = 0;

    // 파일 읽어들여서 내용을 큐에 저장
    while (!feof(fp)) {

        // 파일 읽어서 temp에 임시 저장
        fscanf(fp, "%d%s", &temp.nNum, temp.name);

        // 큐에 저장
        addq(temp);

        nCount++;
    }

    printf("front = %d, rear = %d\n", front, rear);

    // 큐에 저장한 것들 출력
    for (int i = 0; i < nCount; i++) {

        // 요소의 개수 출력
        get_count(temp);

        // 큐에서 꺼내서 temp에 임시 저장
        temp = deleteq();

        // temp 내용 출력
        printf("%d | %s\n", temp.nNum, temp.name);
    }

    printf("front = %d, rear = %d\n", front, rear);

    fclose(fp);
}