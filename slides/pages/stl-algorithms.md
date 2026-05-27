---
layout: cover
---

# C++ 프로그래밍
## STL 알고리즘 (Algorithms)

---
layout: default
---

# 알고리즘 — 컨테이너에 독립적인 연산

STL 알고리즘은 **이터레이터 범위**를 받아 동작한다. 컨테이너 종류와 무관하게 동일한 알고리즘을 적용할 수 있다.

```cpp {}
#include <algorithm>   // sort, find, transform, count, ...
#include <numeric>     // accumulate, iota, ...

std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
std::list<int>   l = {3, 1, 4, 1, 5, 9, 2, 6};

// 같은 알고리즘을 다른 컨테이너에 적용
std::sort(v.begin(), v.end());         // ✅ vector — random access
// std::sort(l.begin(), l.end());      // ❌ list — bidirectional only
l.sort();                              // ✅ list 전용 멤버 함수
```

<br>

| 분류 | 대표 함수 | 헤더 |
|------|-----------|------|
| **검색** | `find`, `find_if`, `count`, `count_if`, `any_of`, `all_of` | `<algorithm>` |
| **정렬** | `sort`, `stable_sort`, `partial_sort`, `nth_element` | `<algorithm>` |
| **변환** | `transform`, `copy`, `copy_if`, `fill`, `generate` | `<algorithm>` |
| **집계** | `accumulate`, `max_element`, `min_element` | `<numeric>` |
| **집합** | `set_union`, `set_intersection`, `set_difference` | `<algorithm>` |

---
layout: two-cols-header
---

# 커스텀 함수 객체 (Functor)

`operator()`를 정의한 클래스를 **함수 객체(functor)**라 한다. 인스턴스를 만들어 함수처럼 호출하거나, STL 알고리즘에 직접 전달할 수 있다.

::left::

## Functor 정의

```cpp {}
// 상태 없는 functor
struct IsEven {
    bool operator()(int x) const { return x % 2 == 0; }
};

// 생성자로 상태를 주입하는 functor
struct GreaterThan {
    int threshold;
    GreaterThan(int t) : threshold(t) {}
    bool operator()(int x) const { return x > threshold; }
};
```

::right::

## 인스턴스 생성과 활용

```cpp {}
std::vector<int> v = {1, 2, 3, 4, 5, 6};

// ① 인스턴스 생성 후 직접 호출
IsEven isEven;
isEven(4);   // true  — 일반 함수처럼 호출
isEven(3);   // false

// ② 인스턴스를 변수에 담아 알고리즘에 전달
auto cnt = std::count_if(v.begin(), v.end(), isEven);
// cnt == 3

// ③ 상태를 주입한 인스턴스 생성 후 전달
GreaterThan gt3(3);   // threshold = 3
gt3(5);   // true
gt3(2);   // false

auto it = std::find_if(v.begin(), v.end(), gt3);
// *it == 4

// ④ 임시 객체로 바로 전달 (①②③ 축약)
std::count_if(v.begin(), v.end(), IsEven{});
std::find_if(v.begin(), v.end(), GreaterThan{3});
```

---
layout: two-cols-header
---

# 표준 라이브러리 Functor (`<functional>`)

`<functional>` 헤더는 자주 쓰는 연산을 functor로 미리 정의해 제공한다. 직접 만들 필요 없이 알고리즘에 바로 전달할 수 있다.

::left::

## 알고리즘에 활용

```cpp {}
#include <functional>

std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// std::greater<T>: 내림차순 정렬
std::sort(v.begin(), v.end(), std::greater<int>());
// v: {9, 6, 5, 4, 3, 2, 1, 1}

// std::plus<T>: accumulate 덧셈
int sum = std::accumulate(v.begin(), v.end(), 0,
                          std::plus<int>());
// sum == 31

// std::negate<T>: 부호 반전
std::vector<int> neg(v.size());
std::transform(v.begin(), v.end(),
               neg.begin(), std::negate<int>());
// neg: {-9, -6, -5, -4, -3, -2, -1, -1}
```

::right::

## 표준 Functor 목록

**비교**

| Functor | 동작 |
|---------|------|
| `std::greater<T>` | `a > b` — 내림차순 |
| `std::less<T>` | `a < b` — 오름차순 (기본) |

**산술 / 논리**

