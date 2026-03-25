#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int old_cap = 3;
    int* arr = (int*)malloc(old_cap * sizeof(int));
    if (arr == NULL) return 1;

    arr[0] = 10; arr[1] = 20; arr[2] = 30;
    printf("확장 전: %d %d %d\n", arr[0], arr[1], arr[2]);

    // 크기를 3 → 6으로 확장
    int new_cap = 6;
    int* tmp = (int*)malloc(new_cap * sizeof(int));
    if (tmp == NULL) { free(arr); return 1; }
    memcpy(tmp, arr, old_cap * sizeof(int));
    free(arr);
    arr = tmp;

    arr[3] = 40; arr[4] = 50; arr[5] = 60;
    for (int i = 0; i < new_cap; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    return 0;
}
