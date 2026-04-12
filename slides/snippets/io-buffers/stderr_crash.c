#include <stdio.h>

int main() {
    // stdout: 버퍼에 저장
    printf("프로그램 시작...");
    // stderr: 즉시 출력 ✅
    fprintf(stderr, "위험한 작업 시작\n");
    // 여기서 크래시 발생
    int* p = NULL;
    *p = 42;  // 💥
    // printf 내용은 버퍼에 남아 유실됨
    // fprintf(stderr) 내용은 이미 출력됨
}
