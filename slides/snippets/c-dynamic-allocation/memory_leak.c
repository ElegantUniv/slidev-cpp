#include <stdio.h>
#include <stdlib.h>

// ❌ 나쁜 예: 메모리 누수
void bad_example() {
    int* p = (int*)malloc(sizeof(int));
    *p = 42;
    // free(p) 호출 누락 → 메모리 누수 발생
}

// ✅ 좋은 예: 올바른 해제
void good_example() {
    int* p = (int*)malloc(sizeof(int));
    if (p == NULL) return;
    *p = 42;
    printf("값: %d\n", *p);
    free(p);   // 반드시 해제
    p = NULL;  // 댕글링 포인터 방지
}

int main() {
    bad_example();   // 누수 발생
    good_example();  // 정상
    return 0;
}
