---
layout: cover
---

# C++ 프로그래밍
## 스마트 포인터 (Smart Pointer)

---
layout: default
---

# 왜 스마트 포인터가 필요한가?

raw 포인터는 강력하지만, 직접 관리하면 실수하기 쉽다.

```cpp
void process(bool error) {
    int* data = new int[1000];

    if (error) {
        return;          // ❌ 메모리 누수! delete[] 없이 반환
    }

    // ... 작업 ...

    delete[] data;       // 정상 경로에서만 해제됨
}
```

raw 포인터의 세 가지 위험:

| 문제 | 설명 |
|------|------|
| **메모리 누수** | `delete` 없이 함수 반환, 예외 발생 시 해제 코드 미실행 |
| **댕글링 포인터** | `delete` 후 포인터를 계속 사용 |
| **이중 해제** | 같은 포인터를 두 번 `delete` → 크래시 |

<br>

> **스마트 포인터**는 객체가 소멸될 때 `delete`를 **자동으로 호출**해 이 문제를 해결한다.
> `#include <memory>` 하나로 사용 가능하다.

---
layout: two-cols-header
---

# RAII — 스마트 포인터의 원리

**RAII** (Resource Acquisition Is Initialization): 자원 획득을 초기화에 묶고, **소멸자에서 자동 해제**하는 C++ 관용구다.

::left::

## 직접 구현해보면

```cpp {}
// 스마트 포인터의 원리를 단순하게 구현
template <typename T>
class SimplePtr {
    T* raw;
public:
    explicit SimplePtr(T* p) : raw(p) {}

    // 소멸자에서 자동 해제
    ~SimplePtr() { delete raw; }

    // 포인터처럼 사용할 수 있도록
    T& operator*()  { return *raw; }
    T* operator->() { return raw; }
};

void use() {
    SimplePtr<int> p(new int(42));
    printf("%d\n", *p);
    // 함수 종료 시 ~SimplePtr() 자동 호출 → delete
}
```

::right::

## 표준 스마트 포인터 세 종류

```cpp {}
#include <memory>
```

<br>

| 타입 | 소유 방식 | 주 용도 |
|------|-----------|---------|
| `unique_ptr<T>` | **단독** 소유 | 일반적인 동적 할당 대체 |
| `shared_ptr<T>` | **공유** 소유 (참조 카운팅) | 여러 곳에서 공유 |
| `weak_ptr<T>` | **비소유** 관찰 | 순환 참조 방지 |

<br>

> 세 종류 중 **`unique_ptr`이 기본 선택**이다.
> 공유가 필요할 때만 `shared_ptr`을 쓰고,
> 순환 참조가 생길 때만 `weak_ptr`로 끊는다.

---
layout: two-cols-header
---

# `unique_ptr` — 단독 소유

하나의 `unique_ptr`만이 객체를 소유한다. **복사 불가, 이동만 가능**하다.

::left::

## 생성과 기본 사용

```cpp {}
#include <memory>

// ✅ make_unique 사용 권장 (C++14)
auto p = std::make_unique<int>(42);
printf("%d\n", *p);      // 42 — 역참조

// 클래스 객체
struct Point { int x, y; };
auto pt = std::make_unique<Point>(Point{3, 4});
printf("%d\n", pt->x);   // 3 — 멤버 접근

// 배열
auto arr = std::make_unique<int[]>(5);
arr[0] = 10;
arr[1] = 20;
// delete[] 불필요 — 스코프 종료 시 자동 해제
```

## 소유권 확인

```cpp {}
auto p = std::make_unique<int>(10);
printf("%p\n", p.get());    // raw 포인터 얻기

if (p) { /* p가 nullptr이 아니면 */ }
p.reset();                  // 명시적 해제, p = nullptr
```

::right::

## 복사 불가 — 이동(move)만 가능

