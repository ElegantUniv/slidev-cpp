---
layout: cover
---

# C++ 프로그래밍
## 포인터 (Pointer) — C와 C++의 차이

---
layout: two-cols-header
---

# C 포인터 복습

::left::

## 핵심 연산자

```cpp {}
int x = 42;

int* p = &x;   // & : 주소 연산자 (x의 주소)
*p = 100;      // * : 역참조 연산자 (p가 가리키는 값)

printf("%d\n", x);   // 100
printf("%p\n", p);   // 0x7fff... (주소)
printf("%d\n", *p);  // 100
```

## 포인터와 배열

```cpp {}
int arr[3] = {10, 20, 30};
int* p = arr;           // 배열 이름 = 첫 번째 원소의 주소

printf("%d\n", *(p + 0));  // 10
printf("%d\n", *(p + 1));  // 20
printf("%d\n", p[2]);      // 30  (배열 표기와 동일)
```

::right::

## C 동적 할당

```cpp {}
#include <stdlib.h>

// 단일 변수
int* p = (int*)malloc(sizeof(int));
*p = 42;
free(p);
p = NULL;

// 배열
int n = 5;
int* arr = (int*)malloc(n * sizeof(int));
if (arr == NULL) { /* 실패 처리 */ }

for (int i = 0; i < n; i++)
    arr[i] = i * 10;

free(arr);
arr = NULL;
```

> C에서는 `malloc` / `free`, 타입 캐스팅, NULL 체크가 항상 함께 따라온다.

---
layout: two-cols-header
---

# `nullptr` — C++의 null 포인터

C++11부터 `NULL` 대신 **`nullptr`** 을 사용한다.

::left::

## NULL의 문제점

```cpp {}
// C에서 NULL은 단순히 정수 0 또는 (void*)0
#define NULL 0

void func(int n)  { printf("int\n"); }
void func(int* p) { printf("ptr\n"); }

func(0);      // "int"  — 의도대로
func(NULL);   // "int"  ← ❌ 포인터 버전이 호출되지 않음!
              //    NULL이 0(int)으로 해석됨
```

::right::

## nullptr 사용

```cpp {}
// nullptr: 포인터 전용 null 상수 (타입: nullptr_t)
void func(int n)  { printf("int\n"); }
void func(int* p) { printf("ptr\n"); }

func(nullptr);  // "ptr"  ✅ 포인터 버전이 정확히 호출됨

// 포인터 초기화
int* p = nullptr;   // ✅ C++ 권장
// int* p = NULL;   // ⚠️ 동작은 하지만 권장 안 함
// int* p = 0;      // ⚠️ 동작은 하지만 의미 불명확

// null 체크
if (p == nullptr) { /* null임 */ }
if (!p)           { /* 동일한 의미 */ }
```

> C++에서는 항상 **`nullptr`** 을 사용하자.

---
layout: two-cols-header
---

# `new` / `delete` — C++ 동적 할당

C++에서는 `malloc` / `free` 대신 **`new`** / **`delete`** 를 사용한다.

::left::

## 단일 객체

```cpp {}
// C 스타일
int* p1 = (int*)malloc(sizeof(int));
*p1 = 42;
free(p1);

// C++ 스타일
int* p2 = new int;      // 할당 (초기화 없음)
*p2 = 42;
delete p2;              // 해제

int* p3 = new int(99);  // 할당 + 초기화
delete p3;

// 클래스 객체 — 생성자/소멸자 자동 호출
struct Point { int x; int y; };
Point* pt = new Point{3, 4};
delete pt;              // 소멸자 자동 호출
```

::right::

## 배열

```cpp {}
int n = 5;

// C 스타일
int* arr1 = (int*)malloc(n * sizeof(int));
free(arr1);

// C++ 스타일
int* arr2 = new int[n];         // 배열 할당
for (int i = 0; i < n; i++)
    arr2[i] = i * 10;
delete[] arr2;                  // ✅ 반드시 delete[] (대괄호 필수!)

// 초기값 지정
int* arr3 = new int[5]{1,2,3,4,5};
delete[] arr3;

// ❌ 혼용 금지
int* p = new int;
free(p);        // 💥 undefined behavior
int* arr = (int*)malloc(5 * sizeof(int));
delete[] arr;   // 💥 undefined behavior
```

---
layout: two-cols-header
---

# `new` vs `malloc` 차이

::left::

## malloc

```cpp {}
#include <stdlib.h>

// 1. 반환형이 void* — 캐스팅 필요
int* p = (int*)malloc(sizeof(int));

// 2. 실패 시 NULL 반환 → 직접 체크
if (p == NULL) { /* 처리 */ }

// 3. 생성자/소멸자 호출 안 함
struct Foo { Foo() { puts("생성"); } };
Foo* f = (Foo*)malloc(sizeof(Foo));
// 생성자 호출 안 됨!

free(p);
free(f);
```

::right::

## new

```cpp {}
// 1. 반환형이 정확한 타입 — 캐스팅 불필요
int* p = new int;

// 2. 실패 시 std::bad_alloc 예외 던짐
//    (예외 없이 nullptr 반환하려면 nothrow 사용)
int* p2 = new (std::nothrow) int;
if (p2 == nullptr) { /* 처리 */ }

// 3. 생성자/소멸자 자동 호출 ✅
struct Foo {
    Foo()  { puts("생성"); }
    ~Foo() { puts("소멸"); }
};
Foo* f = new Foo;   // "생성" 출력
delete f;           // "소멸" 출력

delete p;
```

---
layout: two-cols-header
---

# `const`와 포인터

`const`의 위치에 따라 의미가 달라진다.

::left::

## 세 가지 조합

