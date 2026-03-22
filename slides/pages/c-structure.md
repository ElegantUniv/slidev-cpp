---
layout: cover
---

# C 프로그래밍
## 구조체 (Structure)

---
layout: default
---

# 구조체란?

**여러 타입의 데이터를 하나의 이름으로 묶는 사용자 정의 타입**이다.

```c
// ❌ 관련 데이터가 흩어져 있음
char name[32];
int  age;
double gpa;

// ✅ 구조체로 묶으면 하나의 단위로 다룰 수 있음
struct Student {
    char   name[32];
    int    age;
    double gpa;
};
```

<br>

> 구조체를 쓰면 **관련 데이터를 하나의 타입으로 추상화**할 수 있어,
> 함수에 전달하거나 배열로 만들기가 쉬워진다.

---
layout: two-cols-header
---

# 구조체 선언과 초기화

::left::

## 선언

```c {}
struct Point {
    int x;
    int y;
};
```

- `struct` 키워드 + 태그 이름으로 타입 정의
- 멤버(member)는 중괄호 안에 나열
- 세미콜론으로 끝남

## 초기화

```c {}
// 순서대로 초기화
struct Point p1 = {3, 4};

// 지정 초기화 (C99)
struct Point p2 = {.x = 10, .y = 20};
```

::right::

## 예제

<<< @/snippets/c-structure/struct_basic.c c

---
layout: two-cols-header
---

# typedef — 타입 이름 단순화

`typedef`를 쓰면 `struct` 키워드를 반복하지 않아도 된다.

::left::

## typedef 없이

```c {}
struct Student {
    char name[32];
    int  age;
};

struct Student s;           // struct 필요
struct Student arr[10];
```

## typedef 사용

```c {}
typedef struct {
    char name[32];
    int  age;
} Student;

Student s;                  // struct 불필요
Student arr[10];
```

::right::

## 멤버 접근 — `.` 연산자

```c {}
Student s;

// 멤버에 값 쓰기
s.age = 20;

// 문자열은 strcpy 사용
#include <string.h>
strcpy(s.name, "홍길동");

// 멤버 읽기
printf("%s, %d세\n", s.name, s.age);
```

<br>

> 변수로 선언된 구조체는 `.` 연산자로 멤버에 접근한다.

---
layout: two-cols-header
---

# 구조체 포인터와 `->` 연산자

포인터를 통해 구조체 멤버에 접근할 때는 `->` 연산자를 사용한다.

::left::

## `.` vs `->`

```c {}
Student  s;
Student* p = &s;

// 아래 두 표현은 동일하다
p->age  = 20;        // -> 연산자 (권장)
(*p).age = 20;       // 역참조 후 .
```

## 함수에 구조체 전달

```c {}
// 값 전달 — 복사본이 생성됨 (원본 불변)
void print(Student s) { ... }

// 포인터 전달 — 원본을 직접 수정 가능
void birthday(Student* s) {
    s->age += 1;
}
```

::right::

## 예제

<<< @/snippets/c-structure/struct_pointer.c c

---
layout: two-cols-header
---

# 구조체와 함수

::left::

## 값 전달 (복사)

```c {}
typedef struct { int x; int y; } Point;

// 구조체 전체가 복사됨
void print_point(Point p) {
    printf("(%d, %d)\n", p.x, p.y);
}

// 반환도 가능
Point make_point(int x, int y) {
    Point p = {x, y};
    return p;
}
```

- 원본이 변경되지 않음
- 구조체가 크면 복사 비용 발생

::right::

## 포인터 전달 (권장)

```c {}
// const: 읽기 전용임을 명시
void print_point(const Point* p) {
    printf("(%d, %d)\n", p->x, p->y);
}

// 수정이 필요하면 const 생략
void move(Point* p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}
```

- 복사 없이 원본에 직접 접근
- `const`로 의도를 명확히 표현

---
layout: two-cols-header
---

# 구조체 배열과 동적 할당

::left::

## 구조체 배열

```c {}
Student class[30];          // 30명 분량

for (int i = 0; i < 30; i++) {
    class[i].age = 20 + i;
}
```

## 동적 할당

```c {}
int n = 3;
Student* students =
    (Student*)malloc(n * sizeof(Student));

if (students == NULL) return 1;

students[0].age = 20;    // 배열처럼 접근
(students + 1)->age = 21; // 포인터 연산

free(students);
```

::right::

## 예제

<<< @/snippets/c-structure/struct_dynamic.c c

---
layout: default
---

# 요약

```c {}
#include <string.h>   // strcpy
#include <stdlib.h>   // malloc, free
```

| 주제 | 핵심 |
|------|------|
| **선언** | `struct 태그 { 멤버; };` |
| **typedef** | `struct` 반복 없이 타입명만으로 사용 |
| **초기화** | `= {값, ...}` 또는 지정 초기화 `{.멤버 = 값}` |
| **멤버 접근** | 변수 → `.` 연산자, 포인터 → `->` 연산자 |
| **함수 전달** | 읽기만 할 때 `const Student*`, 수정 시 `Student*` |
| **동적 할당** | `malloc(n * sizeof(Student))` |

<br>

> 구조체는 **관련 데이터를 하나의 타입으로 묶는** C의 핵심 추상화 도구다.
> C++의 클래스(class)는 구조체에서 발전한 개념이다.
