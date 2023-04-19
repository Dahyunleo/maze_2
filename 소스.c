#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

// 좌표를 저장하기 위한 구조체
typedef struct {
    short r;
    short c;
} element;

typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

void init(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return s->top == -1;
}

int is_full(StackType* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        exit(1);
    }
    s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        exit(1);
    }
    return s->stack[(s->top)--];
}

element peek(StackType* s) {
    if (is_empty(s)) {
        exit(1);
    }
    return s->stack[s->top];
}

element here = { 1,0 };
element entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1','1','1','1','1'},
        {'e','1','0','1','0','0','0','1','0','1'},
        {'0','0','0','1','0','0','0','1','0','1'},
        {'0','1','0','0','0','1','1','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','0','0','1','0','1','1'},
        {'1','0','1','1','1','0','1','1','0','1'},
        {'1','1','0','0','0','0','0','0','0','x'},
        {'1','1','1','1','1','1','1','1','1','1'}
};

void push_loc(StackType* s, int r, int c) {
    // 배열 범위를 벗어난 r,c는 금지한다.
    if (r < 0 || c < 0 || r > MAZE_SIZE || c > MAZE_SIZE) return;
    // 벽(1)이 아니고, 이미 왔던 곳(.)이 아니다 = 갈 수 있다
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

void print() {
    int i, j;
    for (i = 0; i < MAZE_SIZE; i++) {
        for (j = 0; j < MAZE_SIZE; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int r, c;
    StackType s;

    init(&s);
    here = entry; // entry는 이때 한번만 사용된다
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';

        print();
        printf("------------\n");

        // 스택은 가장 마지막에 넣은 것을 가장 먼저 뽑아준다
        // 그러므로 북-남-서-동 순서로 넣으면
        // 동-서-남-북 의 순서로 나오게 된다
        push_loc(&s, r - 1, c); // north
        push_loc(&s, r + 1, c); // south
        push_loc(&s, r, c - 1); // west
        push_loc(&s, r, c + 1); // east

        if (is_empty(&s)) {
            printf("실패\n");
            exit(1);
        }
        else {
            here = pop(&s);
        }
    }
    printf("성공\n");
    return 0;
}