```cpp {}
auto a = std::make_unique<int>(100);

// auto b = a;              // ❌ 복사 불가 — 컴파일 오류

// ✅ 소유권 이전 (move)
auto b = std::move(a);
// 이후 a는 nullptr, b가 소유자
printf("%d\n", *b);         // 100
if (a == nullptr) puts("a는 이제 비어 있음");

// 함수로 소유권 이전
void consume(std::unique_ptr<int> p) {
    printf("%d\n", *p);
}   // 함수 종료 시 p 소멸 → 자동 해제

consume(std::move(b));
// b도 이제 nullptr
```

---
layout: two-cols-header
---

# `unique_ptr` — 활용 패턴

::left::

## 팩토리 함수

```cpp {}
struct Animal {
    virtual void speak() = 0;
    virtual ~Animal() = default;
};
struct Dog : Animal {
    void speak() override { puts("멍멍"); }
};
struct Cat : Animal {
    void speak() override { puts("야옹"); }
};

// unique_ptr 반환 — 소유권을 호출자에게 넘김
std::unique_ptr<Animal> make_animal(bool dog) {
    if (dog) return std::make_unique<Dog>();
    else     return std::make_unique<Cat>();
}

int main() {
    auto a = make_animal(true);
    a->speak();   // "멍멍"
}   // a 소멸 → Dog 자동 해제
```

::right::

## 컨테이너에 담기

```cpp {}
#include <memory>
#include <vector>

std::vector<std::unique_ptr<Animal>> zoo;

zoo.push_back(std::make_unique<Dog>());
zoo.push_back(std::make_unique<Cat>());
zoo.push_back(std::make_unique<Dog>());

for (const auto& animal : zoo) {
    animal->speak();
    // "멍멍", "야옹", "멍멍"
}
// vector 소멸 시 모든 Animal 자동 해제
```

<br>

> `unique_ptr`를 컨테이너에 넣으면
> 다형성 객체를 안전하게 관리할 수 있다.

---
layout: two-cols-header
---

# `shared_ptr` — 공유 소유

여러 `shared_ptr`이 같은 객체를 공유한다. **참조 카운트가 0이 될 때** 자동 해제된다.

::left::

## 생성과 공유

```cpp {}
#include <memory>

// ✅ make_shared 사용 권장
auto a = std::make_shared<int>(99);
printf("카운트: %ld\n", a.use_count()); // 1

{
    auto b = a;   // 복사 가능 — 카운트 증가
    printf("카운트: %ld\n", a.use_count()); // 2

    auto c = a;   // 또 복사
    printf("카운트: %ld\n", a.use_count()); // 3

    *b = 200;
    printf("%d\n", *a);  // 200 — 같은 객체!
}   // b, c 소멸 → 카운트 감소

printf("카운트: %ld\n", a.use_count()); // 1
// a 소멸 시 카운트 0 → 비로소 메모리 해제
```

::right::

## 함수 간 공유

```cpp {}
void display(std::shared_ptr<int> p) {
    // 복사로 전달 — 카운트 증가
    printf("값: %d, 카운트: %ld\n",
           *p, p.use_count());
}

int main() {
    auto p = std::make_shared<int>(42);
    printf("카운트: %ld\n", p.use_count()); // 1

    display(p);
    // 함수 내부: 값: 42, 카운트: 2
    // 함수 반환 후: 카운트 다시 1

    printf("카운트: %ld\n", p.use_count()); // 1
}
```

> `shared_ptr`은 **참조 카운팅 비용**이 있다.
> 공유가 필요 없다면 `unique_ptr`이 더 효율적이다.

---
layout: two-cols-header
---

# `shared_ptr` — 순환 참조 문제

두 객체가 서로를 `shared_ptr`로 가리키면 **카운트가 절대 0이 되지 않아** 메모리가 해제되지 않는다.

::left::

## 문제 상황

```cpp {}
struct Node {
    int val;
    std::shared_ptr<Node> next;   // 다음 노드
    std::shared_ptr<Node> prev;   // 이전 노드 ← 문제!

    ~Node() { printf("Node %d 소멸\n", val); }
};

int main() {
    auto a = std::make_shared<Node>(1);
    auto b = std::make_shared<Node>(2);

    a->next = b;   // a → b (b 카운트: 2)
    b->prev = a;   // b → a (a 카운트: 2)
}
// main 종료: a, b 지역변수 소멸 → 카운트 각 1
// 💥 카운트가 1로 남아 소멸자 절대 호출 안 됨!
// → 메모리 누수
```

