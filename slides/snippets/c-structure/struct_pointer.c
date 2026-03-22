#include <stdio.h>

typedef struct {
    char name[32];
    int  age;
} Student;

void print_student(const Student* s) {
    // -> 연산자: 포인터를 통한 멤버 접근
    printf("이름: %s, 나이: %d\n", s->name, s->age);
}

void birthday(Student* s) {
    s->age += 1;  // 원본 수정
}

int main() {
    Student s = {"홍길동", 20};
    print_student(&s);
    birthday(&s);
    print_student(&s);
    return 0;
}