| Functor | 동작 |
|---------|------|
| `std::plus<T>` | `a + b` |
| `std::minus<T>` | `a - b` |
| `std::multiplies<T>` | `a * b` |
| `std::negate<T>` | `-a` |
| `std::logical_not<T>` | `!a` |

<br>

> 람다 `[](int x){ return x % 2 == 0; }`는
> 컴파일러가 내부적으로 **functor 클래스를 자동 생성**한 것이다.
> 이름이 필요하거나 여러 곳에서 재사용할 때는 functor가 유리하다.

---
layout: two-cols-header
---

# 람다 — 문법과 알고리즘 활용

STL 알고리즘은 **동작을 인자로 받는다**. 람다는 그 동작을 코드 안에서 바로 정의하는 **이름 없는 함수**다.

::left::

## 기본 문법

```
[캡처](매개변수) -> 반환타입 { 본문 }
  ↑       ↑           ↑        ↑
외부변수  함수인자   생략가능  실행코드
```

```cpp {}
// 캡처 없음, 반환 타입 자동 추론
[](int x){ return x * 2; }

// 매개변수 두 개 — sort의 비교 함수
[](int a, int b){ return a > b; }

// 반환 타입 명시
[](int x) -> bool { return x > 0; }

// 매개변수 없음 — generate용
[]{ return 42; }
```

## 알고리즘별 람다 형태

```cpp {}
// 단항 조건 (T) → bool    find_if, count_if, copy_if
[](int x){ return x > 0; }

// 이항 비교 (T, T) → bool  sort, max_element
[](int a, int b){ return a > b; }

// 단항 변환 (T) → U        transform
[](int x){ return x * 2; }

// 이항 집계 (acc, T) → acc  accumulate
[](int acc, int x){ return acc + x; }
```

::right::

## 알고리즘에 바로 전달

```cpp {}
std::vector<int> v = {3, 1, 4, 1, 5, 9};

// 단항 조건 — find_if
auto it = std::find_if(v.begin(), v.end(),
    [](int x){ return x > 4; });
// *it == 5

// 이항 비교 — sort
std::sort(v.begin(), v.end(),
    [](int a, int b){ return a > b; });
// v: {9, 5, 4, 3, 1, 1}

// 단항 변환 — transform
std::vector<int> sq(v.size());
std::transform(v.begin(), v.end(), sq.begin(),
    [](int x){ return x * x; });
// sq: {81, 25, 16, 9, 1, 1}

// 이항 집계 — accumulate
int sum = std::accumulate(v.begin(), v.end(), 0,
    [](int acc, int x){ return acc + x; });
// sum == 23
```

---
layout: two-cols-header
---

# 람다 — 캡처 리스트

람다 **바깥**의 변수를 본문에서 쓰려면 `[]` 안에 캡처를 선언해야 한다.

::left::

## 값 캡처 `[변수]` — 복사본 사용

```cpp {}
int threshold = 30;
std::vector<int> v = {10, 20, 30, 40, 50};

// threshold를 값으로 캡처 — 복사본
auto it = std::find_if(v.begin(), v.end(),
    [threshold](int x){ return x > threshold; });
// *it == 40

threshold = 100;   // 나중에 바꿔도 람다에 영향 없음
// 람다는 캡처 시점(생성 시)의 30을 기억
```

## 참조 캡처 `[&변수]` — 원본에 직접 접근

```cpp {}
int cnt = 0;
std::vector<int> v = {10, 20, 30, 40, 50};

// cnt를 참조로 캡처 — 원본 수정 가능
std::for_each(v.begin(), v.end(),
    [&cnt](int x){ if (x > 25) cnt++; });
// cnt == 3  (30, 40, 50이 조건 충족)
```

::right::

## 캡처 방식 정리

```cpp {}
int a = 1, b = 2;

[]{ }              // 캡처 없음 — 외부 변수 사용 불가
[a]{ }             // a만 값으로 캡처
[&a]{ }            // a만 참조로 캡처
[a, &b]{ }         // a는 값, b는 참조
[=]{ }             // 모든 외부 변수를 값으로 캡처
[&]{ }             // 모든 외부 변수를 참조로 캡처
[=, &b]{ }         // 기본 값 캡처, b만 참조로
[&, a]{ }          // 기본 참조 캡처, a만 값으로
```

