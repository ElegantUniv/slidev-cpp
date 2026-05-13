---
layout: cover
---

# C++ 프로그래밍
## 함수 포인터 (Function Pointer)

---
layout: two-cols-header
---

# 함수 포인터란?

함수도 메모리 주소를 갖는다. **함수 포인터**는 그 주소를 저장하는 변수다.

::left::

## 선언 · 대입 · 호출

```cpp {}
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

// 선언: 반환타입 (*이름)(매개변수 타입...)
int (*op)(int, int);

op = add;                  // 대입 — & 생략 가능
printf("%d\n", op(3, 4));  // 호출 → 7

op = sub;
printf("%d\n", op(3, 4));  // 호출 → -1

// 선언과 동시에 초기화
int (*fp)(int, int) = add;
```

::right::

## 포인터와의 비교

| | 데이터 포인터 | 함수 포인터 |
|---|---|---|
| 선언 | `int* p` | `int (*fp)(int)` |
| 대입 | `p = &x` | `fp = func` |
| 역참조 | `*p` | `(*fp)(arg)` 또는 `fp(arg)` |
| 용도 | 데이터 접근 | 함수 간접 호출 |

---
layout: two-cols-header
---

# 콜백 함수 (Callback Function)

**콜백**이란 "나중에 불러달라고 넘겨주는 함수"다. <br>
호출자(caller)가 피호출자(callee)에게 함수를 전달하면, 피호출자가 적절한 시점에 그 함수를 호출한다.

**활용 예시**

| 상황 | 콜백 역할 |
|------|----------|
| `qsort` | 정렬 기준 (비교 함수) |
| GUI 이벤트 | 버튼 클릭 시 실행할 함수 |
| 비동기 I/O | 작업 완료 후 호출할 함수 |
| 알고리즘 라이브러리 | 각 원소에 적용할 처리 함수 |

<br>

> 콜백의 핵심: **"무엇을 할지"를 함수로 분리해 전달** — 호출 시점과 호출 대상을 분리한다.


---
layout: two-cols-header
---

# 함수 포인터를 매개변수로 — 콜백

함수를 인자로 전달해 **호출 시점에 동작을 교체**한다.

> 아래 예제에서 `apply` 함수는 바뀌지 않는다. <br>
> 다만, **전달하는 콜백만 교체**해 `apply` 함수의 동작 원리를 바꾸는 것이다.

<br>

::left::

## 콜백 함수

```cpp {}
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

// op 자리에 어떤 함수든 전달 가능
int apply(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}

printf("%d\n", apply(3, 4, add));  // 7
printf("%d\n", apply(3, 4, mul));  // 12
```

::right::

## 콜백의 흐름

```txt {}
apply(3, 4, add)
│
├─ a=3, b=4 고정
└─ op = add  ◄── 콜백으로 전달
       │
       └─► add(3, 4) → 7

apply(3, 4, mul)
└─ op = mul  ◄── 다른 콜백 전달
       └─► mul(3, 4) → 12
```

<br>


---
layout: two-cols-header
---

# `qsort` — 콜백 기반 정렬

`qsort`는 **비교 함수를 콜백으로 받아** 정렬 기준을 런타임에 결정한다.

::left::

## 함수 시그니처

```cpp {}
// <cstdlib>
void qsort(
    void*  base,   // 배열 시작 주소
    size_t count,  // 원소 개수
    size_t size,   // 원소 하나의 크기 (bytes)
    int (*cmp)(const void*, const void*)  // 비교 콜백
);
```

<br>

## 비교 콜백 반환값 규칙

| 반환값 | 의미 | 결과 |
|--------|------|------|
| **음수** | `a < b` | a를 앞에 배치 |
| **0** | `a == b` | 순서 유지 |
| **양수** | `a > b` | b를 앞에 배치 |

::right::

## 콜백 등록 예제

```cpp {}
#include <cstdlib>
#include <cstdio>

int cmp_asc(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
    //  음수 → a 앞, 양수 → b 앞 (오름차순)
}

int cmp_desc(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
    //  반대 방향 (내림차순)
}

int arr[] = { 5, 2, 8, 1, 9 };

qsort(arr, 5, sizeof(int), cmp_asc);   // 콜백 등록
// arr → 1 2 5 8 9

qsort(arr, 5, sizeof(int), cmp_desc);  // 다른 콜백 등록
// arr → 9 8 5 2 1
```

> `qsort` 내부는 그대로다. **콜백만 바꿔** 정렬 기준을 교체한다.

---
layout: two-cols-header
---

# `typedef` — 가독성 개선 (C 스타일)

`typedef`로 함수 포인터 타입에 이름을 붙이면 선언이 간결해진다.

::left::

## 선언 문법

```cpp {}
// typedef 없이 — 복잡한 문법 반복
int (*op1)(int, int) = add;
int (*op2)(int, int) = sub;

void call(int (*cb)(int, int));

int (*table[4])(int, int);
```

<br>

```cpp {}
// typedef로 타입에 이름 부여
typedef int (*BinaryOp)(int, int);
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      반환타입 (*별칭이름)(매개변수 타입...)

BinaryOp op1 = add;
BinaryOp op2 = sub;

void call(BinaryOp cb);

BinaryOp table[4];
```

::right::

## 활용 예제

```cpp {}
typedef int (*BinaryOp)(int, int);

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int apply(int a, int b, BinaryOp op) {
    return op(a, b);
}

int main() {
    BinaryOp op = add;
    printf("%d\n", op(3, 4));          // 7

    printf("%d\n", apply(3, 4, add));  // 7
    printf("%d\n", apply(3, 4, mul));  // 12

    BinaryOp ops[] = { add, mul };
    printf("%d\n", ops[0](2, 3));      // 5
    printf("%d\n", ops[1](2, 3));      // 6
}
```

> `typedef`는 C에서도 사용 가능한 방식이다.

---
layout: two-cols-header
---

# `using` — 가독성 개선 (C++11)

C++11의 `using`은 `typedef`보다 **읽는 방향이 자연스럽고** 템플릿과도 함께 쓸 수 있다.

::left::

## 선언 문법

```cpp {}
// typedef — 오른쪽에서 왼쪽으로 읽어야 함
typedef int (*BinaryOp)(int, int);

// using — 왼쪽에서 오른쪽으로 자연스럽게 읽힘
using BinaryOp = int (*)(int, int);
//    ^^^^^^^^^   ^^^^^^^^^^^^^^^^^^
//    별칭이름  =  실제 타입
```

<br>

## 활용 예제

```cpp {}
using BinaryOp = int (*)(int, int);

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int apply(int a, int b, BinaryOp op) {
    return op(a, b);
}

BinaryOp op = add;
printf("%d\n", apply(3, 4, op));   // 7

BinaryOp ops[] = { add, mul };
printf("%d\n", ops[1](2, 3));      // 6
```

::right::

## `typedef` vs `using`

| | `typedef` | `using` |
|---|---|---|
| 도입 | C / C++ | C++11 |
| 가독성 | 오른쪽→왼쪽 | 왼쪽→오른쪽 |
| 템플릿 별칭 | ❌ 불가 | ✅ 가능 |
| 권장 여부 | C 호환 필요 시 | **C++에서 권장** |

<br>

```cpp {}
// using은 템플릿 별칭도 지원
template<typename T>
using Comparator = int (*)(const T*, const T*);

// typedef로는 이런 표현 불가
```

> C++ 코드에서는 `using`을 사용한다.
