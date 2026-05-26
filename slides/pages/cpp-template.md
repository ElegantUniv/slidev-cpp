---
layout: cover
---

# C++ 프로그래밍
## 템플릿 (Template)

---
layout: two-cols-header
---

# 코드 중복 문제

타입만 다르고 로직이 같은 함수를 **타입별로 따로** 작성해야 할까?

::left::

### 타입별로 각각 작성

```cpp {}
void swap_int(int& a, int& b) {
  int tmp = a; a = b; b = tmp;
}

void swap_double(double& a, double& b) {
  double tmp = a; a = b; b = tmp;
}

void swap_str(std::string& a, std::string& b) {
  std::string tmp = a; a = b; b = tmp;
}
```

::right::

### 문제점

- 로직이 **완전히 동일**하지만 타입만 다름
- 새 타입이 생길 때마다 **함수를 추가**해야 함
- 한 곳의 버그가 **모든 함수에 복사**됨
- 코드 유지보수 부담 증가

<br>

> 해결책: **타입을 매개변수처럼** 다루는 **템플릿**

---
layout: two-cols-header
---

# 함수 템플릿 — 기본 문법

`template<typename T>`로 타입을 매개변수처럼 받으면 **하나의 코드**로 모든 타입을 처리한다.

::left::

### 함수 템플릿 선언

```cpp {}
template<typename T>      // T: 타입 매개변수
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}
```

<br>

| 키워드 | 역할 |
|--------|------|
| `template` | 템플릿 선언 시작 |
| `typename T` | 타입 매개변수 이름 선언 |
| `T` | 실제 타입의 자리표시자 |

::right::

### 사용 — 타입 자동 추론

```cpp {}
int x = 1, y = 2;
swap(x, y);           // T = int 로 추론
// x=2, y=1

double p = 3.14, q = 2.72;
swap(p, q);           // T = double 로 추론
// p=2.72, q=3.14

std::string s = "hello", t = "world";
swap(s, t);           // T = std::string 으로 추론
// s="world", t="hello"
```

> 컴파일러가 인수 타입을 보고 `T`를 **자동으로 결정**한다.

---
layout: two-cols-header
---

# `class T` vs `typename T`

두 키워드는 **문법적으로 동일**하지만, `typename`이 더 정확하고 현대적인 표현이다.

::left::

### 둘 다 컴파일된다

```cpp {}
// class 키워드 — 초기 C++의 방식
template<class T>
void swap(T& a, T& b) {
  T tmp = a; a = b; b = tmp;
}

// typename 키워드 — C++98 추가, 권장
template<typename T>
void swap(T& a, T& b) {
  T tmp = a; a = b; b = tmp;
}
```

- 두 선언은 **완전히 동등**하다
- 어떤 타입이든 전달 가능 (`int`, `double`, 클래스 모두)

::right::

### 왜 `typename`이 더 정확한가

`class`는 클래스 타입만 받을 것 같은 **오해**를 준다.

```cpp {}
template<class T>     // ← T가 클래스여야만 할 것 같다
T max_val(T a, T b) { return a > b ? a : b; }

max_val(3, 5);        // T = int    — 기본 타입도 OK
max_val(3.14, 2.72);  // T = double — 기본 타입도 OK
```

`typename`은 **"어떤 타입이든"** 이라는 의도를 명확히 전달한다.

| | `class T` | `typename T` |
|---|---|---|
| 등장 | 초기 C++ (표준 이전) | C++98 정식 추가 |
| 뉘앙스 | 클래스 타입만? | 어떤 타입이든 |
| 권장 여부 | ❌ 구식 | ✅ 현대 C++ 권장 |

> 표준 라이브러리 소스와 현대 C++ 코드는 `typename`을 사용한다.

---
layout: two-cols-header
---

# 인스턴스화 (Instantiation)

템플릿은 **설계도**다. 컴파일러가 구체적인 타입을 대입해 실제 함수를 **자동 생성**한다.

::left::

### 컴파일러가 생성하는 코드

```cpp {}
// 원본 템플릿 (설계도)
template<typename T>
void swap(T& a, T& b) {
  T tmp = a; a = b; b = tmp;
}

// swap(x, y)  호출 시 → 컴파일러 자동 생성
void swap(int& a, int& b) {
  int tmp = a; a = b; b = tmp;
}

// swap(p, q)  호출 시 → 컴파일러 자동 생성
void swap(double& a, double& b) {
  double tmp = a; a = b; b = tmp;
}
```

