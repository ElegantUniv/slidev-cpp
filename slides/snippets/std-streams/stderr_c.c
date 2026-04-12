#include <stdio.h>
#include <errno.h>   // errno
#include <string.h>  // strerror

int main(void) {
    FILE* fp = fopen("없는파일.txt", "r");
    if (fp == NULL) {
        // fprintf(stderr, ...): 에러 스트림에 직접 출력
        fprintf(stderr, "오류: 파일을 열 수 없음\n");
        // perror: errno를 해석해 자동으로 stderr에 출력
        perror("fopen 실패");
        // 출력 예: "fopen 실패: No such file or directory"
        // strerror: errno 코드를 문자열로 변환
        fprintf(stderr, "errno %d: %s\n",
                errno, strerror(errno));
        return 1;
    }
    fclose(fp);
    return 0;
}
