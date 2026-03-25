#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;

    // calloc: 할당과 동시에 0으로 초기화
    int* arr = (int*)calloc(n, sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }

    // 초기값 확인 (모두 0)
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    return 0;
}
