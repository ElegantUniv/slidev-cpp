#include <stdio.h>

// stdout을 파일로 전환
freopen("out.txt", "w", stdout);
printf("이제 out.txt에 기록됨\n");   // ✅

// stderr를 파일로 전환
freopen("error.txt", "w", stderr);
fprintf(stderr, "에러 → error.txt\n");

// 원래 터미널로 되돌리기 (플랫폼 의존)
// → 일반적으로 freopen 후에는 되돌리지 않는 것이 관례
