---
layout: cover
---

# C++ 프로그래밍
## 다형성 (Polymorphism)

---
layout: default
---

# 다형성이란?

**같은 인터페이스로 서로 다른 타입의 객체를 동일하게 다루는** 능력이다.

| 종류 | 결정 시점 | 메커니즘 | 예 |
|------|----------|---------|-----|
| **정적 다형성** | 컴파일 타임 | 함수 오버로딩, 템플릿 | `print(int)` vs `print(double)` |
| **동적 다형성** | 런타임 | `virtual` 함수 + 포인터/참조 | `Animal* → Dog::speak()` |

<br>

```cpp {}
// 정적: 컴파일러가 오버로딩 중 어느 버전을 쓸지 결정
void draw(Circle c)    { /* ... */ }
void draw(Rectangle r) { /* ... */ }

// 동적: 런타임에 실제 객체 타입에 따라 함수 결정
void render(Shape* s) {
    s->draw();   // Circle? Rectangle? — 실행 중에 결정
}
```

> 동적 다형성의 핵심: **기본 클래스 포인터/참조를 통해 파생 클래스 객체를 다루면,
> 실제로 어떤 함수가 호출되는지는 런타임에 결정**된다.

---
layout: two-cols-header
---

# 정적 다형성 (Static Polymorphism)

컴파일 타임에 결정되는 다형성이다. 오버헤드가 없지만 **런타임 유연성은 없다**.

::left::

## 함수 오버로딩

```cpp {}
// 이름은 같지만 매개변수 타입이 다름
void print(int n)         { printf("%d\n",    n); }
void print(double d)      { printf("%.2f\n",  d); }
void print(const char* s) { printf("%s\n",    s); }

print(42);       // print(int)    호출
print(3.14);     // print(double) 호출
print("hello");  // print(const char*) 호출
```

컴파일러가 인수 타입을 보고 **호출할 함수를 컴파일 타임에 결정**한다.

::right::

## 함수 템플릿

```cpp {}
// 타입에 관계없이 동일 로직 적용
template<typename T>
T max_val(T a, T b) { return a > b ? a : b; }

printf("%d\n",   max_val(3, 5));       // max_val<int>
printf("%.1f\n", max_val(2.7, 1.3));   // max_val<double>
```

<br>

| | 정적 다형성 | 동적 다형성 |
|---|---|---|
| 결정 시점 | 컴파일 타임 | 런타임 |
| 성능 | 최적 | 간접 호출 1회 |
| 유연성 | 낮음 | 높음 |
| 새 타입 추가 | 재컴파일 필요 | 코드 수정 불필요 |

---
layout: two-cols-header
---

# 가상 함수 (Virtual Function)

`virtual` 키워드를 붙이면 **파생 클래스의 재정의 함수가 런타임에 호출**된다.

::left::

## virtual 없이 — 정적 바인딩

```cpp {}
class Animal {
public:
    void speak() const { printf("...\n"); }
};
class Dog : public Animal {
public:
    void speak() const { printf("왈왈!\n"); }
};
class Cat : public Animal {
public:
    void speak() const { printf("야옹!\n"); }
};

Animal* p = new Dog();
p->speak();    // ⚠️ "..." 출력
               // 포인터 타입(Animal) 기준 결정
delete p;
```

::right::

## virtual 있음 — 동적 바인딩

```cpp {}
class Animal {
public:
    virtual void speak() const { printf("...\n"); }
    virtual ~Animal() {}
};
class Dog : public Animal {
public:
    void speak() const override { printf("왈왈!\n"); }
};
class Cat : public Animal {
public:
    void speak() const override { printf("야옹!\n"); }
};

Animal* p = new Dog();
p->speak();    // ✅ "왈왈!" 출력
               // 실제 타입(Dog) 기준 결정
delete p;
```

---
layout: two-cols-header
---

# 다형성 활용 예시

기본 클래스 포인터/참조를 통해 파생 클래스 객체를 **동일한 코드로 처리**한다.

::left::

### 다형성을 활용한 클래스 함수

```cpp {}
#include <cstdio>
#include <string>

class Animal {
public:
    std::string name;
    Animal(const std::string& n) : name(n) {}
    virtual void speak() const { printf("%s: ...\n", name.c_str()); }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    Dog(const std::string& n) : Animal(n) {}
    void speak() const override { printf("%s: 왈왈!\n", name.c_str()); }
};

class Cat : public Animal {
public:
    Cat(const std::string& n) : Animal(n) {}
    void speak() const override { printf("%s: 야옹!\n", name.c_str()); }
};
```

::right::

### 메인함수에서의 활용

```cpp {}
int main() {
    Dog dog("멍멍이");
    Cat cat("냥냥이");
    Dog dog2("바둑이");

    Animal* zoo[] = { &dog, &cat, &dog2 };
    for (Animal* a : zoo) a->speak();
    // 출력: 멍멍이: 왈왈!  냥냥이: 야옹!  바둑이: 왈왈!
}
```

---
layout: default
---

# vtable & 동적 디스패치

`virtual` 함수를 가진 클래스는 컴파일러가 **가상 함수 테이블(vtable)**을 생성한다.

```
Animal 객체               Animal vtable
┌──────────┐             ┌────────────────────────────┐
│ vptr  ───┼────────────▶│ [0] Animal::speak          │
│ name     │             │ [1] Animal::~Animal        │
└──────────┘             └────────────────────────────┘

Dog 객체                  Dog vtable
┌──────────┐             ┌────────────────────────────┐
│ vptr  ───┼────────────▶│ [0] Dog::speak  (재정의됨) │
│ name     │             │ [1] Animal::~Animal        │
└──────────┘             └────────────────────────────┘
```

