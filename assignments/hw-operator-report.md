# C++ 프로그래밍 과제 보고서
## 연산자 오버로딩: C++과 Python 비교 분석

---

# 1. 이론 조사

## (1) 산술 연산자

### C++ 문법

산술 연산자는 **멤버 함수** 또는 **비멤버 함수** 두 가지 방식으로 오버로딩할 수 있다.

```cpp
// 멤버 함수 방식
Fraction Fraction::operator+(const Fraction& rhs) const;

// 비멤버 함수 방식 (friend)
friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
```

멤버 함수 방식은 왼쪽 피연산자가 반드시 해당 클래스 타입이어야 한다.
비멤버 함수 방식은 왼쪽 피연산자에도 암묵적 변환이 적용될 수 있어 대칭적 연산이 가능하다.
예를 들어 `2 + f` 형태를 지원하려면 비멤버 방식이 필요하다.

### Python 대응

| C++ | Python |
|-----|--------|
| `operator+` | `__add__` |
| `operator-` | `__sub__` |
| `operator*` | `__mul__` |
| `operator/` | `__truediv__` |
| `operator%` | `__mod__` |

### Reflected 연산자

Python에는 `__radd__`, `__rsub__` 등 **reflected 연산자**가 있다.
`2 + f`처럼 왼쪽 피연산자가 해당 클래스가 아닐 때, 먼저 `int.__add__(2, f)`를 시도하고 실패하면 `f.__radd__(2)`를 호출한다.

C++에서는 비멤버 함수로 `operator+(int, Fraction)`을 정의하거나 `int`에서 `Fraction`으로의 암묵적 변환 생성자를 두면 동일한 효과를 얻는다. Python처럼 명시적으로 분리된 reflected 메서드 개념은 없다.

---

## (2) 복합 대입 연산자

### C++ 문법

```cpp
Fraction& Fraction::operator+=(const Fraction& rhs) {
    *this = *this + rhs;
    return *this;   // *this 참조 반환 → 체이닝 가능
}
```

`*this`를 참조로 반환하는 이유는 `(a += b) += c` 같은 체이닝을 허용하기 위해서이다.
값으로 반환하면 임시 객체에 대입하는 결과가 되어 원본이 변경되지 않는다.

### 자동 생성 여부

C++에서 `operator+=`를 정의해도 `operator+`가 자동으로 생성되지 않는다. 반대도 마찬가지이다.
다만 관례적으로 `operator+`를 `operator+=`를 이용해 구현하면 중복 코드를 줄일 수 있다.

```cpp
Fraction operator+(Fraction lhs, const Fraction& rhs) {
    lhs += rhs;   // operator+= 재사용
    return lhs;
}
```

Python도 동일하다. `__add__`와 `__iadd__`는 독립적이며, 한쪽만 정의한다고 다른 쪽이 생기지 않는다.

---

## (3) 비교 연산자

### C++ 문법 (C++20 이전 / 이후)

**C++20 이전**: `==`, `!=`, `<`, `>`, `<=`, `>=` 각각 개별 정의 필요.
`operator==`를 정의해도 `operator!=`는 자동 생성되지 않는다.
관례적으로 `operator!=`는 `!(*this == rhs)`로 구현한다.

**C++20 이후**: 삼중 비교 연산자(spaceship operator) `<=>`를 정의하면 나머지 비교 연산자가 자동으로 생성된다.

```cpp
// C++20
auto operator<=>(const Fraction& rhs) const = default;
```

### Python 대응

| C++ | Python |
|-----|--------|
| `operator==` | `__eq__` |
| `operator!=` | `__ne__` |
| `operator<`  | `__lt__` |
| `operator<=` | `__le__` |
| `operator>`  | `__gt__` |
| `operator>=` | `__ge__` |

Python 3에서는 `__eq__`만 정의하면 `!=`는 자동으로 그 부정으로 동작한다.
C++20의 `<=>` 연산자는 Python의 `__lt__` 하나로 `functools.total_ordering`을 쓰는 관례와 유사한 방향성이다.

