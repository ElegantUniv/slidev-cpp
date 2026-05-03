---
layout: cover
---

# C++ 프로그래밍
## 상속 (Inheritance)

---
layout: default
---

# 상속이란?

**기존 클래스(기본 클래스)의 멤버를 물려받아 새 클래스(파생 클래스)를 만드는** 기법이다.

```
      Shape
     /     \
 Circle   Rectangle
```

- **코드 재사용**: 공통 멤버를 기본 클래스에 한 번만 작성
- **is-a 관계**: "Circle은 Shape이다" — 파생 클래스는 기본 클래스의 일종
- **계층 확장**: 공통 인터페이스를 유지하면서 기능을 추가

```cpp {}
class Shape {              // 기본 클래스 (Base Class)
public:
    double x, y;
    Shape(double x, double y) : x(x), y(y) {}
    void print() const { printf("위치: (%.1f, %.1f)\n", x, y); }
};

class Circle : public Shape {  // 파생 클래스 (Derived Class)
    double radius;
public:
    Circle(double x, double y, double r) : Shape(x, y), radius(r) {}
    double area() const { return 3.14159 * radius * radius; }
};
```

---
layout: two-cols-header
---

# 기본 문법

`class 파생 : public 기본` 형태로 상속한다. 파생 클래스는 기본 클래스의 `public` / `protected` 멤버를 그대로 사용할 수 있다.

::left::

## 클래스 정의

```cpp {}
class Shape {
public:
    double x, y;
    Shape(double x, double y) : x(x), y(y) {}

    double area() const { return 0.0; }

    void print() const {
        printf("넓이: %.2f\n", area());
    }
};

class Circle : public Shape {
    double r;
public:
    Circle(double x, double y, double r)
        : Shape(x, y), r(r) {} // 기본 클래스 생성자 호출

    double area() const { return 3.14159 * r * r; }
};

class Rect : public Shape {
    double w, h;
public:
    Rect(double x, double y, double w, double h)
        : Shape(x, y), w(w), h(h) {}

    double area() const { return w * h; }
};
```

::right::

## 사용

```cpp {}
Circle c(1.0, 2.0, 5.0);
Rect   r(0.0, 0.0, 3.0, 4.0);

// 상속된 멤버 사용
printf("x=%.1f\n", c.x);     // Shape의 x
c.print();                     // Shape의 print() → area() 호출

// 파생 클래스 멤버
printf("%.2f\n", c.area());   // Circle::area
printf("%.2f\n", r.area());   // Rect::area
```

<br>

> `print()`는 `Shape`에 한 번만 정의했지만 `Circle`, `Rect` 모두에서 동작한다.

---
layout: two-cols-header
---

# `protected` 멤버

`private`은 파생 클래스에서도 접근 불가. `protected`는 **파생 클래스 내부에서만** 접근 가능하다.

::left::

```cpp {}
class Shape {
private:
    int id;           // 파생 클래스에서 접근 불가
protected:
    double x, y;      // 파생 클래스 내부에서 접근 가능
public:
    Shape(double x, double y) : id(0), x(x), y(y) {}
};

class Circle : public Shape {
    double r;
public:
    Circle(double x, double y, double r)
        : Shape(x, y), r(r) {}

    void move(double dx, double dy) {
        // id += 1;  // ❌ private — 접근 불가
        x += dx;    // ✅ protected — 파생 클래스 OK
        y += dy;    // ✅
    }
};
```

::right::

<br>

| 접근 지정자 | 같은 클래스 | 파생 클래스 | 외부 |
|------------|:-----------:|:-----------:|:----:|
| `public`    | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ❌ |
| `private`   | ✅ | ❌ | ❌ |

<br>

```cpp {}
Circle c(0, 0, 5);
// c.x = 1.0;  // ❌ protected — 외부 접근 불가
c.move(1.0, 2.0);  // ✅ public 함수로 간접 수정
```

> **설계 원칙**: 파생 클래스가 직접 수정해야 하는 멤버는 `protected`, 그 외에는 `private`으로 선언한다.

---
layout: two-cols-header
---

# 상속 접근 지정자

상속 시 지정자(`public` / `protected` / `private`)에 따라 **기본 클래스 멤버의 접근 수준이 바뀐다**.

::left::

