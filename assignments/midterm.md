# C++ 프로그래밍 중간고사

**시험 시간**: 120분  
**총점**: 100점

---

> **주의사항**
> - 코드 관련 문제는 별도 언급이 없으면 컴파일 오류 없이 빌드된다고 가정한다.
> - 포인터 선언은 `int* p;` 형식을 사용한다.
> - 참조 선언은 `int& r;` 형식을 사용한다.
> - C++ 코드는 C++17 표준을 기준으로 한다.

---

## 1번 (5점) — 메모리 구조

다음 코드에서 각 항목이 저장되는 메모리 영역을 보기에서 골라 빈칸을 채워라.

**보기**: `Code` / `Data` / `Stack` / `Heap`

```c
int g1 = 100;               // (1) ___________

void func(void) {
    int local = 42;         // (2) ___________
    static int s = 0;       // (3) ___________

    int* p = (int*)malloc(sizeof(int));
    // p 변수 자체는 (4) ___________, *p 가 가리키는 공간은 (5) ___________
}
```

---
## 1번 (5점) — 메모리 누수(memory leak)

메모리 누수(Memory Leak)란 무엇인지 간단히 정의하시오.



## 1번 (5점) — Java의 Garbage Collection과 C++의 Smart Pointer의 차이점을 설명하시오.

Java의 Garbage Collection과 C++의 Smart Pointer의 차이점을 설명하시오.


---

## 2번 (6점) — 포인터 추적

다음 코드의 각 출력을 적어라.

```c
int arr[] = {10, 20, 30, 40, 50};
int* p = arr + 2;

printf("%d\n", *p);           // (1) ___
printf("%d\n", *(p + 1));     // (2) ___
printf("%d\n", p[-1]);        // (3) ___
*p = 99;
printf("%d\n", arr[2]);       // (4) ___
printf("%d\n", p[0]);         // (5) ___
printf("%d\n", arr[1] + arr[3]); // (6) ___
```

---

## 3번 (6점) — 메모리 오류 분류

다음 네 코드 조각에서 메모리 오류가 있으면 오류 종류를 적고, 없으면 "정상"을 적어라.

```c
// (1)
int* p = (int*)malloc(sizeof(int));
free(p);
p = NULL;
printf("%d\n", *p);
```

```c
// (2)
char buf[4];
strcpy(buf, "ABC");
printf("%s\n", buf);
```

```c
// (3)
int* arr = (int*)malloc(3 * sizeof(int));
arr[3] = 99;
free(arr);
```

```c
// (4)
int* p = (int*)malloc(sizeof(int));
int* q = p;
free(p);
free(q);
```

---

## 4번 (6점) — 변수 scope와 값 전달

다음 코드의 각 출력을 적어라.

```c
int g = 10;

void modify(int x) {
    x = 99;
    g = 99;
}

int counter(void) {
    static int count = 0;
    count++;
    return count;
}

int main(void) {
    int a = 5;
    modify(a);
    printf("%d %d\n", a, g);    // (1) ___ ___

    printf("%d\n", counter());  // (2) ___
    printf("%d\n", counter());  // (3) ___
    printf("%d\n", counter());  // (4) ___
    return 0;
}
```

---

## 5번 (6점) — 참조(Reference) 추적

다음 코드의 각 출력을 적어라.

```cpp
int a = 10, b = 20;
int& r = a;

printf("(1) %d %d\n", a, r);

r = b;
printf("(2) %d %d %d\n", a, r, b);

b = 99;
printf("(3) %d %d %d\n", a, r, b);
```

---

## 6번 (6점) — 참조 vs 포인터

다음 비교표의 빈칸을 채워라.

| 항목 | 포인터 (`int* p`) | 참조 (`int& r`) |
|------|---------------------|-----------------|
| 초기화 시점 | 선언 후 대입 가능 | (1) |
| null 가능 여부 | `nullptr` 가능 | (2) |
| 재지정 (rebind) | (3) | 불가 |
| 값 접근 문법 | `*p` | (4) |
| null 체크 필요 | (5) | (6) |

---

## 7번 (7점) — 생성자 / 소멸자 호출 순서

다음 코드의 출력을 순서대로 적어라.

```cpp
#include <cstdio>

class Res {
    int id;
public:
    Res(int i) : id(i) { printf("생성 %d\n", id); }
    ~Res()              { printf("소멸 %d\n", id); }
};

Res global(0);

void func() {
    Res r2(2);
    Res r3(3);
}

int main() {
    Res r1(1);
    func();
    printf("main 계속\n");
    return 0;
}
```

---

## 8번 (6점) — `const`와 포인터

다음 각 줄이 컴파일 가능하면 O, 불가능하면 X를 적어라.

```cpp
int a = 10, b = 20;
const int* p1 = &a;   // 읽기 전용 포인터
int* const p2 = &a;   // 고정 포인터

// (1) *p1 = 99;                             →
// (2) p1 = &b;                              →
// (3) *p2 = 99;                             →
// (4) p2 = &b;                              →
// (5) const int* const p3 = &a; *p3 = 1;   →
// (6) const int* p4 = &a; printf("%d\n", *p4); →
```