---

## (4) 단항 연산자

### C++ 문법

이항 `operator-`와 단항 `operator-`는 **매개변수 수**로 구별한다.

```cpp
Fraction operator-(const Fraction& rhs) const;   // 이항: 매개변수 1개 (멤버 함수)
Fraction operator-() const;                       // 단항: 매개변수 없음 (멤버 함수)
```

비멤버 함수로 정의할 경우:

```cpp
Fraction operator-(const Fraction& lhs, const Fraction& rhs);   // 이항: 매개변수 2개
Fraction operator-(const Fraction& operand);                     // 단항: 매개변수 1개
```

### Python 대응

| C++ | Python |
|-----|--------|
| 단항 `operator-` | `__neg__` |
| 단항 `operator+` | `__pos__` |
| `operator~`      | `__invert__` |

---

## (5) 첨자 연산자

### C++ 문법

C++의 `operator[]`는 하나의 함수가 읽기와 쓰기를 모두 처리한다.
**참조(reference)를 반환**하기 때문에 왼쪽 값(lvalue)으로도 사용할 수 있다.

```cpp
int& operator[](int index);             // 비-const: 읽기/쓰기 가능 (참조 반환)
const int& operator[](int index) const; // const: 읽기만 가능
```

`const` 버전과 비-`const` 버전을 모두 제공해야 하는 이유는, `const Fraction`으로 선언된 객체에서도 `[]`를 사용할 수 있게 하기 위해서이다.

### Python 대응

Python은 읽기와 쓰기가 **별도 메서드**로 분리되어 있다.

| 역할 | C++ | Python |
|------|-----|--------|
| 읽기 | `operator[]` (const 버전) | `__getitem__` |
| 쓰기 | `operator[]` (비-const 버전, 참조 반환) | `__setitem__` |
| 삭제 | 없음 | `__delitem__` |

C++은 참조 반환이라는 언어 메커니즘을 활용해 읽기/쓰기를 하나의 함수로 처리하는 반면,
Python은 두 연산을 명시적으로 분리해 의도를 더 명확하게 표현한다.

---

## (6) 함수 호출 연산자

### C++ 문법

```cpp
class Adder {
public:
    Adder(int base) : base_(base) {}
    int operator()(int x) const { return base_ + x; }
private:
    int base_;
};

Adder add5(5);
std::cout << add5(3);   // 8
```

`operator()`를 구현한 객체를 **함수 객체(functor)**라고 한다.
일반 함수와 달리 **상태(state)를 가질 수 있다**는 점이 핵심이다.

C++ 람다는 내부적으로 `operator()`를 가진 익명 구조체로 컴파일된다.
즉 람다는 함수 객체의 syntactic sugar이다.

### Python 대응

```python
class Adder:
    def __init__(self, base):
        self.base = base
    def __call__(self, x):
        return self.base + x

add5 = Adder(5)
print(add5(3))   # 8
```

Python의 `__call__`과 C++의 `operator()`는 개념과 사용법이 사실상 동일하다.

---

## (7) 출력 연산자와 문자열 변환

### C++에서 비멤버 함수로 정의하는 이유

`operator<<`의 왼쪽 피연산자는 `std::ostream`이다.
멤버 함수로 정의하면 왼쪽 피연산자가 자신의 클래스가 되어야 하므로 `f << cout` 형태가 되어버린다.
따라서 반드시 **비멤버 함수**로 정의해야 `cout << f` 형태로 사용할 수 있다.

```cpp
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    if (f.den_ == 1) os << f.num_;
    else             os << f.num_ << "/" << f.den_;
    return os;
}
```

`std::ostream&`을 반환하는 이유는 **체이닝**을 위해서이다.

```cpp
cout << a << " + " << b << " = " << (a + b) << endl;
// 위 식은 다음과 동일하다:
// operator<<(operator<<(operator<<(cout, a), " + "), b) ...
```

