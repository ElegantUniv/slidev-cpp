---
layout: section
---

## C 프로그래밍 소개
# 배열과 문자열

---
layout: two-cols
---

# 배열 (Array)

<br>

```c 
// 배열 선언과 초기화
int arr[5] = {10, 20, 30, 40, 50};
//  인덱스:    0   1   2   3   4
printf("%d\n", arr[2]);  // 30

// 배열 순회
int n = sizeof(arr) / sizeof(arr[0]); // 길이: 5
for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
}
// 출력: 10 20 30 40 50

// 2차원 배열 (개인적인 의견: 되도록 쓰지 마세요)
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
printf("%d\n", matrix[1][2]); // 6

// 배열 = 함수에 전달 시 포인터로 넘어감
void print_arr(int arr[], int n);
```

::right::


### ⚠️ 배열 주의사항


1. **크기 고정** — 컴파일 시 결정, 변경 불가
   ```c
   int arr[5];  // 크기 5, 이후 변경 불가
   ```

2. **경계 검사 없음** — 가장 위험한 C 버그!
   ```c
   int arr[5];
   arr[10] = 99;  // ❌ 컴파일은 됨! 런타임 오류
   // Python은 IndexError로 잡아주지만 C는 그냥 실행됨
   ```

3. **길이 계산 관용구**
   ```c
   int n = sizeof(arr) / sizeof(arr[0]);
   ```

4. **함수에 배열 전달 시 크기도 같이 전달**
   ```c
   void func(int arr[], int n) { ... }
   func(arr, 5);
   ```

---
layout: two-cols-header
---

# 문자열 (String)
C 언어에서 문자열은 character 배열로 처리됨.

::left ::

```c 
// 문자열 = char 배열 + NULL 종료자('\0')
char s1[10] = "Hello";
// 메모리: H e l l o \0 ? ? ? ?
//  인덱스: 0 1 2 3 4  5

// 문자열 리터럴 (수정 불가)
const char* s2 = "World";  // 읽기 전용!

// string.h 함수들
#include <string.h>

strlen(s1);           // 길이: 5 ('\0' 미포함)
strcpy(dst, src);     // 복사 (dst 충분히 커야 함)
strncpy(dst, src, n); // 안전한 복사
strcat(s1, "!");      // 연결: "Hello!"
strcmp(s1, s2);       // 비교: <0, 0, >0

// 문자열 → 숫자 (#include <stdlib.h>)
int  n = atoi("42");     // "42" → 42
double d = atof("3.14"); // "3.14" → 3.14

// 형식 지정 문자열 생성
char buf[50];
sprintf(buf, "%s is %d", "age", 20);
```

::right::

### 메모리 구조

```c {}
char s1[10] = "Hello";

s1:    [0][1][2][3][4][5][6][7]
value:  H  e  l  l  o \0  ?   ?
                       ↑
                     NULL 종료자
                     (필수! 없으면 오작동)

const char* s2 = "World";

s2:    [0][1][2][3][4][5][6][7]
value:  W  o  r  l  d \0  ?   ?
                       ↑
                     NULL 종료자
                     (필수! 없으면 오작동)
```



---
layout: two-cols-header
---

# 포인터 & 배열

::left::

```c 
int arr[] = {10, 20, 30, 40, 50};

// 배열 이름 = 첫 번째 원소의 주소
int* p = arr;        // == &arr[0]
printf("%d\n", *p);  // 10

// 포인터 산술
p++;                 // 다음 int로 이동 (+4 bytes)
printf("%d\n", *p);  // 20

// 두 표현은 동일
printf("%d\n", arr[2]);    // 30
printf("%d\n", *(arr+2));  // 30

// 포인터로 배열 순회
for (int* ptr = arr; ptr < arr + 5; ptr++) {
    printf("%d ", *ptr);
}
// 출력: 10 20 30 40 50
```

::right::

### 포인터 산술 규칙

```
arr = &arr[0] = 0x1000

p = arr        →  p = 0x1000  (arr[0] = 10)
p + 1          →  p = 0x1004  (arr[1] = 20)  +4 bytes
p + 2          →  p = 0x1008  (arr[2] = 30)  +8 bytes
```

### NULL 포인터

```c
int* p = NULL;  // 아무것도 가리키지 않음

// 사용 전 반드시 NULL 체크!
if (p != NULL) {
    printf("%d\n", *p);
}

// NULL 포인터 역참조 → 프로그램 충돌!
// int* p = NULL;
// *p = 42;  // ❌ Segmentation Fault
```

