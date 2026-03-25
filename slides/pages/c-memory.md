---
layout: cover
---

# C 프로그래밍
## 메모리 관리

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

# 정적 메모리 할당

컴파일 시점에 크기와 위치가 **결정**되는 메모리 할당 방식이다.

::left::

```c
// Data 영역: 초기화된 전역 변수
int global_a = 10;

// BSS 영역: 초기화되지 않은 전역 변수 (자동으로 0)
int global_b;

void func(void) {
    // Stack 영역: 지역 변수 (자동 할당·해제)
    int local = 42;
    int arr[5] = {1, 2, 3, 4, 5};

    // Stack 영역: 정적 지역 변수 → Data/BSS에 저장
    static int count = 0;
    count++;
}
```

::right::

## 저장 위치

| 종류 | 저장 위치 | 생존 기간 |
|------|-----------|-----------|
| 지역 변수, 지역 배열 | **Stack** | 함수 실행 중 |
| 초기화된 전역·정적 변수 | **Data** | 프로그램 전체 |
| 미초기화 전역·정적 변수 | **BSS** | 프로그램 전체 |

---
layout: two-cols-header
---

# 정적 메모리 할당 — 스택(Stack) 영역

함수가 호출될 때 지역 변수와 배열이 스택에 **자동으로** 할당되고, 함수가 반환되면 **자동으로** 해제된다.

::left::

```c
#include <stdio.h>

void print_squares(int n) {
    int arr[n];   // ❌ 가변 길이 배열(VLA): 비권장
    int arr2[10]; // ✅ 크기가 상수인 배열

    for (int i = 0; i < 10; i++)
        arr2[i] = i * i;

    for (int i = 0; i < 10; i++)
        printf("%d ", arr2[i]);
}

int main(void) {
    print_squares(10);
    // 함수 반환 후 arr2는 자동 해제
    return 0;
}
```

::right::

### 특징

- 크기는 **컴파일 시점에 상수**여야 한다
- 할당·해제가 **자동**이므로 관리 부담 없음
- 스택 크기는 제한적 (수 MB 수준)
- 큰 배열을 스택에 올리면 **스택 오버플로** 발생 위험

```c
// ✅ 작은 배열 → 스택에 선언
int buf[256];

// ❌ 큰 배열 → 스택 오버플로 위험
int big[10000000];  // 약 40 MB, 위험!
```

> 크기를 모르거나 크기가 크다면 동적 할당을 사용하라.

---
layout: two-cols-header
---

# 정적 메모리 할당 — 전역 변수와 `static`

전역 변수와 `static` 변수는 **Data / BSS 영역**에 저장되며 프로그램 종료 시까지 유지된다.

::left::

```c
#include <stdio.h>

// Data 영역 (초기화됨)
int global_count = 0;

void increment(void) {
    // static 지역 변수: 함수가 끝나도 값 유지
    static int call_count = 0;
    call_count++;
    global_count++;
    printf("호출 횟수: %d\n", call_count);
}

int main(void) {
    increment();  // 호출 횟수: 1
    increment();  // 호출 횟수: 2
    increment();  // 호출 횟수: 3
    printf("global_count = %d\n", global_count); // 3
    return 0;
}
```

::right::

### `static` 키워드 정리

| 위치 | 효과 |
|------|------|
| 전역 변수에 `static` | 해당 파일 내에서만 접근 가능 (파일 범위 제한) |
| 지역 변수에 `static` | 함수 종료 후에도 값이 유지됨 |


---
layout: default
---

# 메모리 할당 — 장단점

| | 정적 메모리 할당 | 동적 메모리 할당 |
|---|---|---|
| **크기 결정** | 컴파일 시점 | 실행 시점 |
| **저장 위치** | Stack / Data / BSS | Heap |
| **할당·해제** | 자동 | 수동 (`malloc` / `free`) |
| **속도** | 빠름 | 느림 (OS 요청 필요) |
| **유연성** | 낮음 (고정 크기) | 높음 (가변 크기) |
| **위험 요소** | 스택 오버플로 | 메모리 누수, 댕글링 포인터 |

<br>

> 크기가 **컴파일 시점에 확정**되고 **작은 데이터**라면 정적 할당을 우선하라.
> 크기가 **실행 중에 결정**되거나 **큰 메모리**가 필요하면 동적 할당을 사용하라.


---
layout: two-cols-header
---

# 동적 메모리 할당
크기가 **실행 중에 결정**되거나 **큰 메모리**가 필요하면 동적 할당 사용