| 캡처 | 의미 | 외부 변수 수정 |
|------|------|--------------|
| `[]` | 없음 | 불가 |
| `[x]` | x 값 복사 | 불가 (복사본) |
| `[&x]` | x 참조 | ✅ 가능 |
| `[=]` | 전체 값 복사 | 불가 |
| `[&]` | 전체 참조 | ✅ 가능 |

<br>

> 값 캡처는 람다 **생성 시점**의 스냅샷.
> 참조 캡처는 람다 **실행 시점**의 원본 — 참조 대상의 수명이 람다보다 길어야 한다.

---
layout: two-cols-header
---

# 검색 알고리즘

::left::

## `find` / `find_if`

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

// find: 값으로 검색 — 처음 찾은 이터레이터 반환
auto it = std::find(v.begin(), v.end(), 30);
if (it != v.end()) {
    std::cout << *it;         // 30
    std::cout << (it - v.begin());  // 2 (인덱스)
}

// find_if: 조건으로 검색
auto it2 = std::find_if(v.begin(), v.end(),
    [](int x){ return x > 25; });
// *it2 == 30 (25보다 큰 첫 원소)

// find_if_not: 조건을 만족하지 않는 첫 원소
auto it3 = std::find_if_not(v.begin(), v.end(),
    [](int x){ return x < 40; });
// *it3 == 40
```

::right::

## `count` / `count_if` / `any_of` / `all_of`

```cpp {}
std::vector<int> v = {1, 3, 5, 2, 4, 3, 3};

// count: 특정 값의 개수
std::count(v.begin(), v.end(), 3);     // 3

// count_if: 조건을 만족하는 개수
std::count_if(v.begin(), v.end(),
    [](int x){ return x % 2 == 0; }); // 2 (짝수 개수)

// any_of: 하나라도 조건 만족하는가?
std::any_of(v.begin(), v.end(),
    [](int x){ return x > 4; });      // true (5 있음)

// all_of: 모두 조건 만족하는가?
std::all_of(v.begin(), v.end(),
    [](int x){ return x > 0; });      // true

// none_of: 아무도 조건 만족 안 하는가?
std::none_of(v.begin(), v.end(),
    [](int x){ return x > 10; });     // true
```

---
layout: two-cols-header
---

# 정렬 알고리즘

::left::

## `sort` / `stable_sort`

```cpp {}
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// 오름차순 정렬 (기본)
std::sort(v.begin(), v.end());
// v: {1, 1, 2, 3, 4, 5, 6, 9}

// 내림차순 정렬 — 비교 함수 전달
std::sort(v.begin(), v.end(), std::greater<int>());
// v: {9, 6, 5, 4, 3, 2, 1, 1}

// 람다로 커스텀 정렬
std::sort(v.begin(), v.end(),
    [](int a, int b){ return a > b; });

// stable_sort: 동일 원소의 상대 순서 유지
struct Student { std::string name; int score; };
std::vector<Student> students = { {"A",90}, {"B",90}, {"C",80} };
std::stable_sort(students.begin(), students.end(),
    [](const Student& a, const Student& b){
        return a.score > b.score;
    });
// score 같으면 기존 순서 유지: A, B, C
```

::right::

## `partial_sort` / `nth_element`

```cpp {}
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// partial_sort: 상위 N개만 정렬
std::partial_sort(v.begin(), v.begin() + 3, v.end());
// 처음 3개만 정렬: {1, 1, 2, ...나머지 순서 불보장}

// nth_element: N번째 원소를 제자리로
std::vector<int> v2 = {3, 1, 4, 1, 5, 9, 2, 6};
std::nth_element(v2.begin(), v2.begin() + 3, v2.end());
// v2[3]에는 정렬 시 4번째 원소가 위치
// 앞쪽은 v2[3]보다 작거나 같고, 뒤쪽은 크거나 같음
```

<br>

## `is_sorted` 확인

```cpp {}
std::vector<int> a = {1, 2, 3, 4, 5};
std::vector<int> b = {3, 1, 2};

std::is_sorted(a.begin(), a.end());   // true
std::is_sorted(b.begin(), b.end());   // false
```

---
layout: two-cols-header
---

# 변환 알고리즘

::left::

## `transform`

```cpp {}
#include <algorithm>

std::vector<int> v = {1, 2, 3, 4, 5};
std::vector<int> result(v.size());