::right::

### 타입 추론 vs 명시적 지정

```cpp {}
template<typename T>
T max_val(T a, T b) {
  return a > b ? a : b;
}

// 타입 추론 — 인수로 T 자동 결정
max_val(3, 5);           // T = int
max_val(3.14, 2.72);     // T = double

// 명시적 지정 — <> 안에 T를 직접 기입
max_val<int>(3, 5);      // T = int
max_val<double>(3, 5);   // T = double
                         // (3, 5가 double로 변환됨)
```

---
layout: two-cols-header
---

# 여러 타입 매개변수

`template<typename T, typename U>`처럼 **타입 매개변수를 여러 개** 사용할 수 있다.

::left::

### 두 타입을 받는 함수 템플릿

```cpp {}
#include <iostream>

template<typename T, typename U>
void print_pair(T a, U b) {
  std::cout << a << ", " << b << "\n";
}

int main() {
  print_pair(42, "hello");    // T=int,    U=const char*
  print_pair(3.14, true);     // T=double, U=bool
  print_pair('A', 65);        // T=char,   U=int
}
```

```txt {}
42, hello
3.14, 1
A, 65
```

::right::

### 반환 타입이 두 타입 중 하나인 경우

```cpp {}
// C++11: decltype으로 반환 타입 추론
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
  return a + b;
}

// C++14 이후: auto만으로 가능
template<typename T, typename U>
auto add2(T a, U b) {
  return a + b;
}

std::cout << add(1, 2.5);   // 3.5 (double)
std::cout << add('A', 1);   // 66  (int)
```

---
layout: section
---

# 클래스 템플릿

---
layout: two-cols-header
---

# 클래스 템플릿 — 기본

`template<typename T>`를 클래스 앞에 붙이면 **타입을 매개변수로 받는 클래스**를 만든다.

::left::

### Pair 클래스 템플릿

```cpp {}
template<typename T, typename U>
class Pair {
public:
  T first;
  U second;

  Pair(T f, U s) : first(f), second(s) {}

  void print() const {
    std::cout << first << ", " << second << "\n";
  }
};

// 사용 — 타입 인수를 <> 안에 명시
Pair<int, std::string> p1(1, "hello");
p1.print();    // 1, hello

Pair<double, bool> p2(3.14, true);
p2.print();    // 3.14, 1
```

::right::

### 함수 템플릿과의 차이

| | 함수 템플릿 | 클래스 템플릿 |
|---|---|---|
| 타입 추론 | 인수에서 자동 추론 | 직접 명시 필요 |
| 인스턴스화 | `f(x)` 호출 시 | 변수 선언 시 |
| 예시 | `max_val(3, 5)` | `Pair<int, int>` |

<br>

> C++17부터 클래스 템플릿도 **생성자 인수로 타입 추론** 가능 (CTAD)
>
> ```cpp
> Pair p(1, "hello");  // C++17: Pair<int, const char*>
> ```

---
layout: two-cols-header
---

# Stack 클래스 템플릿

클래스 템플릿으로 **어떤 타입이든 담을 수 있는 스택**을 만들 수 있다.

::left::

### Stack<T> 구현

```cpp {}
#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
  std::vector<T> data;
public:
  void push(const T& v) { data.push_back(v); }

  void pop() {
    if (empty()) throw std::runtime_error("empty");
    data.pop_back();
  }

  T top() const {
    if (empty()) throw std::runtime_error("empty");
    return data.back();
  }

  bool empty() const { return data.empty(); }
  int  size()  const { return (int)data.size(); }
};
```

::right::

### 사용 — 타입만 바꿔 재사용

```cpp {}
// int 스택
Stack<int> si;
si.push(1); si.push(2); si.push(3);
std::cout << si.top();   // 3
si.pop();
std::cout << si.top();   // 2

// string 스택 — 같은 클래스, 다른 타입
Stack<std::string> ss;
ss.push("hello");
ss.push("world");
std::cout << ss.top();   // world
```

<br>