```cpp {}
int a = 10, b = 20;

// 1. 가리키는 값이 const (읽기 전용 포인터)
const int* p1 = &a;
// *p1 = 99;   // ❌ 값 변경 불가
p1 = &b;       // ✅ 다른 변수를 가리키도록 변경 가능

// 2. 포인터 자체가 const (고정 포인터)
int* const p2 = &a;
*p2 = 99;      // ✅ 값 변경 가능
// p2 = &b;    // ❌ 다른 변수를 가리킬 수 없음

// 3. 둘 다 const
const int* const p3 = &a;
// *p3 = 99;   // ❌
// p3 = &b;    // ❌
```

::right::

## 읽는 방법 — 오른쪽에서 왼쪽으로

```cpp {}
const int* p   // p is a pointer to const int
                // → 가리키는 int값이 const

int* const p   // p is a const pointer to int
                // → p 자체가 const

const int* const p  // p is a const pointer to const int
                    // → 둘 다 const
```

## 함수 인자에서의 활용

```cpp {}
// 읽기만 할 때 — const int* (또는 const int&)
void print(const int* arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

// 수정할 때 — int*
void fill(int* arr, int n, int val) {
    for (int i = 0; i < n; i++)
        arr[i] = val;
}
```

---
layout: two-cols-header
---

# 포인터와 클래스

::left::

## `new`로 객체 생성

```cpp {}
class Student {
public:
    int  age;
    char name[32];

    Student(int a, const char* n) : age(a) {
        strcpy(name, n);
    }
    void greet() { printf("안녕, %s!\n", name); }
};

int main() {
    // 스택 할당 — 스코프 벗어나면 자동 소멸
    Student s1(20, "홍길동");
    s1.greet();

    // 힙 할당 — 직접 delete 필요
    Student* s2 = new Student(21, "이순신");
    s2->greet();     // 포인터는 -> 연산자
    delete s2;       // 소멸자 자동 호출
}
```

::right::

## 객체 배열

```cpp {}
// 스택 배열
Student arr[3] = {
    {20, "홍길동"},
    {21, "이순신"},
    {22, "강감찬"},
};

// 힙 배열 (기본 생성자 필요)
Student* heap_arr = new Student[3];
heap_arr[0].age = 20;
// heap_arr[0]->age  ← ❌ 배열 원소는 . 사용
delete[] heap_arr;   // ✅ delete[] 로 해제

// 포인터 배열 (각각 독립적으로 할당)
Student* ptrs[3];
ptrs[0] = new Student(20, "홍길동");
ptrs[1] = new Student(21, "이순신");
for (int i = 0; i < 2; i++)
    delete ptrs[i];
```

---
layout: two-cols-header
---

# 스마트 포인터 (Smart Pointer)

`new` / `delete`를 직접 쓰면 실수하기 쉽다. C++11부터는 **스마트 포인터**로 메모리를 자동 관리한다.

::left::

## `unique_ptr` — 단독 소유

```cpp {}
#include <memory>

// new 없이 make_unique 사용 (C++14)
auto p = std::make_unique<int>(42);

printf("%d\n", *p);    // 42 — 역참조
// delete 불필요 — 스코프 벗어나면 자동 해제

// 클래스 객체
auto s = std::make_unique<Student>(20, "홍길동");
s->greet();            // -> 연산자 동일

// 배열
auto arr = std::make_unique<int[]>(5);
arr[0] = 10;
// delete[] 불필요 — 자동 해제

// 소유권 이전 (복사 불가, 이동만 가능)
auto p2 = std::move(p);  // p → p2 로 소유권 이전
// p는 이제 nullptr
```

::right::

## `shared_ptr` — 공유 소유

```cpp {}
#include <memory>

// 여러 포인터가 같은 객체를 공유
auto a = std::make_shared<int>(99);
auto b = a;   // 복사 가능 — 참조 횟수 증가 (2)

printf("%d\n", *a);   // 99
printf("%d\n", *b);   // 99
printf("%ld\n", a.use_count());  // 2

b = nullptr;  // 참조 횟수 감소 (1)
// a가 소멸될 때 비로소 메모리 해제
```

## raw 포인터와 비교

| | `new`/`delete` | `unique_ptr` | `shared_ptr` |
|-|----------------|--------------|--------------|
| 소유자 | 프로그래머 | 단독 | 공유 |
| 해제 | 수동 | 자동 | 자동 |
| 복사 | 가능 | 불가 (이동만) | 가능 |

---
layout: default
---

# C vs C++ 포인터 비교 요약

| 항목 | C | C++ |
|------|---|-----|
| **null 포인터** | `NULL` (= 정수 0) | **`nullptr`** (타입 안전) |
| **동적 할당** | `malloc(size)` + 캐스팅 | **`new T`** (타입 추론, 캐스팅 불필요) |
| **배열 할당** | `malloc(n * sizeof(T))` | **`new T[n]`** |
| **해제** | `free(p)` | **`delete p`** / **`delete[] p`** |
| **실패 처리** | `NULL` 반환 체크 | `bad_alloc` 예외 (또는 `nothrow`) |
| **생성자/소멸자** | 호출 안 됨 | **자동 호출** |
| **자동 메모리 관리** | 없음 | **스마트 포인터** (`unique_ptr`, `shared_ptr`) |
| **참조 타입** | 없음 | **`int&`** — 포인터의 안전한 대안 |

<br>

```cpp {}
// C 스타일 — 여전히 C++에서 동작하지만 권장하지 않음
int* p = (int*)malloc(sizeof(int));
free(p);

// C++ 권장 스타일
auto p = std::make_unique<int>(0);   // 해제 불필요
```

<br>

> C++ 에서 raw 포인터(`new`/`delete`)는 꼭 필요한 경우에만 쓰고,
> 그 외엔 **스마트 포인터**나 **참조**를 사용하는 것이 현대 C++ 관례다.