// 각 원소에 함수 적용 → result에 저장
std::transform(v.begin(), v.end(),
               result.begin(),
               [](int x){ return x * x; });
// result: {1, 4, 9, 16, 25}

// 제자리 변환 (in-place)
std::transform(v.begin(), v.end(),
               v.begin(),
               [](int x){ return x * 2; });
// v: {2, 4, 6, 8, 10}

// 두 범위를 합쳐 변환
std::vector<int> a = {1, 2, 3};
std::vector<int> b = {4, 5, 6};
std::vector<int> c(3);
std::transform(a.begin(), a.end(),
               b.begin(), c.begin(),
               [](int x, int y){ return x + y; });
// c: {5, 7, 9}
```

::right::

## `copy` / `copy_if` / `fill` / `generate`

```cpp {}
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst(5);

// copy: 범위를 복사
std::copy(src.begin(), src.end(), dst.begin());
// dst: {1, 2, 3, 4, 5}

// copy_if: 조건을 만족하는 원소만 복사
std::vector<int> evens;
std::copy_if(src.begin(), src.end(),
             std::back_inserter(evens),
             [](int x){ return x % 2 == 0; });
// evens: {2, 4}

// fill: 모든 원소를 같은 값으로
std::fill(dst.begin(), dst.end(), 0);
// dst: {0, 0, 0, 0, 0}

// generate: 함수 호출 결과로 채우기
int n = 0;
std::generate(dst.begin(), dst.end(),
              [&n]{ return n++; });
// dst: {0, 1, 2, 3, 4}
```

---
layout: two-cols-header
---

# `remove` / `unique` — 제거와 중복 처리

::left::

## `remove` / `remove_if` — erase-remove 패턴

```cpp {}
// ⚠️ std::remove는 실제로 삭제하지 않는다!
// 제거 대상을 뒤로 밀고, 유효 범위의 끝을 반환한다.

std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};

auto new_end = std::remove(v.begin(), v.end(), 2);
// v: {1, 3, 4, 5, ?, ?, ?}  ← ? 는 쓰레기값
// new_end → 유효 원소 다음을 가리킴

// erase로 실제 삭제 — erase-remove 관용구
v.erase(new_end, v.end());
// v: {1, 3, 4, 5}

// 한 줄로 (관용구 형태)
v.erase(std::remove(v.begin(), v.end(), 2), v.end());

// remove_if: 조건으로 제거
v.erase(
    std::remove_if(v.begin(), v.end(),
        [](int x){ return x % 2 == 0; }),
    v.end());
// v: {1, 3, 5}  (짝수 모두 제거)
```

::right::

## `unique` — 연속 중복 제거

```cpp {}
// ⚠️ unique도 실제로 삭제하지 않는다.
// 연속된 중복을 뒤로 밀고 유효 범위의 끝을 반환한다.

// 연속된 중복만 제거 (정렬 없이)
std::vector<int> v1 = {1, 1, 2, 3, 3, 3, 4};
v1.erase(std::unique(v1.begin(), v1.end()), v1.end());
// v1: {1, 2, 3, 4}

// 모든 중복 제거: sort 후 unique
std::vector<int> v2 = {3, 1, 4, 1, 5, 9, 2, 6, 5};
std::sort(v2.begin(), v2.end());
// v2: {1, 1, 2, 3, 4, 5, 5, 6, 9}
v2.erase(std::unique(v2.begin(), v2.end()), v2.end());
// v2: {1, 2, 3, 4, 5, 6, 9}
```

<br>

> `remove` / `unique`는 **원소를 물리적으로 삭제하지 않는다**.
> 반드시 `erase`와 짝지어 사용해야 컨테이너 크기가 줄어든다.

---
layout: two-cols-header
---

# `for_each` / `reverse` / `binary_search`

::left::

## `for_each` — 각 원소에 동작 적용

```cpp {}
std::vector<int> v = {1, 2, 3, 4, 5};

// 읽기 — 각 원소 출력
std::for_each(v.begin(), v.end(),
    [](int x){ std::cout << x << " "; });
// 1 2 3 4 5

// 쓰기 — 참조로 캡처해 원본 수정
std::for_each(v.begin(), v.end(),
    [](int& x){ x *= 2; });
