#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int capacity = 2;
    int size = 0;
    int* arr = (int*)malloc(capacity * sizeof(int));
    if (arr == NULL) return 1;

    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        // 공간 부족 시 두 배로 확장
        if (size == capacity) {
            int new_cap = capacity * 2;
            int* tmp = (int*)malloc(new_cap * sizeof(int));
            if (tmp == NULL) { free(arr); return 1; }
            memcpy(tmp, arr, capacity * sizeof(int));
            free(arr);
            arr = tmp;
            capacity = new_cap;
            printf("용량 확장: %d\n", capacity);
        }
        arr[size++] = values[i];
    }

    printf("저장된 원소: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
