/////////////////////////////////////////////////////////////////////////////////////////////////
// 연결리스트로 구현한 스택

#include<stdio.h>
#include<stdlib.h>
typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode* link;
}StackNode;
typedef struct {
    StackNode* top;
}LinkedStackType;

void initialize(LinkedStackType* s)
{
    s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
    return (s->top == NULL);
}
int is_full(LinkedStackType* s)
{
    return 0;
}
void push(LinkedStackType* s, element data)
{
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL)
    {
        printf("memory allocation failed\n");
    }
    else
    {
        temp->data = data;
        temp->link = s->top;
        s->top = temp;
    }
}
void printStack(LinkedStackType* s)
{
    StackNode* temp = s->top;

    for (; temp; temp = temp->link)
    {
        printf("|(%3d)|\n", temp->data);
    }
    printf("---------");
}
element pop(LinkedStackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else
    {
        StackNode* temp = s->top;
        int data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;
    }
}

void clear(LinkedStackType* s)
{
    StackNode* temp = s->top;
    StackNode* removed;
    while (temp)
    {
        removed = temp;
        temp = temp->link;
        printf("removed ->data = %d\n", removed->data);
        free(removed);
    }
    s->top = temp;
}

element peek(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else
        return s->top->data;
}
int main(void)
{
    LinkedStackType s;
    initialize(&s);
    push(&s, 15);
    push(&s, 62);
    push(&s, 35);
    push(&s, 52);
    push(&s, 37);
    push(&s, 55);
    printf("\n-- 출력 --\n");
    printStack(&s);

    printf("\n-- 클리어 --\n");
    clear(&s);
    printf("\n-- 출력 --\n");
    printStack(&s);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
// 중위표기식 후위표기식

#include<stdio.h>
#include<stdlib.h>
typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode* link;
}StackNode;
typedef struct {
    StackNode* top;
}LinkedStackType;

void initialize(LinkedStackType* s)
{
    s->top = NULL;
}

int isEmpty(LinkedStackType* s)
{
    return (s->top == NULL);
}
int is_full(LinkedStackType* s)
{
    return 0;
}
void push(LinkedStackType* s, element data)
{
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL)
    {
        printf("memory allocation failed\n");
    }
    else
    {
        temp->data = data;
        temp->link = s->top;
        s->top = temp;
    }
}
int peek(LinkedStackType* s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
    }
    else
    {
        return (s->top)->data;
    }
}
void printStack(LinkedStackType* s)
{
    StackNode* temp = s->top;

    for (; temp; temp = temp->link)
    {
        printf("|(%3d)|\n", temp->data);
    }
    printf("---------");
}
int pop(LinkedStackType* s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else
    {
        StackNode* temp = s->top;
        int data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;
    }
}

void clear(LinkedStackType* s)
{
    StackNode* temp = s->top;
    StackNode* removed;
    while (temp)
    {
        removed = temp;
        temp = temp->link;
        printf("removed ->data = %d\n", removed->data);
        free(removed);
    }
    s->top = temp;
}
int prec(int op)
{
    switch (op)
    {
    case'(':
    case')':
        return 0;
    case'+':
    case'-':
        return 1;
    case'*':
    case'/':
        return 2;
    }
}
void infix_to_postfix(char exp[], char* inpost)
{
    LinkedStackType* s;
    int cnt = 0;
    int len = strlen(exp);
    char ch, top_op;
    int i;
    initialize(&s);

    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        switch (ch)

        {
        case'+':
        case'-':
        case '*':
        case '/':
            while (!isEmpty(&s) && (prec(ch) <= prec(peek(&s))))
            {
                inpost[cnt++] = pop(&s);
            }
            push(&s, ch);
            break;
        case '(':
            push(&s, ch);
            break;
        case ')':
            top_op = pop(&s);
            //왼쪽 괄호를 만날때까지 출력 
            while (top_op != '(') {
                inpost[cnt++] = top_op;
                top_op = pop(&s);
            }
            break;
        default: //피연산자 
            inpost[cnt++] = ch;
            break;
        } //end of switch 
    } //end of for 

    while (!isEmpty(&s))
    {
        inpost[cnt++] = pop(&s);
    }
}
int eval(char exp[])
{
    LinkedStackType s;
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;

    initialize(&s);
    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            //피연산자면 
            value = ch - '0';
            push(&s, value);
        }
        else {
            //연산자의 경우 필요한 피연산자 2개 pop()
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch)
            {
            case'+':
                push(&s, op1 + op2);
                break;
            case'-':
                push(&s, op1 - op2);
                break;
            case'*':
                push(&s, op1 * op2);
                break;
            case'/':
                push(&s, op1 / op2);
                break;
            } //end of else

        }//end of for 
    }
    return pop(&s);
}
int main(void)
{
    char buf[] = "(2+3)*4+9";
    char buf2[1024] = { 0 };
    printf("중위표기식: %s\n", buf);
    infix_to_postfix(buf, buf2);
    printf("후위표기식: %s\n", buf2);

    printf("후위표기식 결과: %d\n", eval(buf2));


    return 0;
}

////////////////////////////////////////////////////////////////////////////
// 연결된 큐

#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode* link;
}QueueNode;

typedef struct {
    QueueNode* front, * rear;
}LinkedQueueType;

void init(LinkedQueueType* q)
{
    q->front = q->rear = 0;
}
int is_empty(LinkedQueueType* q)
{
    return (q->front == NULL);
}
int is_full(LinkedQueueType* q)
{
    return 0;
}
int enqueue(LinkedQueueType* q, element data)
{
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = data;
    temp->link = NULL;
    if (is_empty(q))
    {
        q->front = temp;
        q->rear = temp;

    }
    else
    {
        q->rear->link = temp;
        q->rear = temp;
    }
}

int dequeue(LinkedQueueType* q)
{
    QueueNode* temp = q->front;
    element data;
    if (is_empty(q))
    {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        data = temp->data;
        q->front = q->front->link;
        if (q->front == NULL)
            q->rear = NULL;
        free(temp);
        return data;
    }

}
void print_queue(LinkedQueueType* q)
{
    QueueNode* p;
    for (p = q->front; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}
int main(void)
{
    LinkedQueueType queue;
    init(&queue);

    enqueue(&queue, 1); print_queue(&queue);
    enqueue(&queue, 2); print_queue(&queue);
    enqueue(&queue, 3); print_queue(&queue);
    dequeue(&queue); print_queue(&queue);
    dequeue(&queue); print_queue(&queue);
    dequeue(&queue); print_queue(&queue);
    return 0;
}