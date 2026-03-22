#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int  score;
} Student;

int main() {
    int n = 3;
    Student* students = (Student*)malloc(n * sizeof(Student));
    if (students == NULL) return 1;

    strcpy(students[0].name, "홍길동"); students[0].score = 90;
    strcpy(students[1].name, "이순신"); students[1].score = 85;
    strcpy(students[2].name, "강감찬"); students[2].score = 92;

    for (int i = 0; i < n; i++) {
        printf("%s: %d점\n", students[i].name, students[i].score);
    }

    free(students);
    return 0;
}
