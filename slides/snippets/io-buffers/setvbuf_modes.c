#include <stdio.h>

// 프로그램 시작 직후, 첫 I/O 전에 호출
int main() {
    // stdout을 강제로 언버퍼드로
    setvbuf(stdout, NULL, _IONBF, 0);

    // stdout을 라인 버퍼링으로
    setvbuf(stdout, NULL, _IOLBF, 0);

    // stdout을 풀 버퍼링으로 (버퍼 크기 지정)
    setvbuf(stdout, NULL, _IOFBF, 4096);
}
