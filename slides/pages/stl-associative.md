---
layout: cover
---

# C++ 프로그래밍
## 연관 컨테이너 (Associative Containers)

---
layout: cover
---

# `std::set`
## 중복을 허용하지 않는 원소(Key)들의 연관 컨테이너

---
layout: two-cols-header
---

# `std::set` — 중복 없는 집합

`set`은 **중복을 허용하지 않는** 집합이다. 원소의 삽입·검색·삭제를 빠르게 수행할 수 있다.

::left::

## 기본 사용

```cpp {}
#include <set>

std::set<int> s;

// 삽입 — 중복 무시
s.insert(30);
s.insert(10);
s.insert(20);
s.insert(10);   // 중복 — 무시됨

// 순회
for (int x : s) {
    std::cout << x << " ";  // 10 20 30
}

s.size();    // 3
s.empty();   // false
```

::right::

## 검색과 삭제

```cpp {}
std::set<int> s = {10, 20, 30, 40, 50};

// 검색 — O(log n)
auto it = s.find(30);
if (it != s.end()) {
    std::cout << *it;   // 30
}

// 존재 여부 확인
s.count(30);         // 1 (있음) 또는 0 (없음)
// s.contains(30);   // C++20 ✅

// 삭제
s.erase(20);         // s: {10, 30, 40, 50}

// 범위 삭제 — [30, 50)
s.erase(s.find(30), s.find(50));
// s: {10, 50}
```

> `find()`는 O(log n) — `std::find()`(선형 탐색)보다 훨씬 빠르다.

---
layout: two-cols-header
---

# `std::set` — 초기화와 활용 패턴

::left::

## 다양한 초기화

```cpp {}
// initializer list — 중복 자동 제거
std::set<int> s1 = {5, 3, 1, 4, 2, 3, 1};
// s1: {1, 2, 3, 4, 5}

// 문자열 set
std::set<std::string> words;
words.insert("banana");
words.insert("apple");
words.insert("cherry");
words.insert("apple");   // 중복 무시
// words: {"apple", "banana", "cherry"}

// vector → set: 중복 제거
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
std::set<int> s2(v.begin(), v.end());
// s2: {1, 2, 3, 4, 5, 6, 9}
```

::right::

## 활용 패턴

```cpp {}
// ① 방문 여부 추적
std::set<int> visited;
visited.insert(3);
visited.insert(5);
visited.insert(3);   // 이미 방문 — 무시

if (visited.count(5)) {
    std::cout << "5는 이미 방문\n";   // ✅
}

// ② 중복 제거 후 vector로 복원
std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5};
std::set<int> s(data.begin(), data.end());
std::vector<int> unique_data(s.begin(), s.end());
// unique_data: {1, 2, 3, 4, 5, 6, 9}

// ③ insert 반환값 — 삽입 성공 여부 확인
auto [it, ok] = s1.insert(99);
// ok == true  → 삽입됨
// ok == false → 이미 존재
```

> `set`은 **중복 없는 원소 집합**이 필요할 때 사용한다.
> 방문 추적, 중복 제거, 멤버십 확인에 자주 활용된다.

---
layout: cover
---

# `std::map`
## Key-Value 쌍의  연관 컨테이너

---
layout: two-cols-header
---

# `std::map` — 키로 값을 찾는 사전

`map`은 **키(key)로 값(value)을 찾는 사전**이다. 배열이 정수 인덱스로 값을 찾듯, `map`은 **임의 타입의 키**로 값을 찾는다.

::left::

## 배열 vs `map`

```txt {}
vector<int>             map<string, int>
─────────────────       ─────────────────────
인덱스(int) → 값         키(string)  → 값
─────────────────       ─────────────────────
  0  →  95              "Alice"  →  95
  1  →  88              "Bob"    →  88
  2  →  72              "Carol"  →  72
```

```cpp {}
// vector: 정수 인덱스만 가능
std::vector<int> v = {95, 88, 72};
v[0];   // 95

// map: 문자열·정수·객체 등 키로 사용 가능
std::map<std::string, int> score;
score["Alice"] = 95;
score["Alice"];   // 95 — 이름으로 직접 접근
```

::right::

## 활용 예시

```cpp {}
// 영한 사전: 단어 → 뜻
std::map<std::string, std::string> dict;
dict["apple"]  = "사과";
dict["banana"] = "바나나";
dict["apple"];   // "사과"

// 학번 → 점수
std::map<int, double> grade;
grade[20241001] = 4.5;
grade[20241002] = 3.8;

// 단어 빈도 카운팅
std::map<std::string, int> freq;
freq["hello"]++;
freq["world"]++;
freq["hello"]++;
// freq["hello"] == 2
```

> - 키는 어떤 타입이든 가능 (단, `<` 비교 가능해야 함)
> - 삽입·검색·삭제 모두 **O(log n)**

---
layout: two-cols-header
---

# `std::map` — 생성과 삽입

`map`은 **키-값 쌍**을 저장한다. 키는 중복될 수 없으며, 빠르게 삽입·검색·삭제할 수 있다.

::left::

### 생성