1. 컴파일러는 `virtual` 함수마다 vtable에 슬롯을 만든다
2. 각 객체 내부에 `vptr`(vtable 포인터)이 생긴다
3. `p->speak()` 호출 시 `p->vptr[0]`을 따라 실제 함수를 호출한다

> `virtual` 함수가 없으면 vptr도 없고, 직접 호출로 처리된다. 간접 참조가 1회 추가되지만 현대 CPU에서는 무시 가능한 수준이다.

---
layout: two-cols-header
---

# 순수 가상 함수 & 추상 클래스

`= 0`을 붙이면 **구현이 없는 순수 가상 함수**가 된다. 하나라도 있으면 추상 클래스다.

::left::

## 추상 클래스 (인터페이스 역할)

```cpp {}
class Shape {
public:
    // 파생 클래스에서 반드시 구현해야 함
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;

    // 일반 가상 함수 — 선택적 오버라이딩
    virtual void print() const {
        printf("넓이=%.2f\n", area());
    }

    virtual ~Shape() {}
};

// Shape s;   // ❌ 추상 클래스는 직접 생성 불가
// new Shape; // ❌
```

**용도**: 공통 인터페이스를 강제하는 기반 타입

::right::

## 구체 클래스 (Concrete Class)

```cpp {}
class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area()      const override { return 3.14159 * r * r; }
    double perimeter() const override { return 2 * 3.14159 * r; }
};

class Rect : public Shape {
    double w, h;
public:
    Rect(double w, double h) : w(w), h(h) {}
    double area()      const override { return w * h; }
    double perimeter() const override { return 2 * (w + h); }
};

Circle c(5);
Rect   r(3, 4);

Shape* shapes[] = { &c, &r };
for (Shape* s : shapes)
    s->print();   // 각 타입의 area() 호출
```

---
layout: two-cols-header
---

# 가상 소멸자 (Virtual Destructor)

기본 클래스 포인터로 `delete`할 때, **소멸자가 `virtual`이 아니면 파생 클래스 소멸자가 호출되지 않는다**.

::left::

## ❌ 가상 소멸자 없음 — 메모리 누수

```cpp {}
class Base {
public:
    ~Base() { printf("Base 소멸\n"); }
};

class Derived : public Base {
    int* data;
public:
    Derived() : data(new int[100]) {}
    ~Derived() {
        delete[] data;          // 실행되지 않음!
        printf("Derived 소멸\n");
    }
};

Base* p = new Derived();
delete p;
// 출력: "Base 소멸" 만 출력
// Derived::~Derived 미호출 → 메모리 누수!
```

::right::

## ✅ 가상 소멸자 — 올바른 소멸

```cpp {}
class Base {
public:
    virtual ~Base() { printf("Base 소멸\n"); }
};

class Derived : public Base {
    int* data;
public:
    Derived() : data(new int[100]) {}
    ~Derived() {
        delete[] data;
        printf("Derived 소멸\n");
    }
};

Base* p = new Derived();
delete p;
// 출력: "Derived 소멸"
//       "Base 소멸"
// 파생 → 기본 순서로 올바르게 소멸!
```

> **규칙**: 다형성으로 사용되는 기본 클래스는 **반드시 `virtual` 소멸자**를 선언한다.

---
layout: two-cols-header
---

# `override` & `final`

C++11 키워드로, 오버라이딩 실수를 **컴파일 타임에** 잡아낸다.

::left::

## `override`

```cpp {}
class Animal {
public:
    virtual void speak() const {}
    virtual void move()  const {}
};

class Dog : public Animal {
public:
    // ✅ 서명이 맞는지 컴파일러가 검증
    void speak() const override {}

    // ❌ 컴파일 오류 — Animal::move(int)는 없음
    // void move(int speed) const override {}

    // ⚠️ override 없으면 숨김(hiding) — 경고 없음
    void move(int speed) const {}
};
```

`override`가 없으면 오타나 서명 불일치를 잡지 못한다.

::right::

## `final`

```cpp {}
class Shape {
public:
    virtual double area() const = 0;
};

// Circle::area 이후 오버라이딩 금지
class Circle : public Shape {
    double r = 1.0;
public:
    double area() const override final {
        return 3.14159 * r * r;
    }
};

// ❌ Circle::area는 final이므로 오버라이딩 불가
// class Ellipse : public Circle {
//     double area() const override {}
// };

// 클래스 자체 봉인
class ImmutablePoint final {
    double x, y;
};
// class Sub : public ImmutablePoint {}; // ❌
```

---
layout: default
---

# 요약

| 개념 | 키워드 / 문법 | 핵심 |
|------|--------------|------|
| **정적 다형성** | 오버로딩, 템플릿 | 컴파일 타임 결정, 오버헤드 없음 |
| **동적 다형성** | `virtual` + 포인터/참조 | 런타임 결정, 확장에 열려있음 |
| **가상 함수** | `virtual void f()` | 파생 클래스 버전이 런타임에 호출됨 |
| **vtable** | 컴파일러 자동 생성 | 함수 포인터 배열 — 런타임 디스패치 |
| **순수 가상 함수** | `virtual f() = 0` | 추상 클래스, 인터페이스 강제 |
| **가상 소멸자** | `virtual ~Base()` | 다형성 클래스에 필수, 누수 방지 |
| **override** | `void f() override` | 오버라이딩 서명을 컴파일 타임에 검증 |
| **final** | `void f() final` | 이후 오버라이딩 금지 |

<br>

> 동적 다형성의 핵심: **기본 클래스 포인터/참조로 파생 클래스를 다루면
> `virtual` 함수 호출은 런타임에 실제 객체 타입이 결정한다.**