::right::

## `weak_ptr`로 해결

```cpp {}
struct Node {
    int val;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node>   prev;   // ✅ weak_ptr로 변경

    ~Node() { printf("Node %d 소멸\n", val); }
};

int main() {
    auto a = std::make_shared<Node>(1);
    auto b = std::make_shared<Node>(2);

    a->next = b;   // a → b (b 카운트: 2)
    b->prev = a;   // b ⇢ a (a 카운트: 1, weak은 불포함)
}
// main 종료: a 카운트 0 → "Node 1 소멸"
//           b 카운트 0 → "Node 2 소멸" ✅
```

---
layout: two-cols-header
---

# `weak_ptr` — 비소유 관찰

`weak_ptr`은 객체를 **소유하지 않고 관찰**만 한다. 참조 카운트에 영향을 주지 않는다.

::left::

## 생성과 접근

```cpp {}
auto sp = std::make_shared<int>(42);
std::weak_ptr<int> wp = sp;   // weak_ptr 생성

printf("카운트: %ld\n", sp.use_count()); // 1
                                          // weak은 카운트 불포함

// weak_ptr로 직접 접근 불가 — lock() 필요
// *wp = 10;   // ❌ 컴파일 오류

// lock(): shared_ptr 임시 생성 (원본이 살아있으면)
if (auto locked = wp.lock()) {
    printf("값: %d\n", *locked);  // 42
} else {
    puts("객체가 이미 소멸됨");
}
```

::right::

## 객체 소멸 후 접근

```cpp {}
std::weak_ptr<int> wp;

{
    auto sp = std::make_shared<int>(99);
    wp = sp;

    if (auto lk = wp.lock()) {
        printf("살아있음: %d\n", *lk);  // 99
    }
}   // sp 소멸 → 카운트 0 → 메모리 해제

// 이미 소멸된 객체에 접근 시도
if (auto lk = wp.lock()) {
    printf("살아있음\n");
} else {
    puts("이미 소멸됨");   // ← 이쪽 실행
}

// expired()로 소멸 여부 확인
printf("만료됨: %d\n", wp.expired()); // 1 (true)
```

---
layout: two-cols-header
---

# 커스텀 삭제자 (Custom Deleter)

`delete` 대신 **원하는 해제 로직**을 지정할 수 있다.

::left::

## unique_ptr 커스텀 삭제자

```cpp {}
#include <cstdio>
#include <memory>

// FILE* 를 스마트 포인터로 관리
auto file_deleter = [](FILE* f) {
    if (f) {
        fclose(f);
        puts("파일 닫힘");
    }
};

// 두 번째 타입 인자에 삭제자 타입 지정
std::unique_ptr<FILE, decltype(file_deleter)>
    fp(fopen("test.txt", "w"), file_deleter);

if (fp) {
    fprintf(fp.get(), "Hello, file!\n");
}
// 스코프 종료 시 file_deleter 자동 호출 → fclose
```

::right::

## shared_ptr 커스텀 삭제자

```cpp {}
// shared_ptr은 타입 인자 없이 삭제자 전달
auto sp = std::shared_ptr<FILE>(
    fopen("test.txt", "r"),
    [](FILE* f) {
        if (f) fclose(f);
    }
);

// C 라이브러리 핸들 관리 패턴
auto buf = std::shared_ptr<uint8_t>(
    (uint8_t*)malloc(1024),
    [](uint8_t* p) { free(p); }
);

// 여러 곳에서 공유해도 마지막에 free 한 번만 호출
auto buf2 = buf;
```

> C 라이브러리의 `FILE*`, `malloc` 메모리 등
> `delete`로 해제할 수 없는 자원도 안전하게 관리할 수 있다.

---
layout: two-cols-header
---

