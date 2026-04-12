#include <stdio.h>

// 이미 열린 FD에 버퍼링된 FILE* 스트림 추가
int fd = fileno(stdout);     // FD 번호 추출
FILE* fp = fdopen(fd, "w");  // FILE*로 래핑

fprintf(fp, "래핑된 스트림\n");
fclose(fp);