### C++ vs Python 비교

| 관점 | C++ `operator<<` | Python `__str__` |
|------|-----------------|-----------------|
| 반환값 | `ostream&` (스트림 반환) | `str` (문자열 반환) |
| 출력 대상 | `ostream` 인자로 결정 | 호출하는 쪽이 결정 |
| 체이닝 | `cout << a << b` 가능 | 해당 없음 |
| 다양한 스트림 | `cout`, `cerr`, `fstream` 모두 동작 | `str()` 결과를 원하는 곳에 전달 |

공통점은 "객체를 어떻게 텍스트로 표현할지 정의한다"는 것이다.
차이는 C++은 **어디에 출력할지**도 연산자가 제어하는 반면, Python은 문자열 생성과 출력 목적지를 분리한다.

---

## (8) bool 변환 연산자

### C++ 문법

```cpp
explicit operator bool() const { return num_ != 0; }
```

`explicit`를 붙이는 이유: `explicit` 없이 정의하면 `Fraction`이 산술식에서 암묵적으로 `int`로 변환되는 의도치 않은 동작이 발생할 수 있다.

```cpp
Fraction f(1, 2);
int n = f + 1;   // explicit 없으면 컴파일됨 → 버그 가능성
```

`explicit`가 있으면 `if (f)`, `while (f)`, `static_cast<bool>(f)` 처럼 명시적 bool 문맥에서만 변환이 일어난다.

### Python 대응

```python
def __bool__(self):
    return self.num != 0
```

`if obj:` 구문에서 두 언어 모두 동일하게 동작한다.
Python에서 `__bool__`을 정의하지 않으면 `__len__`을 시도하고, 그것도 없으면 항상 `True`를 반환한다.
C++은 변환 연산자가 없으면 `if (obj)` 자체가 컴파일 오류가 된다.

---

## (9) C++에만 있는 연산자

| C++ 연산자 | Python에 없는 이유 |
|-----------|-----------------|
| `++`, `--` | Python에 해당 연산자 자체가 없다. 증감은 `+= 1`로 표현한다. |
| `->` | Python에는 포인터 개념이 없다. 멤버 접근은 언제나 `.`이다. |
| `&&`, `\|\|` | Python의 `and`/`or`는 단락 평가(short-circuit)를 언어가 보장하며 오버로딩할 수 없다. `__bool__`로 피연산자의 진리값만 제어할 수 있다. |
| `new`, `delete` | Python은 가비지 컬렉션으로 메모리를 관리하므로 수동 메모리 연산자가 없다. |

---

# 2. 구현

## 2-1. C++ 구현 핵심 설명

### 불변 조건 유지

모든 `Fraction` 객체는 **항상 기약분수이며 분모가 양수**인 상태를 유지한다.
이 불변 조건은 생성자에서만 설정하면 된다. 산술 연산자는 생성자를 통해 새 객체를 반환하므로 자동으로 보장된다.

```cpp
Fraction(int numerator, int denominator) : num_(numerator), den_(denominator) {
    if (den_ == 0) throw std::invalid_argument("denominator cannot be zero");
    if (den_ < 0) { num_ = -num_; den_ = -den_; }
    reduce();
}
```

### operator+= 구현 전략

`operator+=`를 직접 계산하는 대신 `operator+`를 재사용한다.
코드 중복을 제거하고, 생성자의 정규화 로직도 자동으로 적용된다.

```cpp
Fraction& operator+=(const Fraction& rhs) {
    *this = *this + rhs;
    return *this;
}
```

### operator== 구현

항상 기약분수 불변 조건이 보장되므로, `1/2`와 `2/4`는 둘 다 내부적으로 `(1, 2)`로 저장된다.
따라서 분자와 분모를 직접 비교하는 것으로 충분하다.
크로스 곱(`num_ * rhs.den_ == rhs.num_ * den_`)은 불필요하다.

```cpp
bool operator==(const Fraction& rhs) const {
    return num_ == rhs.num_ && den_ == rhs.den_;
}
```

