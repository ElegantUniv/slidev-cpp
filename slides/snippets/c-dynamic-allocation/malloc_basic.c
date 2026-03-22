#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("정수 개수 입력: ");
    scanf("%d", &n);

    // n개의 int를 힙에 할당
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);  // 반드시 해제
    return 0;
}
