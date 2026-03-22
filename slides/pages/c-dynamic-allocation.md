---
layout: cover
---

# C 프로그래밍
## 동적 메모리 할당

---
layout: two-cols-header
---

# 프로그램의 메모리 구조

프로그램 실행 시 메모리는 크게 4개의 영역으로 나뉜다.


::left::

```
높은 주소
┌─────────────────────────┐
│        Stack            │  ← 지역 변수, 함수 호출
│   (위에서 아래로 성장)     │     자동 할당 / 자동 해제
├─────────────────────────┤
│           ↕             │
│        (여유 공간)        │
│           ↕             │
├─────────────────────────┤
│         Heap            │  ← 동적 메모리
│   (아래에서 위로 성장)      │     malloc() / free()
├─────────────────────────┤
│    BSS (미초기화)        │  ← 초기화 안 된 전역변수
├─────────────────────────┤
│    Data (초기화됨)       │  ← 초기화된 전역/정적 변수
├─────────────────────────┤
│    Text (Code)          │  ← 실행 코드 (읽기 전용)
└─────────────────────────┘
낮은 주소
```

::right::

```c 
#include <stdlib.h>     // 동적 할당을 위한 각종 함수 제공

// Text 영역: 함수 코드
int add(int a, int b) { return a + b; }

// Data 영역: 초기화된 전역변수
int global_init = 100;
// BSS 영역: 초기화 안 된 전역변수
int global_uninit;

// Stack 영역: 지역변수 (함수 호출 시)
void func(void) {
    int local = 42;      // Stack에 할당
    int arr[100];        // Stack에 할당 (400 bytes)
    // 함수 반환 시 자동 해제
}

// Heap 영역: 동적 할당
int* p = (int*)malloc(sizeof(int));
*p = 42;
free(p);   // ← 반드시 해제!
p = NULL;
```


---
layout: two-cols-header
---

# 프로그램의 메모리 구조

프로그램 실행 시 메모리는 크게 4개의 영역으로 나뉜다.


::left::

```
높은 주소
┌─────────────────────────┐
│        Stack            │  ← 지역 변수, 함수 호출
│   (위에서 아래로 성장)     │     자동 할당 / 자동 해제
├─────────────────────────┤
│           ↕             │
│        (여유 공간)        │
│           ↕             │
├─────────────────────────┤
│         Heap            │  ← 동적 메모리
│   (아래에서 위로 성장)      │     malloc() / free()
├─────────────────────────┤
│    BSS (미초기화)        │  ← 초기화 안 된 전역변수
├─────────────────────────┤
│    Data (초기화됨)       │  ← 초기화된 전역/정적 변수
├─────────────────────────┤
│    Text (Code)          │  ← 실행 코드 (읽기 전용)
└─────────────────────────┘
낮은 주소
```

::right::



| 영역 | 설명 |
|------|------|
| **코드(Code)** | 실행할 기계어 명령이 저장되는 영역 |
| **데이터(Data)** | 전역 변수, 정적 변수가 저장되는 영역 |
| **스택(Stack)** | 함수 호출 시 지역 변수·매개변수가 저장되는 영역 (자동 관리) |
| **힙(Heap)** | 프로그래머가 직접 할당·해제하는 영역 (동적 할당) |

<br>

> 동적 메모리 할당은 **힙(Heap)** 영역을 사용한다.



---
layout: two-cols-header
---

# 정적 할당 vs 동적 할당

::left::

## 정적 할당

```c {}
int arr[10];  // 크기를 컴파일 시점에 결정
```

- 크기가 고정됨
- 스택에 저장, 자동 해제
- 실행 전에 크기를 알아야 함

::right::


## 동적 할당

```c {}
#include <stdlib.h>     // 동적 할당을 위한 각종 함수 제공

int n = 10;
int* arr = (int*)malloc(n * sizeof(int));

free(arr);
```

- **실행 시점**에 크기 결정 가능
- 힙에 저장, **수동 해제** 필요
- 크기를 유연하게 조절 가능


---
layout: two-cols-header
---

# 동적 메모리 할당
- 동적 메모리 할당은 바이트(byte) 단위로 할당됨.
- 할당된 메모리는 타입이 없음
- 포인터 타입이 할당된 메모리를 어떻게 쓰는지 결정함.
- 프로그램이 구동된 후에야 메모리의 크기가 결정될 때만, 동적 메모리 할당을 쓰도록 하자!

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int arr[100];  // 100개 정도는 스택에 잡으세요.
    int* s = (int*)malloc(sizeof(int)*100);   // 이런 코드는 쓰지 말 것!!!

    void* p = malloc(8000);

    char*   pc = (char*) p;
    int*    pi = (int*) p;
    float*  pf = (float*) p;
    double* pd = (double*) p;

    free(s);
    free(p);

    return 0;
}
```

---
layout: two-cols-header
---

# 동적 메모리 할당 & 메모리 오류

::left::

### 올바른 동적 메모리 사용

```c 
#include <stdio.h>
#include <stdlib.h>     // 동적 할당을 위한 각종 함수 제공