## 2-2. Python 구현 핵심 설명

### __iadd__ 구현 전략

C++과 동일하게 `__add__`를 재사용한다.
`__iadd__`는 반드시 `self`를 반환해야 한다. 그렇지 않으면 `a += b` 이후 `a`가 `None`이 된다.

```python
def __iadd__(self, other):
    result = self + other
    self.num = result.num
    self.den = result.den
    return self
```

### __str__ vs __repr__

```python
def __str__(self):
    return f"{self.num}" if self.den == 1 else f"{self.num}/{self.den}"

def __repr__(self):
    return f"Fraction({self.num}, {self.den})"
```

`__str__`은 사람이 읽는 형식(`1/2`)이고, `__repr__`은 `eval()`로 재현 가능한 형식(`Fraction(1, 2)`)이다.
`print(f)`는 `__str__`을, 대화형 인터프리터에서 객체를 직접 입력하면 `__repr__`을 사용한다.

---

# 3. 실행 결과

두 구현의 실행 결과는 동일하다 (Python의 `True`/`False` 대소문자는 언어 표준 차이).

```
1/2 + 1/3 = 5/6
1/2 - 1/3 = 1/6
1/2 * 1/3 = 1/6
1/2 / 1/3 = 3/2
-1/2 = -1/2
1/2 == 1/2 : true
1/2 <  1/3 : false
1/2 is nonzero
0 is zero
a += b : 5/6
분자: 5, 분모: 6
-1/2
3/2
2
```

---

# 4. 분석 및 결론

### (1) `operator<<`와 `__str__`의 설계 철학 차이

두 방식 모두 "객체를 텍스트로 어떻게 표현할지"를 정의한다는 공통 목적을 가진다.

차이는 **책임의 위치**에 있다.
C++의 `operator<<`는 출력 형식과 출력 대상(스트림)을 하나의 연산자 안에서 처리한다.
이 덕분에 같은 코드가 `cout`, `cerr`, `fstream`, `stringstream`에 모두 동작한다.

Python의 `__str__`은 문자열을 반환할 뿐이며, 그 문자열을 어디로 보낼지는 호출하는 쪽의 책임이다.
두 관심사를 분리했기 때문에 더 유연하지만, C++처럼 스트림 체이닝을 직접 제어할 수는 없다.

### (2) C++의 `operator[]`가 읽기/쓰기를 구분하는 메커니즘

C++은 **참조(reference) 반환**과 **const 오버로딩**을 조합해 하나의 함수로 두 역할을 처리한다.

```cpp
int& operator[](int i);             // 비-const 객체 → 참조 반환 → 쓰기 가능
const int& operator[](int i) const; // const 객체 → const 참조 반환 → 읽기만 가능
```

`v[0] = 5;`처럼 왼쪽 값으로 쓰일 때는 비-const 버전이 호출되어 참조를 반환하고,
그 참조에 대입이 이루어진다. Python이 `__getitem__`과 `__setitem__`을 명시적으로 분리한 것과 대조적으로,
C++은 타입 시스템(const/비-const, lvalue)을 활용해 암묵적으로 구분한다.

### (3) 두 언어로 구현하며 느낀 차이

가장 큰 차이는 **불변 조건 유지 방식**이다.
C++에서는 `private` 멤버와 생성자를 통해 불변 조건(`항상 기약분수, 분모 양수`)을 컴파일러가 강제한다.
외부에서 `num_`, `den_`을 직접 바꿀 수 없으므로 한 번 올바르게 만들어진 객체는 이후에도 올바름이 보장된다.

Python에서는 관례적으로 `_`를 붙이거나 `@property`로 접근을 제한할 수 있지만 언어 차원의 강제가 아니다.
대신 코드가 더 짧고 직관적이며, `__iadd__`에서 `self + other`를 호출하면 `__init__`의 정규화가 자동 적용되는 등 덕 타이핑의 유연함을 활용할 수 있었다.