```cpp {}
#include <map>

// 빈 map
std::map<std::string, int> m1;

// initializer list
std::map<std::string, int> score = {
    {"Alice", 95},
    {"Bob",   88},
    {"Carol", 72}
};
```

### `insert` — 명시적 삽입

```cpp {}
std::map<std::string, int> m;

m.insert({"Dave", 85});

// insert는 이미 있는 키를 덮어쓰지 않는다
auto [it, ok] = m.insert({"Dave", 99});  // C++17
// ok == false — 삽입 실패 (Dave 이미 존재)
// it  → 기존 Dave 원소를 가리킴
```

::right::

### `emplace`/`try_emplace`/`insert_or_assign`

```cpp {}
std::map<std::string, int> m;

// emplace: 키-값을 전달해 제자리 생성
m.emplace("Alice", 95);

// try_emplace (C++17): 없을 때만 삽입
m.try_emplace("Alice", 0);   // 이미 있으면 무시
m.try_emplace("Bob",  88);   // 없으면 삽입

// insert_or_assign (C++17): 항상 갱신
m.insert_or_assign("Alice", 100);  // 있으면 덮어씀
```

<br>

| 메서드 | 이미 있는 키 | 없는 키 |
|--------|------------|---------|
| `insert` | 무시 | 삽입 |
| `try_emplace` | 무시 | 삽입 |
| `insert_or_assign` | **갱신** | 삽입 |
| `[]` | **갱신** | **0으로 삽입** |

---
layout: two-cols-header
---

# `std::map` — `[]` 연산자: 편리함과 함정

::left::

### `[]`로 삽입·갱신

```cpp {}
std::map<std::string, int> m;

// [] 로 삽입
m["Alice"] = 95;
m["Bob"]   = 88;

// [] 로 접근
std::cout << m["Alice"];   // 95

// [] 로 수정 (덮어씀)
m["Alice"] = 100;
```

<br>

### ⚠️ 없는 키에 접근하면 자동 삽입!

```cpp {}
std::map<std::string, int> m;
m["Alice"] = 95;

// 없는 키를 읽으면 0으로 초기화 후 삽입
std::cout << m["Nobody"];  // 0 출력
std::cout << m.size();     // 2 ← Nobody가 추가됨!

// const map에서는 [] 사용 불가
const auto& cm = m;
// cm["Alice"];   // ❌ 컴파일 오류
```

::right::

### ✅ 안전한 읽기: `at()` / `find()`

```cpp {}
std::map<std::string, int> m = {
    {"Alice", 95}, {"Bob", 88}
};

// at() — 없으면 std::out_of_range 예외
std::cout << m.at("Alice");   // 95
try {
    m.at("Nobody");   // ❌ 예외 발생
} catch (const std::out_of_range&) {
    std::cout << "키 없음\n";
}

// find() — 없으면 end() 반환 (가장 안전)
auto it = m.find("Bob");
if (it != m.end()) {
    std::cout << it->second;   // 88
}

// C++20: contains()
if (m.contains("Alice")) {
    std::cout << m.at("Alice");
}
```

> **원칙**: `[]`는 **쓰기 전용**, 읽기에는 `at()` 또는 `find()`를 사용한다.

---
layout: two-cols-header
---

# `std::map` — 검색·범위 조회

::left::

## `find` / `count` / `contains`

```cpp {}
std::map<std::string, int> score = {
    {"Alice", 95}, {"Bob", 88},
    {"Carol", 72}, {"Dave", 85}
};

// find: O(log n), 이터레이터 반환
auto it = score.find("Bob");
if (it != score.end()) {
    it->first;           // "Bob" — 키
    it->second;          // 88   — 값
    it->second = 90;     // 값 수정도 가능
}

// count: 키 존재 여부 (0 또는 1)
score.count("Alice");    // 1
score.count("Nobody");   // 0

// C++20: contains
score.contains("Carol"); // true
```

::right::

## `lower_bound` / `upper_bound` — 키 범위 조회

```cpp {}
std::map<int, std::string> m = {
    {10, "A"}, {20, "B"}, {30, "C"}, {40, "D"}
};

// lower_bound: 키 이상인 첫 번째 이터레이터
auto lb = m.lower_bound(20);
// lb → {20, "B"}

// upper_bound: 키 초과인 첫 번째 이터레이터
auto ub = m.upper_bound(30);
// ub → {40, "D"}

// 키 [20, 30] 범위 순회
for (auto it = m.lower_bound(20);
         it != m.upper_bound(30); ++it) {
    std::cout << it->first << " ";  // 20 30
}
```

> `lower_bound` / `upper_bound` 모두 **O(log n)**.
> 특정 키 범위를 빠르게 조회하는 것은 `map`의 고유 강점이다.

---
layout: two-cols-header
---

# `std::map` — 이터레이터와 순회

::left::

## `it->first` / `it->second`

```cpp {}
std::map<std::string, int> score = {
    {"Alice", 95}, {"Bob", 88}, {"Carol", 72}
};

// 이터레이터 순회
for (auto it = score.begin(); it != score.end(); ++it) {
    std::cout << it->first           // 키
              << ": " << it->second  // 값
              << "\n";
}
// Alice: 95
// Bob: 88
// Carol: 72

// 역방향 순회
for (auto it = score.rbegin(); it != score.rend(); ++it) {
    std::cout << it->first << "\n";
    // Carol → Bob → Alice
}
```

