#include <stdio.h>

int main() {
    printf("진행 중...");
    fflush(stdout);     // ← 즉시 화면에 출력
    do_heavy_work();
    printf(" 완료\n");
}

// fflush(NULL) — 모든 출력 스트림 플러시
fflush(NULL);