// v: {2, 4, 6, 8, 10}
```

## `reverse` — 순서 뒤집기

```cpp {}
std::vector<int> v = {1, 2, 3, 4, 5};
std::reverse(v.begin(), v.end());
// v: {5, 4, 3, 2, 1}

std::string s = "hello";
std::reverse(s.begin(), s.end());
// s: "olleh"
```

::right::

## `binary_search` / `lower_bound` — 정렬된 범위 검색

```cpp {}
std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// ⚠️ 반드시 정렬된 상태여야 한다

// binary_search: 존재 여부 확인 — bool 반환
std::binary_search(v.begin(), v.end(), 5);  // true
std::binary_search(v.begin(), v.end(), 99); // false

// lower_bound: key 이상인 첫 이터레이터
auto lb = std::lower_bound(v.begin(), v.end(), 5);
// *lb == 5

// upper_bound: key 초과인 첫 이터레이터
auto ub = std::upper_bound(v.begin(), v.end(), 5);
// *ub == 6

// 값이 없을 때 — end() 반환
auto it = std::lower_bound(v.begin(), v.end(), 99);
if (it == v.end()) std::cout << "없음\n";
```

> `binary_search` / `lower_bound` / `upper_bound`는
> **정렬된 범위**에서만 올바르게 동작한다. O(log n).

---
layout: two-cols-header
---

# 집계 알고리즘

::left::

## `accumulate`

```cpp {}
#include <numeric>

std::vector<int> v = {1, 2, 3, 4, 5};

// 합계 (초기값 0)
int sum = std::accumulate(v.begin(), v.end(), 0);
// sum == 15

// 곱 (초기값 1)
int product = std::accumulate(v.begin(), v.end(), 1,
    [](int acc, int x){ return acc * x; });
// product == 120

// 문자열 연결
std::vector<std::string> words = {"C++", " ", "STL"};
std::string sentence = std::accumulate(
    words.begin(), words.end(), std::string{});
// sentence == "C++ STL"
```

::right::

## `max_element` / `min_element` / `minmax_element`

```cpp {}
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// 최댓값 이터레이터
auto max_it = std::max_element(v.begin(), v.end());
std::cout << *max_it;   // 9
std::cout << (max_it - v.begin());  // 5 (인덱스)

// 최솟값 이터레이터
auto min_it = std::min_element(v.begin(), v.end());
std::cout << *min_it;   // 1

// 최솟값·최댓값 동시에
auto [lo, hi] = std::minmax_element(v.begin(), v.end());
std::cout << *lo << ", " << *hi;   // 1, 9
```

<br>

## `iota` — 순차 값 채우기

```cpp {}
#include <numeric>
std::vector<int> v(5);
std::iota(v.begin(), v.end(), 1);
// v: {1, 2, 3, 4, 5}
```

---
layout: two-cols-header
---

# 알고리즘 조합 예제

학생 성적 데이터를 STL 알고리즘으로 처리한다.

> 알고리즘은 **이터레이터로 컨테이너와 분리**되어 있어 재조합이 자유롭다.

::left::

```cpp {}
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>

struct Student { std::string name; int score; };
```


```cpp {}
int main() {
    std::vector<Student> students = {
        {"Alice", 85}, {"Bob", 92}, {"Carol", 78},
        {"Dave", 96},  {"Eve", 70}, {"Frank", 88}
    };

    // ① 점수 내림차순 정렬
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b){
            return a.score > b.score;
        });

    // ② 80점 이상인 학생 수
    int pass = std::count_if(students.begin(), students.end(),
        [](const Student& s){ return s.score >= 80; });
    std::cout << "합격: " << pass << "명\n";
    // 합격: 4명
```

::right::

```cpp {}
    // ③ 전체 평균 점수
    int total = std::accumulate(students.begin(), students.end(), 0,
        [](int acc, const Student& s){ return acc + s.score; });
    double avg = static_cast<double>(total) / students.size();
    std::cout << "평균: " << avg << "\n";
    // 평균: 84.83...

    // ④ 90점 이상 학생 추출
    std::vector<Student> top;
    std::copy_if(students.begin(), students.end(),
        std::back_inserter(top),
        [](const Student& s){ return s.score >= 90; });
    for (const auto& s : top)
        std::cout << s.name << "(" << s.score << ")\n";
    // Dave(96)  Bob(92)

    return 0;
}
```