---
layout: section
---

## C 프로그래밍 소개
# 메모리 구조 이해

---
layout: two-cols-header
---

# 프로그램의 메모리 구조

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
#include <stdlib.h>

int* p = (int*)malloc(sizeof(int));
*p = 42;
free(p);   // ← 반드시 해제!
p = NULL;
```


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
#include <stdlib.h>

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
layout: section
---

## C 프로그래밍 소개
# 구조체 (struct)

---
layout: two-cols-header
---

# 구조체 정의 & 사용
구조체는 사용자 정의 자료구조임.

::left::

```c
// 구조체 정의 (typedef로 편하게)
typedef struct {
    char   name[50];
    int    student_id;
    double gpa;
} Student;  // ← 타입 이름

// 구조체 변수 생성 & 초기화
Student s1 = {"김철수", 20230001, 3.8};
Student s2;                   // 선언만

// 멤버 접근: . (점 연산자)
strcpy(s2.name, "이영희");
s2.student_id = 20230002;
s2.gpa = 3.5;
printf("%s: %.1f\n", s1.name, s1.gpa);

Student* s = &s1;
printf("%-10s %d %.2f\n",
        s->name,          // -> 연산자!
        s->student_id,
        s->gpa);
```

::right::

### 접근 연산자 비교

<br>

| 상황 | 연산자 | 예시 |
|------|--------|------|
| 일반 변수 | `.` (점) | `s1.gpa` |
| 포인터 변수 | `->` (화살표) | `p->gpa` |


<br>

- C `struct`는 **메서드(함수) 없음**
- C `struct`는 **상속 없음** <br>
→ C++의 `class` = struct + 메서드 + 접근 제어


---
layout: two-cols-header
---

# 구조체 — 동적 할당 & 실전 예제

::left::

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char   name[50];
    int    scores[3];   // 중간, 기말, 과제
    double average;
} Student;

// 평균 계산 함수
void calc_avg(Student* s) {
    int sum = 0;
    for (int i = 0; i < 3; i++)
        sum += s->scores[i];
    s->average = (double)sum / 3;
}

// 학점 반환
char get_grade(double avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    return 'F';
}
```

::right::

```c
int main(void) {
    // 동적 배열로 학생 관리
    int n = 3;
    Student* students =
        (Student*)malloc(n * sizeof(Student));

    // 데이터 설정
    strcpy(students[0].name, "김철수");
    students[0].scores[0] = 85;
    students[0].scores[1] = 90;
    students[0].scores[2] = 78;

    for (int i = 0; i < n; i++) {
        calc_avg(&students[i]);
        printf("%-10s 평균: %.1f  학점: %c\n",
               students[i].name,
               students[i].average,
               get_grade(students[i].average));
    }

    free(students);  // 반드시 해제!
    return 0;
}
```

> 💡 이 패턴이 C++의 `class` + **생성자/소멸자**로 발전합니다.


---
layout: two-cols
---

# C 학습 완료 체크리스트

✅ **컴파일 & 빌드** — gcc, 전처리 링크 이해

✅ **변수 & 자료형** — 타입 명시, sizeof

✅ **조건문 & 반복문** — 괄호, 세미콜론 필수

✅ **함수** — 프로토타입, 값 전달 vs 포인터 전달

✅ **배열 & 문자열** — char 배열, string.h 함수

✅ **포인터** — &, *, 포인터 산술

✅ **메모리 구조** — Stack/Heap, malloc/free

✅ **구조체** — typedef struct, `.` vs `->`

:: right::

<div class="bg-amber-500/20 border border-amber-500 rounded-lg p-6">

### 이제 C++로! 🚀


다음에 배울 내용:

- `class` & 객체 지향 프로그래밍
- 생성자 / 소멸자
- 상속과 다형성
- **참조자** (`int &ref = x`)
- 연산자 오버로딩
- **STL** — `vector`, `map`, `string`
- 스마트 포인터 (`unique_ptr`, `shared_ptr`)

> 오늘 배운 **포인터 & 메모리** 이해가  
> C++를 잘 쓰기 위한 핵심 기반입니다!


</div>

<!--
2주간 수고하셨습니다!
C에서 배운 포인터와 메모리 개념이 C++의 스마트 포인터, 참조자, RAII 패턴의 기반이 됩니다.
-->