# `make_unique` vs `make_shared` vs `new` 직접 사용

::left::

## `new` 직접 사용의 문제

```cpp {}
// 함수 인자 평가 순서가 비결정적 → 잠재적 누수
void process(std::shared_ptr<int> p, int n);

process(
    std::shared_ptr<int>(new int(42)),  // A
    compute()                           // B
);
// A의 new와 shared_ptr 생성 사이에 B가 실행되고
// B에서 예외가 나면 new된 메모리가 누수될 수 있음

// ✅ make_shared/make_unique는 이 문제 없음
process(std::make_shared<int>(42), compute());
```

::right::

## `make_shared`의 메모리 효율

```cpp {}
// new 직접 사용: 할당이 두 번 발생
//   1. int 객체용 힙 메모리
//   2. 참조 카운트 블록용 힙 메모리
std::shared_ptr<int> p1(new int(42));

// make_shared: 할당이 한 번만 발생 ✅
//   객체 + 참조 카운트 블록을 한 번에 할당
auto p2 = std::make_shared<int>(42);
```

## 권장 사용법 정리

```cpp {}
// 항상 make 함수를 사용한다
auto up = std::make_unique<T>(args...);  // C++14
auto sp = std::make_shared<T>(args...);

// new를 직접 써야 하는 경우
// — 커스텀 삭제자가 필요할 때 (shared_ptr만 해당)
std::shared_ptr<T> p(new T, my_deleter);
```

---
layout: default
---

# 스마트 포인터 선택 가이드

```
동적 할당이 필요한가?
│
├─ 단독 소유 (기본 선택)
│      → unique_ptr<T>
│        make_unique<T>(args...)
│
├─ 여러 곳에서 공유해야 하는가?
│      → shared_ptr<T>
│        make_shared<T>(args...)
│
│        shared_ptr를 쓰는데 순환 참조가 생기는가?
│            → 한쪽을 weak_ptr<T>로 변경
│
└─ 이미 존재하는 C 자원 (FILE*, malloc 등)?
       → unique_ptr / shared_ptr + 커스텀 삭제자
```

<br>

| 상황 | 선택 |
|------|------|
| 함수 내 지역 동적 할당 | `unique_ptr` |
| 팩토리 함수 반환값 | `unique_ptr` |
| 컨테이너에 다형성 객체 저장 | `vector<unique_ptr<Base>>` |
| 캐시, 공유 설정 객체 | `shared_ptr` |
| 부모↔자식 양방향 참조 | 부모→자식 `shared_ptr`, 자식→부모 `weak_ptr` |
| 관찰자(Observer) 패턴 | `weak_ptr` |

---
layout: default
---

# 요약

```cpp {}
#include <memory>

// unique_ptr — 단독 소유, 복사 불가, 이동 가능
auto up = std::make_unique<T>(args...);
auto up2 = std::move(up);    // 소유권 이전

// shared_ptr — 공유 소유, 참조 카운팅
auto sp = std::make_shared<T>(args...);
auto sp2 = sp;               // 복사 가능, 카운트 증가
sp.use_count();              // 현재 참조 카운트

// weak_ptr — 비소유 관찰, 순환 참조 방지
std::weak_ptr<T> wp = sp;
if (auto lk = wp.lock()) {  // 살아있을 때만 접근
    // lk 사용
}
wp.expired();                // 소멸 여부 확인
```

<br>

| 타입 | 복사 | 이동 | 참조 카운트 | null 가능 | 주 용도 |
|------|------|------|-------------|-----------|---------|
| `unique_ptr` | ❌ | ✅ | 없음 | ✅ | 일반 동적 할당 |
| `shared_ptr` | ✅ | ✅ | 있음 | ✅ | 공유 소유 |
| `weak_ptr` | ✅ | ✅ | 불포함 | ✅ | 순환 참조 방지 |

<br>

> **규칙**: raw `new`/`delete`는 커스텀 삭제자가 필요한 경우 등 특수한 상황에서만 쓰고,
> 그 외 모든 동적 할당은 **스마트 포인터**로 대체하라.