두 언어 모두 연산자 오버로딩의 **핵심 목적(코드 가독성 향상)** 은 동일하다.
`a + b`, `a == b`, `cout << a` 형태의 코드는 내부 구현을 모르더라도 의미를 즉시 파악할 수 있다.
C++은 이를 타입 안전성과 성능을 유지하면서 달성하고, Python은 더 간결한 문법으로 달성한다.

---

# Appendix: 코드

## A. C++ (`fraction.cpp`)

```cpp
#include <iostream>
#include <numeric>
#include <stdexcept>

class Fraction {
public:
    Fraction(int numerator, int denominator) : num_(numerator), den_(denominator) {
        if (den_ == 0)
            throw std::invalid_argument("denominator cannot be zero");
        if (den_ < 0) { num_ = -num_; den_ = -den_; }
        reduce();
    }

    Fraction operator+(const Fraction& rhs) const {
        return Fraction(num_ * rhs.den_ + rhs.num_ * den_, den_ * rhs.den_);
    }
    Fraction operator-(const Fraction& rhs) const {
        return Fraction(num_ * rhs.den_ - rhs.num_ * den_, den_ * rhs.den_);
    }
    Fraction operator*(const Fraction& rhs) const {
        return Fraction(num_ * rhs.num_, den_ * rhs.den_);
    }
    Fraction operator/(const Fraction& rhs) const {
        return Fraction(num_ * rhs.den_, den_ * rhs.num_);
    }

    Fraction operator-() const { return Fraction(-num_, den_); }

    Fraction& operator+=(const Fraction& rhs) {
        *this = *this + rhs;
        return *this;
    }

    bool operator==(const Fraction& rhs) const {
        return num_ == rhs.num_ && den_ == rhs.den_;
    }
    bool operator!=(const Fraction& rhs) const { return !(*this == rhs); }
    bool operator<(const Fraction& rhs) const {
        return num_ * rhs.den_ < rhs.num_ * den_;
    }

    explicit operator bool() const { return num_ != 0; }

    int operator[](int index) const {
        if (index == 0) return num_;
        if (index == 1) return den_;
        throw std::out_of_range("index must be 0 or 1");
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.den_ == 1) os << f.num_;
        else             os << f.num_ << "/" << f.den_;
        return os;
    }

private:
    int num_;
    int den_;

    void reduce() {
        int g = std::gcd(std::abs(num_), den_);
        num_ /= g;
        den_ /= g;
    }
};
```

## B. Python (`fraction.py`)

```python
from math import gcd

class Fraction:
    def __init__(self, numerator: int, denominator: int):
        if denominator == 0:
            raise ValueError("denominator cannot be zero")
        if denominator < 0:
            numerator, denominator = -numerator, -denominator
        g = gcd(abs(numerator), denominator)
        self.num = numerator // g
        self.den = denominator // g

    def __add__(self, other):
        return Fraction(self.num * other.den + other.num * self.den,
                        self.den * other.den)
    def __sub__(self, other):
        return Fraction(self.num * other.den - other.num * self.den,
                        self.den * other.den)
    def __mul__(self, other):
        return Fraction(self.num * other.num, self.den * other.den)
    def __truediv__(self, other):
        return Fraction(self.num * other.den, self.den * other.num)

    def __neg__(self):
        return Fraction(-self.num, self.den)

    def __iadd__(self, other):
        result = self + other
        self.num = result.num
        self.den = result.den
        return self

    def __eq__(self, other):
        return self.num == other.num and self.den == other.den
    def __lt__(self, other):
        return self.num * other.den < other.num * self.den

    def __bool__(self):
        return self.num != 0

    def __getitem__(self, index):
        if index == 0: return self.num
        if index == 1: return self.den
        raise IndexError("index must be 0 or 1")

    def __str__(self):
        return str(self.num) if self.den == 1 else f"{self.num}/{self.den}"
    def __repr__(self):
        return f"Fraction({self.num}, {self.den})"
```