::right::

## 범위 기반 for / 구조화 바인딩

```cpp {}
// C++11: pair로 순회
for (const auto& p : score) {
    std::cout << p.first << ": " << p.second << "\n";
}

// C++17: structured bindings ← 권장
for (const auto& [name, s] : score) {
    std::cout << name << ": " << s << "\n";
}
// Alice: 95
// Bob: 88
// Carol: 72

// 값 수정: 참조로 받기
for (auto& [name, s] : score) {
    s += 5;   // 모든 점수 +5
}
```

> map은 항상 **일관된 키 순서**로 순회된다.
> C++17 구조화 바인딩으로 `it->first` / `it->second` 없이 읽기 쉽게 쓸 수 있다.

---
layout: two-cols-header
---

# `std::map` — 삭제와 활용 패턴

::left::

## 삭제

```cpp {}
std::map<std::string, int> m = {
    {"Alice", 95}, {"Bob", 88}, {"Carol", 72}
};

// 키로 삭제 — O(log n)
m.erase("Bob");
// m: {Alice:95, Carol:72}

// 이터레이터로 삭제
auto it = m.find("Carol");
if (it != m.end()) m.erase(it);
// m: {Alice:95}

// 범위 삭제 [first, last)
m.erase(m.begin(), m.end());   // == m.clear()

m.size();    // 0
m.empty();   // true
```

::right::

## 활용 패턴: 빈도 카운팅

`[]`의 "없으면 0 삽입" 특성을 활용한 전형적인 패턴이다.

```cpp {}
std::vector<std::string> words = {
    "apple", "banana", "apple",
    "cherry", "banana", "apple"
};

std::map<std::string, int> freq;

for (const auto& w : words) {
    freq[w]++;   // 없으면 0으로 삽입 후 +1
}
// freq: {apple:3, banana:2, cherry:1}

for (const auto& [word, cnt] : freq) {
    std::cout << word << ": " << cnt << "\n";
}

// 가장 많이 등장한 단어
auto max_it = std::max_element(freq.begin(), freq.end(),
    [](const auto& a, const auto& b){
        return a.second < b.second;
    });
std::cout << max_it->first;   // "apple"
```

---
layout: two-cols-header
---

# `std::pair` — 두 값을 묶는 타입

`map`의 각 원소는 `std::pair<const Key, Value>`로 저장됨. `pair`를 이해하면 `map` 이터레이터를 자연스럽게 읽을 수 있음.

::left::

### 기본 사용

```cpp {}
#include <utility>   // std::pair

// 선언과 초기화
std::pair<std::string, int> p1 {"Alice", 95};

// make_pair — 타입 자동 추론
auto p2 = std::make_pair("Bob", 88);

// 중괄호 초기화 (C++11)
std::pair<std::string, int> p3 = {"Carol", 72};

// 멤버 접근
p1.first;    // "Alice" — 첫 번째 값
p1.second;   // 95      — 두 번째 값

// 비교 — first 기준, 같으면 second 기준
p1 < p3;     // "Alice" < "Carol" → true
```

::right::

### `map`의 원소 타입

```cpp {}
// map<K, V>의 value_type = pair<const K, V>

std::map<std::string, int> score = {
    {"Alice", 95}, {"Bob", 88}   // 각 원소가 pair
};

// 이터레이터 → pair를 가리킴
auto it = score.begin();
it->first;    // "Alice" — 키 (const, 수정 불가)
it->second;   // 95      — 값

// insert에 pair 전달
score.insert(std::make_pair("Dave", 85));
score.insert({"Eve", 79});   // 중괄호 초기화도 가능

// range-based for: pair로 받기
for (const auto& p : score) {
    std::cout << p.first << ": " << p.second << "\n";
}
// → C++17 구조화 바인딩으로 더 간결하게 사용 가능
```

> `map` 이터레이터의 `->first` / `->second`는
> `pair<const Key, Value>`의 두 멤버다.

---
layout: default
---

# 연관 컨테이너 비교

| 컨테이너 | 중복 키 | `[]` | 헤더 | 주 용도 |
|----------|---------|------|------|---------|
| `set<T>` | ❌ | ❌ | `<set>` | 중복 없는 집합, 존재 여부 확인 |
| `map<K,V>` | ❌ | ✅ | `<map>` | 키-값 저장, 빠른 검색 |

<br>

```
연관 컨테이너가 필요한 경우
│
├─ 중복 없는 집합이 필요한가?
│      → set<T>   (예: 방문한 노드 추적, 단어 사전)
│
└─ 키-값 쌍을 저장해야 하는가?
       → map<K,V>  (예: 이름→점수, 단어 빈도 카운팅)
```

<br>

> 모든 연관 컨테이너는 삽입·검색·삭제가 **O(log n)**이다.
> 순서가 필요 없고 O(1) 검색이 중요하다면 `unordered_map` / `unordered_set`을 고려한다.
