#include <stdio.h>

int main(void) {
    int age;
    char name[32];

    // stdout 출력
    printf("이름을 입력하세요: ");

    // stdin 입력
    scanf("%s", name);
    scanf("%d", &age);

    printf("안녕하세요, %s님! 나이: %d\n",
           name, age);
    return 0;
}
