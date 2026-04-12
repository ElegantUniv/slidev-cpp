#include <stdio.h>

int main() {
    int age;
    char name[32];

    scanf("%d", &age);
    // 입력: "25\n"
    // scanf는 "25"만 읽고 '\n'은 버퍼에 남김

    scanf("%c", &name[0]);
    // '\n'을 읽어버림! 의도한 문자가 아님
    printf("age=%d, name[0]=%d\n", age, name[0]);
    // → age=25, name[0]=10  (10 = ASCII '\n')
}