> `Stack<int>`과 `Stack<std::string>`은
> **별개의 클래스**로 인스턴스화된다.

---
layout: two-cols-header
---

# 비타입 템플릿 매개변수

타입 뿐만 아니라 **정수 값도** 템플릿 매개변수로 쓸 수 있다.

::left::

### 크기가 고정된 배열 클래스

```cpp {}
template<typename T, int N>
class Array {
  T data[N];            // N은 컴파일 타임 상수
public:
  T&       operator[](int i)       { return data[i]; }
  const T& operator[](int i) const { return data[i]; }
  int size() const { return N; }
};

int main() {
  Array<int, 5> arr;    // int[5] 고정 크기
  for (int i = 0; i < arr.size(); i++)
    arr[i] = i * 10;
  // 0 10 20 30 40

  Array<double, 3> da;
  da[0] = 1.1; da[1] = 2.2; da[2] = 3.3;
}
```

::right::

### std::array — 표준 라이브러리 구현

표준 라이브러리의 `std::array<T, N>`이 이 패턴으로 구현된다.

```cpp {}
#include <array>
#include <algorithm>

std::array<int, 5> a = {3, 1, 4, 1, 5};

std::sort(a.begin(), a.end());
// a = {1, 1, 3, 4, 5}

std::cout << a.size();  // 5
```

<br>

| | `T[]` (C 배열) | `std::array<T, N>` |
|---|---|---|
| 크기 | 고정 | 고정 |
| 범위 검사 | 없음 | `at()` 사용 |
| 반복자 | 없음 | `begin()/end()` |
| 함수 전달 | 포인터로 decay | 레퍼런스로 전달 |

---
layout: two-cols-header
---

# 표준 라이브러리와 템플릿

STL의 모든 컨테이너와 알고리즘은 **템플릿으로 구현**되어 있다.

::left::

### 컨테이너 — 클래스 템플릿

```cpp {}
#include <vector>
#include <map>
#include <set>

// 클래스 템플릿 인스턴스화
std::vector<int>            vi;   // vector<int>
std::vector<std::string>    vs;   // vector<string>
std::map<std::string, int>  mi;   // map<string,int>
std::set<double>            sd;   // set<double>

// std::pair — 두 타입을 묶는 클래스 템플릿
std::pair<std::string, int> p = {"score", 95};
std::cout << p.first;    // score
std::cout << p.second;   // 95
```

::right::

### 알고리즘 — 함수 템플릿

```cpp {}
#include <algorithm>
#include <numeric>
#include <vector>

std::vector<int> v = {3, 1, 4, 1, 5, 9};

// 함수 템플릿 — 타입 자동 추론
std::sort(v.begin(), v.end());
// v = {1, 1, 3, 4, 5, 9}

auto it = std::find(v.begin(), v.end(), 4);
// it → v[2] (값 4의 위치)

int s = std::accumulate(v.begin(), v.end(), 0);
// s = 23

// 같은 템플릿, 다른 타입으로도 동작
std::vector<std::string> words = {"banana", "apple"};
std::sort(words.begin(), words.end());
// words = {"apple", "banana"}
```

---
layout: default
---

# 정리

| 개념 | 문법 | 용도 |
|------|------|------|
| 함수 템플릿 | `template<typename T> void f(T a)` | 타입만 다른 함수를 하나로 |
| 클래스 템플릿 | `template<typename T> class C { }` | 타입만 다른 클래스를 하나로 |
| 타입 추론 | `f(x)` — 인수에서 자동 결정 | 함수 템플릿에서 편리하게 |
| 명시적 지정 | `f<int>(x)` | 추론이 안 되거나 명확히 할 때 |
| 비타입 매개변수 | `template<typename T, int N>` | 컴파일 타임 상수 값 전달 |
| 인스턴스화 | 컴파일러 자동 생성 | 각 타입 조합마다 별개 코드 |

<br>

### 핵심 원칙

- 템플릿은 **설계도** — 사용 시점에 컴파일러가 구체적인 코드를 생성한다
- 함수 템플릿은 **타입 추론** 가능, 클래스 템플릿은 **명시 필요** (C++17 이전)
- STL의 모든 컨테이너·알고리즘이 **템플릿으로 구현**됨 — 우리가 이미 사용해왔다
