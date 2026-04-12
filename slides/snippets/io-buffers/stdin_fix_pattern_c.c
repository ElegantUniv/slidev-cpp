#include <stdio.h>

int main(void) {
    char line[256];
    int  age;
    char name[64];

    // fgets: 줄 전체 소비 — '\n'이 버퍼에 남지 않음
    if (fgets(line, sizeof(line), stdin))
        sscanf(line, "%63s", name);

    if (fgets(line, sizeof(line), stdin))
        sscanf(line, "%d", &age);

    printf("이름: %s, 나이: %d\n", name, age);
    return 0;
}