- 동적 메모리 할당은 바이트(byte) 단위로 할당됨.
- 할당된 메모리는 타입이 없음.
- 포인터 타입이 할당된 메모리를 어떻게 쓰는지 결정함.
- `#include <stdlib.h>`을 포함시켜, 메모리 설정을 위한 함수 호출을 준비할 것.


```c
#include <stdio.h>
#include <stdlib.h>   // 메모리 설정을 위한 각종 함수 제공

int main(void)
{
    int arr[100];  // 100개 정도는 스택에 잡으세요.
    void* p = malloc(8000);

    char*   pc = (char*) p;
    int*    pi = (int*) p;
    float*  pf = (float*) p;
    double* pd = (double*) p;

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
#include <stdlib.h>   // 메모리 설정을 위한 각종 함수 제공

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

# malloc() — 동적 메모리 할당

`malloc`은 지정한 바이트 수만큼 힙에 메모리를 동적 할당하고, 그 시작 주소를 반환한다.

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

<<< @/snippets/c-memory/malloc_basic.c c 

---
layout: two-cols-header
---

# calloc() — 0으로 초기화된 동적 메모리 할당

`calloc`은 메모리를 동적 할당하면서 **모든 바이트를 0으로 초기화**한다.

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

<<< @/snippets/c-memory/calloc_example.c c

---
layout: two-cols-header
---

# free() — 동적 할당 메모리 해제

동적 할당한 메모리는 사용 후 반드시 **`free()`로 해제**해야 한다.

::left::

## free() 함수


```c {}
void free(void* ptr);
```

- `malloc`, `calloc`으로 동적 할당한 포인터만 전달
- 같은 포인터를 두 번 해제하면 **정의되지 않은 동작**
- 해제 후 포인터를 `NULL`로 설정하는 것이 안전

```c {}
free(arr);
arr = NULL;  // 댕글링 포인터 방지
```

::right::

## 메모리 누수와 댕글링 포인터

<<< @/snippets/c-memory/memory_leak.c c


---
layout: default
---


# free() — 동적 할당 메모리 해제

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

# 정적 메모리 할당 vs 동적 메모리 할당

| | 정적 메모리 할당 | 동적 메모리 할당 |
|---|---|---|
| **크기 결정** | 컴파일 시점 | 실행 시점 |
| **저장 위치** | Stack / Data / BSS | Heap |
| **할당·해제** | 자동 | 수동 (`malloc` / `free`) |
| **유연성** | 낮음 (고정 크기) | 높음 (가변 크기) |
| **위험 요소** | 스택 오버플로 | 메모리 누수, 댕글링 포인터 |

<br>
::left::

#### 정적 메모리 할당
- 크기가 **컴파일 시점에 확정**되고 **작은 데이터**
```c {}
int arr[10];  // 크기를 컴파일 시점에 결정
```

::right::


#### 동적 메모리 할당
- 크기가 **실행 중에 결정**되거나 **큰 메모리**가 필요


```c {}
#include <stdlib.h>   // 메모리 설정을 위한 각종 함수 제공

int n;
int* arr;

scanf("동적 할당할 int 개수: %d", &n);   // 크기를 실행 중에 결정
arr = (int*)malloc(n * sizeof(int));

free(arr);
```



---
layout: two-cols-header
---

# memset() — 메모리 초기화

`memset`은 메모리 블록의 **모든 바이트를 특정 값으로 설정**한다. `<string.h>`에 선언되어 있다.

::left::

## 함수 시그니처

```c {}
#include <string.h>

void* memset(void* ptr, int value, size_t n);
```

| 매개변수 | 설명 |
|----------|------|
| `ptr` | 설정할 메모리의 시작 주소 |
| `value` | 설정할 값 (바이트 단위로 적용) |
| `n` | 설정할 바이트 수 |

- 반환값: `ptr`과 동일한 포인터
- `value`는 `unsigned char`로 변환되어 각 바이트에 복사됨

> ⚠️ `value`는 바이트 단위로 채워진다.
> `int` 배열을 0 이외의 값으로 채울 때는 주의가 필요하다.

::right::

## 예제

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    // 배열을 0으로 초기화
    int arr[5];
    memset(arr, 0, sizeof(arr));
    // arr = {0, 0, 0, 0, 0}

    // 동적 할당 후 0으로 초기화
    int* buf = (int*)malloc(5 * sizeof(int));
    if (buf == NULL) return 1;
    memset(buf, 0, 5 * sizeof(int));

    // char 배열을 특정 문자로 채우기
    char str[6];
    memset(str, 'A', 5);
    str[5] = '\0';
    printf("%s\n", str);   // AAAAA

    free(buf);
    return 0;
}
```