```cpp {}
class Base {
public:    int pub;
protected: int prot;
private:   int priv;  // 항상 접근 불가
};

class PubDerived    : public    Base {};
class ProtDerived   : protected Base {};
class PrivDerived   : private   Base {};
```

::right::

| 기본 클래스 멤버 | `public` 상속 | `protected` 상속 | `private` 상속 |
|:---------------:|:-------------:|:----------------:|:--------------:|
| `public`        | `public`      | `protected`      | `private`      |
| `protected`     | `protected`   | `protected`      | `private`      |
| `private`       | 접근 불가     | 접근 불가        | 접근 불가      |

<br>

```cpp {}
PubDerived  pd;
pd.pub  = 1;   // ✅ public 상속 → pub은 public 유지

ProtDerived td;
// td.pub = 1; // ❌ protected 상속 → pub이 protected로 강등
```

> 일반적으로 **`public` 상속**만 사용한다. `protected` / `private` 상속은 "구현 상속"으로, 드물게 쓰인다.

---
layout: two-cols-header
---

# 생성자 & 소멸자 호출 순서

파생 클래스 객체를 만들 때 **기본 클래스 생성자가 먼저** 호출된다. 소멸은 반대 순서다.

::left::

```cpp {}
class Base {
public:
    Base()  { printf("Base 생성\n");  }
    ~Base() { printf("Base 소멸\n");  }
};

class Derived : public Base {
public:
    Derived() { printf("Derived 생성\n"); }
    ~Derived() { printf("Derived 소멸\n"); }
};

int main() {
    Derived d;
}
```

::right::

## 실행 결과

```
Base 생성
Derived 생성
Derived 소멸
Base 소멸
```

<br>

```
생성: Base → Derived  (기반 먼저)
소멸: Derived → Base  (역순)
```

> 생성자는 가장 깊은 기반 클래스부터, 소멸자는 가장 바깥 파생 클래스부터 호출된다.

---
layout: default
---

# 기본 클래스 생성자 호출

파생 클래스 생성자의 **초기화 목록**에서 기본 클래스 생성자를 명시적으로 호출할 수 있다.

```cpp {}
class Shape {
public:
    double x, y;
    Shape(double x, double y) : x(x), y(y) {
        printf("Shape(%g, %g) 생성\n", x, y);
    }
};

class Circle : public Shape {
    double r;
public:
    //           ↓ 기본 클래스 생성자 호출
    Circle(double x, double y, double r)
        : Shape(x, y), r(r) {   // Shape 먼저 초기화
        printf("Circle(r=%g) 생성\n", r);
    }
};

class Cylinder : public Circle {
    double h;
public:
    Cylinder(double x, double y, double r, double h)
        : Circle(x, y, r), h(h) {  // Circle → Shape 순으로 초기화
        printf("Cylinder(h=%g) 생성\n", h);
    }
};
```

> 초기화 목록에서 기본 클래스 생성자를 호출하지 않으면 **기본 생성자가 자동 호출**된다.
> 기본 생성자가 없으면 컴파일 오류.

---
layout: two-cols-header
---

# 함수 오버라이딩 vs 함수 숨김

파생 클래스에서 기본 클래스와 **같은 이름**의 함수를 정의하면 기본 클래스 버전이 **가려진다(hiding)**.

::left::

## 함수 숨김 (virtual 없이)

```cpp {}
class Shape {
public:
    void describe() const {
        printf("Shape\n");
    }
    double area() const { return 0.0; }
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : Shape(0,0), r(r) {}

    // Shape::area를 가린다 (hiding)
    double area() const {
        return 3.14159 * r * r;
    }
};
```

::right::

## 호출 결과

```cpp {}
Circle c(5.0);

c.area();           // Circle::area  ✅
c.Shape::area();    // Shape::area — 명시적 호출

Shape* p = &c;
p->area();  // ⚠️ Shape::area 호출!
            // 포인터 타입 기준 — 컴파일 타임 결정
```

<br>

| 방식 | 결정 시점 | 방법 |
|------|----------|------|
| **함수 숨김** | 컴파일 타임 | 포인터/참조 타입 기준 |
| **오버라이딩** | 런타임 | `virtual` + 실제 객체 타입 기준 |

> 포인터/참조를 통한 다형성이 목적이라면 `virtual`을 사용해야 한다.

---
layout: two-cols-header
---

# 업캐스팅 & 다운캐스팅