int main(void) {
    int n = 5;
    int* arr = (int*)malloc(n * sizeof(int));

    // ✅ NULL 체크 필수
    if (arr == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        arr[i] = (i + 1) * 10;

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);  // 10 20 30 40 50

    free(arr);    // ✅ 반드시 해제
    arr = NULL;   // ✅ 댕글링 포인터 방지
    return 0;
}
```

::right::

### 흔한 메모리 오류

1. 메모리 누수 (Memory Leak)
```c
int* p = malloc(100);
// free(p) 빠뜨림 → 프로그램이 계속 메모리 점유
```

2. 댕글링 포인터 (Dangling Pointer)
```c
int* p = malloc(sizeof(int));
free(p);
*p = 42;  // ❌ 해제된 메모리 접근! 위험!
```

3. 버퍼 오버플로우
```c
char buf[5];
strcpy(buf, "Hello, World!");  // ❌ 넘침!
// 보안 취약점의 주요 원인
```

4. 이중 해제 (Double Free)
```c
free(p);
free(p);  // ❌ 이미 해제된 메모리 재해제
```




---
layout: two-cols-header
---

# malloc() — 메모리 할당

`malloc`은 지정한 바이트 수만큼 힙에 메모리를 할당하고, 그 시작 주소를 반환한다.

::left::

## malloc() 함수

```c {}
void* malloc(size_t size);
```

- 할당 성공 시: 할당된 메모리의 포인터 반환
- 할당 실패 시: `NULL` 반환
- 할당된 메모리의 초기값은 **쓰레기 값**


> ⚠️ `malloc` 반환값의 자료형은 `void*`이다. 왜 그럴까?


<br>

```c {}
// int 하나를 위한 공간 할당
int* p = (int*)malloc(sizeof(int));

// int 배열 n개를 위한 공간 할당
int* arr = (int*)malloc(n * sizeof(int));
```

::right::

## malloc() 예제

<<< @/snippets/c-dynamic-allocation/malloc_basic.c c 

---
layout: two-cols-header
---

# calloc() — 0으로 초기화된 할당

`calloc`은 메모리를 할당하면서 **모든 바이트를 0으로 초기화**한다.

::left::

## calloc() 함수

```c {}
void* calloc(size_t nmemb, size_t size);
```

- `nmemb`: 요소의 개수
- `size`: 요소 하나의 바이트 크기
- `malloc(nmemb * size)`와 같지만 **초기화**가 다름

::right::

## calloc() 예제

<<< @/snippets/c-dynamic-allocation/calloc_example.c c

---
layout: two-cols-header
---

# free() — 메모리 해제

동적 할당한 메모리는 사용 후 반드시 **`free()`로 해제**해야 한다.

::left::

## free() 함수


```c {}
void free(void* ptr);
```

- `malloc`, `calloc`으로 할당한 포인터만 전달
- 같은 포인터를 두 번 해제하면 **정의되지 않은 동작**
- 해제 후 포인터를 `NULL`로 설정하는 것이 안전

```c {}
free(arr);
arr = NULL;  // 댕글링 포인터 방지
```

::right::

## 메모리 누수와 댕글링 포인터

<<< @/snippets/c-dynamic-allocation/memory_leak.c c


---
layout: default
---


# free() — 메모리 해제

동적 할당한 메모리는 사용 후 반드시 **`free()`로 해제**해야 한다.


## 주의사항 정리

| 문제 | 원인 | 해결책 |
|------|------|--------|
| **메모리 누수** | `free()` 미호출 | 모든 경로에서 `free()` 호출 |
| **댕글링 포인터** | `free()` 후 포인터 사용 | `free()` 후 `p = NULL` |
| **이중 해제** | 같은 포인터 두 번 `free()` | `free()` 후 `p = NULL` |
| **NULL 역참조** | 할당 실패 확인 누락 | 항상 `NULL` 체크 |
| **버퍼 오버플로** | 할당 범위 초과 접근 | 인덱스 범위 확인 |


---
layout: two-cols-header
---

# 메모리 크기 재조정 — malloc() + memcpy() + free()

새 블록을 할당하고 데이터를 복사한 뒤 기존 블록을 해제한다.

::left::

#### 패턴

```c {}
#include <string.h>  // memcpy

int new_cap = old_cap * 2;
int* tmp = (int*)malloc(new_cap * sizeof(int));
if (tmp == NULL) { free(arr); return 1; }
memcpy(tmp, arr, old_cap * sizeof(int));
free(arr);
arr = tmp;
```

| 단계 | 함수 | 역할 |
|------|------|------|
| 1 | `malloc` | 새 크기만큼 힙 공간 확보 |
| 2 | `memcpy` | 기존 데이터를 새 공간으로 복사 |
| 3 | `free` | 기존 블록 해제 |

::right::

#### 예제

<<< @/snippets/c-dynamic-allocation/realloc_example.c c


---
layout: default
---

# 요약

```c {}
#include <stdlib.h>     // 동적 할당을 위한 각종 함수 제공
```

| 함수 | 역할 | 초기값 |
|------|------|--------|
| `malloc(size)` | `size` 바이트 할당 | 쓰레기 값 |
| `calloc(n, size)` | `n * size` 바이트 할당 | 0 |
| `free(ptr)` | 할당된 메모리 해제 | — |
| `memcpy(dst, src, n)` | `n` 바이트 복사 (`<string.h>`) | — |

<br>

> 동적 할당을 사용하면 **유연한 자료구조**를 만들 수 있지만,
> **메모리 관리 책임**은 전적으로 프로그래머에게 있다.
