---
layout: cover
---

# C++ 프로그래밍
## STL (Standard Template Library)

---
layout: default
---

# STL이란?

**STL** (Standard Template Library)은 C++98부터 표준에 포함된 **자료구조와 알고리즘 라이브러리**다.

```cpp {}
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    std::vector<int> scores = {85, 92, 78, 95, 88};

    // 정렬 — 직접 구현 불필요
    std::sort(scores.begin(), scores.end());
    // scores: {78, 85, 88, 92, 95}

    // 키-값 저장
    std::map<std::string, int> student;
    student["Alice"] = 95;
    student["Bob"]   = 88;
    std::cout << student["Alice"];  // 95
}
```

<br>

| 특성 | 내용 |
|------|------|
| **범용성** | 템플릿 기반 — 어떤 타입이든 동일한 인터페이스 |
| **표준 탑재** | 모든 C++ 컴파일러에 기본 포함 |
| **검증된 구현** | 최적화·안전성이 보장된 코드 |
| **재사용성** | 자료구조·알고리즘을 직접 구현할 필요 없음 |

---
layout: two-cols-header
---

# STL의 4대 구성 요소

**컨테이너 → 이터레이터 → 알고리즘** 순서로 연계해 동작한다.

::left::

## 컨테이너 (Containers)
데이터를 **저장**하는 자료구조

```cpp {}
std::vector<int> v = {1, 2, 3};   // 동적 배열
std::set<int>    s = {3, 1, 2};   // 정렬된 집합
std::map<std::string, int> m;     // 키-값 저장소
m["one"] = 1;
```

<br>

## 이터레이터 (Iterators)
컨테이너를 **순회**하는 범용 포인터

```cpp {}
std::vector<int> v = {10, 20, 30};

auto it = v.begin();   // 첫 원소를 가리킴
*it;                   // 10 — 역참조
++it;                  // 다음 원소로 이동
*it;                   // 20
```

::right::

## 알고리즘 (Algorithms)
이터레이터 범위에 **연산**을 적용

```cpp {}
#include <algorithm>
#include <numeric>

std::vector<int> v = {3, 1, 4, 1, 5};

std::sort(v.begin(), v.end());       // 정렬
// v: {1, 1, 3, 4, 5}

auto it = std::find(v.begin(), v.end(), 3);
// *it == 3

int sum = std::accumulate(v.begin(), v.end(), 0);
// sum == 14
```

<br>

## 함수 객체 / 람다 (Functors / Lambdas)
알고리즘에 **동작을 주입**하는 방식

```cpp {}
// 내림차순 정렬 — 표준 함수 객체
std::sort(v.begin(), v.end(), std::greater<int>());

// 람다로 커스텀 조건 전달
auto it2 = std::find_if(v.begin(), v.end(),
    [](int x){ return x > 3; });
```

---
layout: default
---

# STL 헤더 파일

```cpp {}
// ── 시퀀스 컨테이너 ─────────────────────────────────────────
#include <vector>         // vector<T>        동적 배열  ← 기본 선택
#include <array>          // array<T, N>      고정 크기 배열 (C++11)
#include <list>           // list<T>          이중 연결 리스트
#include <deque>          // deque<T>         양방향 큐

// ── 연관 컨테이너 (트리 기반, 키 순 정렬) ──────────────────
#include <set>            // set<T>, multiset<T>
#include <map>            // map<K,V>, multimap<K,V>

// ── 비정렬 컨테이너 (해시 기반, C++11) ─────────────────────
#include <unordered_set>  // unordered_set<T>
#include <unordered_map>  // unordered_map<K,V>

// ── 알고리즘과 집계 ─────────────────────────────────────────
#include <algorithm>      // sort, find, transform, count, ...
#include <numeric>        // accumulate, iota, inner_product, ...
#include <functional>     // greater<T>, less<T>, std::function
```

<br>

> **기본 원칙**: 특별한 이유가 없으면 `std::vector`를 먼저 선택한다.
> 키 기반 검색이 필요하면 `std::map`, 중복 없는 집합이면 `std::set`을 고른다.