**업캐스팅**: 파생 → 기본 방향 변환. 항상 안전하며 암묵적으로 수행된다.  
**다운캐스팅**: 기본 → 파생 방향 변환. 명시적 변환이 필요하고 주의가 필요하다.

::left::

## 업캐스팅 (Upcasting)

```cpp {}
Circle c(0, 0, 5.0);

// 암묵적 업캐스팅 — 항상 안전
Shape* sp = &c;
Shape& sr = c;

sp->print();   // Shape::print 호출
// sp->area(); // ❌ Shape*로는 Circle 멤버 접근 불가
```

<br>

## `static_cast` 다운캐스팅

```cpp {}
Shape* p = new Circle(0, 0, 5.0);

// 타입이 맞다고 확신할 때만 사용
Circle* cp = static_cast<Circle*>(p);
printf("%.2f\n", cp->area());  // ✅

Shape* p2 = new Rect(0, 0, 3.0, 4.0);
Circle* wrong = static_cast<Circle*>(p2);
// ⚠️ 컴파일은 되지만 undefined behavior!
```

::right::

## `dynamic_cast` 다운캐스팅

```cpp {}
// dynamic_cast: 런타임에 타입 검사 (virtual 함수 필요)
Shape* p = new Circle(0, 0, 5.0);

Circle* cp = dynamic_cast<Circle*>(p);
if (cp) {
    printf("Circle: %.2f\n", cp->area()); // ✅
} else {
    printf("Circle이 아님\n");
}

Rect* rp = dynamic_cast<Rect*>(p);
// rp == nullptr — 타입 불일치
```

<br>

| | `static_cast` | `dynamic_cast` |
|---|---|---|
| 검사 시점 | 컴파일 타임 | 런타임 |
| 실패 시 | UB | `nullptr` |
| 속도 | 빠름 | 느림 |
| 요구 사항 | — | `virtual` 함수 |

---
layout: two-cols-header
---

# 다중 상속 (Multiple Inheritance)

C++는 여러 기본 클래스를 동시에 상속할 수 있다.

::left::

## 문법

```cpp {}
class Flyable {
public:
    void fly() { printf("날기\n"); }
};

class Swimmable {
public:
    void swim() { printf("수영\n"); }
};

// 두 클래스를 동시에 상속
class Duck : public Flyable,
             public Swimmable {
public:
    void quack() { printf("꽥꽥!\n"); }
};

int main() {
    Duck d;
    d.fly();    // Flyable::fly
    d.swim();   // Swimmable::swim
    d.quack();
}
```

::right::

## 다이아몬드 문제

```cpp {}
class Animal { public: int age; };
class Lion  : public Animal {};
class Tiger : public Animal {};

// Lion과 Tiger 각각 Animal을 상속
// → Duck에 Animal이 두 개 존재!
class Liger : public Lion, public Tiger {};

Liger li;
// li.age = 5;        // ❌ 모호함 — 어느 age?
li.Lion::age  = 5;   // ✅ 명시적 지정
li.Tiger::age = 5;   // ✅
```

<br>

**해결책**: `virtual` 상속으로 기본 클래스를 하나만 공유

```cpp {}
class Lion  : virtual public Animal {};
class Tiger : virtual public Animal {};
class Liger : public Lion, public Tiger {};
// 이제 age가 하나만 존재
```

---
layout: default
---

# 요약

| 개념 | 문법 | 핵심 |
|------|------|------|
| **상속** | `class D : public B` | is-a 관계, 멤버 재사용 |
| **protected** | `protected:` | 파생 클래스 내부에서만 접근 가능 |
| **상속 접근 지정자** | `public` / `protected` / `private` | 멤버 접근 수준 변환; 보통 `public` 사용 |
| **생성자 순서** | 초기화 목록 `: Base(args)` | 기본 → 파생 순 생성, 역순 소멸 |
| **함수 숨김** | 같은 이름 재정의 | 포인터 타입 기준 컴파일 타임 결정 |
| **업캐스팅** | 암묵적 변환 | 파생 → 기본, 항상 안전 |
| **다운캐스팅** | `static_cast` / `dynamic_cast` | 기본 → 파생, 주의 필요 |
| **다중 상속** | `class D : public A, public B` | 다이아몬드 문제 시 `virtual` 상속 |

<br>

> 상속은 **is-a 관계**일 때만 사용한다. 단순 코드 재사용이 목적이라면 포함(has-a)이 더 적합하다.