---

## 9번 (7점) — `enum class` 타입 안전성

다음 각 줄이 컴파일 가능하면 O, 불가능하면 X를 적어라.  
X인 경우 이유를 한 줄로 적어라.

```cpp
enum Color { RED, GREEN, BLUE };
enum class Direction { NORTH, EAST, SOUTH, WEST };

// (1) int n = RED;                                    →
// (2) Color c = 2;                                    →
// (3) Direction d = NORTH;                            →
// (4) Direction d = Direction::NORTH;                 →
// (5) if (RED == GREEN) { }                           →
// (6) if (Direction::NORTH == Direction::EAST) { }   →
// (7) int n = static_cast<int>(Direction::EAST);     →
```

---

## 10번 (7점) — `new` / `delete`

**(1)** 다음 코드에서 버그를 찾고 올바르게 수정하라.

```cpp
int* arr = new int[10];
arr[0] = 42;
delete arr;
```

**(2)** 다음 중 클래스 생성자가 호출되는 것을 모두 고르시오.

```cpp
struct Foo { Foo() { puts("생성"); } };

// a) Foo* p = (Foo*)malloc(sizeof(Foo));
// b) Foo* p = new Foo;
// c) Foo* p = new Foo();
// d) Foo f;
```

**(3)** `malloc`/`free`와 `new`/`delete`를 혼용해서는 안 되는 이유를 한 문장으로 설명하라.

---

## 11번 (6점) — `std::string`

다음 C 코드와 동일하게 동작하는 코드를 `std::string`을 사용해 C++로 작성하라.

```c
char s[50] = "Hello";
strcat(s, ", World");
printf("길이: %zu\n", strlen(s));

if (strcmp(s, "Hello, World") == 0)
    printf("일치\n");

char sub[6];
strncpy(sub, s, 5);
sub[5] = '\0';
printf("%s\n", sub);
```

---

## 12번 (9점) — 클래스 설계

다음 요구사항을 모두 만족하는 `Counter` 클래스를 작성하라.

- `count` : `private` 멤버 변수 (`int`)
- 생성자 : 초기값을 인자로 받으며, **초기화 리스트**를 사용한다. 기본값은 0.
- `increment()` : `count`를 1 증가. **메서드 체이닝**을 위해 `Counter&` 반환.
- `reset()` : `count`를 0으로 초기화. **메서드 체이닝**을 위해 `Counter&` 반환.
- `get()` : `count` 값 반환. **`const` 멤버 함수**로 선언.

다음 코드가 정상 동작해야 한다.

```cpp
Counter c(5);
c.increment().increment();   // count = 7
printf("%d\n", c.get());     // 7

c.reset().increment();        // count = 1
printf("%d\n", c.get());      // 1
```

---

## 13번 (6점) — 표준 입출력 버퍼링

**(1)** 다음 중 `stdout`이 **풀 버퍼링(full buffering)**으로 동작하는 경우를 모두 고르시오.

```
a) ./prog              (터미널에서 직접 실행)
b) ./prog > out.txt
c) ./prog | cat
d) ./prog 2> err.txt   (stdout은 터미널에 연결)
```

**(2)** 다음 코드에서 `std::endl`과 `"\n"`의 차이를 설명하고, 루프 안에서 `"\n"` 사용이 권장되는 이유를 쓰시오.

```cpp
for (int i = 0; i < 1000; i++) {
    std::cout << i << std::endl;  // ⚠️
    // std::cout << i << "\n";   // ✅
}
```

---

## 14번 (7점) — `unique_ptr` 코드 추적

다음 코드의 출력을 순서대로 적어라.

```cpp
#include <memory>
#include <iostream>

class Res {
    int id;
public:
    Res(int i) : id(i) { std::cout << "생성 " << id << "\n"; }
    ~Res()              { std::cout << "소멸 " << id << "\n"; }
};

int main() {
    auto p1 = std::make_unique<Res>(1);
    {
        auto p2 = std::make_unique<Res>(2);
        std::cout << "블록 안\n";
    }

    auto p3 = std::move(p1);
    std::cout << "이동 후\n";

    if (!p1) std::cout << "p1은 nullptr\n";

    return 0;
}
```

---

## 15번 (9점) — 종합: C → C++17 리팩토링

다음 C 스타일 코드를 C++17 스타일로 변환하라.

**변환 시 반드시 적용할 요소:**
- `char` 배열 → `std::string`
- 값 전달(`Student*`) → 적절한 참조 전달 (`const T&` 또는 `T&`)
- `NULL` → `nullptr`
- `malloc`/`free` → `std::make_unique` 또는 `new`/`delete`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int  score;
} Student;

void print_student(Student* s) {
    if (s == NULL) return;
    printf("이름: %s, 점수: %d\n", s->name, s->score);
}

void update_score(Student* s, int new_score) {
    s->score = new_score;
}

int main(void) {
    Student* p = (Student*)malloc(sizeof(Student));
    if (p == NULL) return 1;

    strcpy(p->name, "홍길동");
    p->score = 80;

    print_student(p);
    update_score(p, 95);
    print_student(p);

    free(p);
    return 0;
}
```
