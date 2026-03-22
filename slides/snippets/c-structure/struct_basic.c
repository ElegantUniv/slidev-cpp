#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    // 순서대로 초기화
    struct Point p1 = {3, 4};

    // 지정 초기화 (C99)
    struct Point p2 = {.x = 10, .y = 20};

    printf("p1: (%d, %d)\n", p1.x, p1.y);
    printf("p2: (%d, %d)\n", p2.x, p2.y);

    // 멤버 접근 및 수정
    p1.x = 100;
    printf("p1 수정 후: (%d, %d)\n", p1.x, p1.y);

    return 0;
}