---
layout: two-cols-header
---

# memset() — 주의사항

`memset`은 **바이트 단위**로 값을 채우기 때문에, `int` 등 다바이트 자료형에 0 또는 -1 이외의 값을 채울 때는 예상과 다른 결과가 나온다.

::left::

### 안전한 사용 — 0과 -1(0xFF)

```c
int arr[4];

// ✅ 0으로 채우기: 모든 바이트가 0x00 → int도 0
memset(arr, 0, sizeof(arr));

// ✅ -1로 채우기: 모든 바이트가 0xFF → int는 -1 (2의 보수)
memset(arr, -1, sizeof(arr));
```

::right::

### 위험한 사용 — 그 외 정수값

```c
int arr[4];

// ❌ 1로 채우기: 각 바이트가 0x01
//    → int 하나 = 0x01010101 = 16843009 (의도와 다름!)
memset(arr, 1, sizeof(arr));

// ✅ 올바른 방법: 루프로 직접 채우기
for (int i = 0; i < 4; i++)
    arr[i] = 1;
```

---
layout: two-cols-header
---

# memcpy() — 메모리 복사

`memcpy`는 메모리 블록을 **바이트 단위로 복사**한다. `<string.h>`에 선언되어 있다.

::left::

## 함수 시그니처

```c {}
#include <string.h>

void* memcpy(void* dst, const void* src, size_t n);
```

| 매개변수 | 설명 |
|----------|------|
| `dst` | 복사 대상(목적지) 주소 |
| `src` | 복사 원본 주소 |
| `n` | 복사할 바이트 수 |

- 반환값: `dst`와 동일한 포인터
- `dst`와 `src`가 **겹치면 안 됨** → 겹칠 경우 `memmove()` 사용

> ⚠️ `src`가 `const`이므로 원본은 수정되지 않는다.

::right::

## 예제

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int src[5] = {1, 2, 3, 4, 5};

    // 스택 배열 복사
    int dst[5];
    memcpy(dst, src, sizeof(src));
    // dst = {1, 2, 3, 4, 5}

    // 동적 배열 복사
    int* buf = (int*)malloc(5 * sizeof(int));
    if (buf == NULL) return 1;
    memcpy(buf, src, 5 * sizeof(int));

    for (int i = 0; i < 5; i++)
        printf("%d ", buf[i]);  // 1 2 3 4 5

    free(buf);
    return 0;
}
```

---
layout: default
---

# memset() / memcpy() 요약

```c {}
#include <string.h>   // memset, memcpy
```

| 함수 | 역할 | 주의사항 |
|------|------|----------|
| `memset(ptr, val, n)` | `n` 바이트를 `val`로 채움 | `val`은 바이트 단위 적용 — 0, -1 외에는 주의 |
| `memcpy(dst, src, n)` | `n` 바이트를 `src`에서 `dst`로 복사 | `dst`와 `src`가 겹치면 안 됨 |

<br>

```c {}
// 전형적인 패턴: 할당 → 초기화 → 사용 → 해제
int* buf = (int*)malloc(n * sizeof(int));
if (buf == NULL) return 1;
memset(buf, 0, n * sizeof(int));       // 0으로 초기화
memcpy(buf, src, n * sizeof(int));     // 데이터 복사
free(buf);
buf = NULL;
```

---
layout: two-cols-header
---

# 동적 메모리 크기 재조정 — malloc()+memcpy()+free()

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

<<< @/snippets/c-memory/realloc_example.c c


---
layout: default
---

# 요약
왠만하면 정적 할당 쓰세요.

- 동적 할당을 사용하면 **유연한 자료구조**를 만들 수 있지만,
**메모리 관리 책임**은 전적으로 프로그래머에게 있다.

| 헤더 | 함수 | 역할 |
|------|------|------|
| `<stdlib.h>` | `malloc(size)` | `size` 바이트 할당 (초기값: 쓰레기) |
| `<stdlib.h>` | `free(ptr)` | 할당된 메모리 해제 |

<br>

- 정적 할당 받았던 동적 할당 받았던 상관없이, 메모리 설정 및 복사 함수를 이용해서 빠르게 메모리 값 변경이 가능.

| 헤더 | 함수 | 역할 |
|------|------|------|
| `<string.h>` | `memset(ptr, val, n)` | `n` 바이트를 `val`로 초기화 |
| `<string.h>` | `memcpy(dst, src, n)` | `n` 바이트 복사 (겹침 불가) |
