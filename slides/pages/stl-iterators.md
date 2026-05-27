---
layout: cover
---

# C++ 프로그래밍
## 이터레이터 (Iterators)

---
layout: two-cols-header
---

# 이터레이터란?

이터레이터는 **컨테이너의 원소를 가리키는 객체**다. 포인터와 유사한 인터페이스를 제공하며, 컨테이너 종류와 무관하게 **동일한 방식으로 순회**할 수 있다.

::left::

## 포인터처럼 사용

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

// 이터레이터 선언
std::vector<int>::iterator it = v.begin();

*it;    // 10 — 역참조
++it;   // 다음으로 이동
*it;    // 20

it += 2;    // 2칸 앞으로 (random access)
*it;        // 40

// auto로 간결하게
auto it2 = v.begin();
std::cout << *it2;   // 10
```

::right::

## begin / end

```cpp {}
std::vector<int> v = {10, 20, 30};

// begin(): 첫 번째 원소를 가리킴
// end():   마지막 다음을 가리킴 (유효한 원소 아님)

auto first = v.begin();   // → 10
auto last  = v.end();     // → (30 다음, 접근 불가)

// 반복 패턴
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";   // 10 20 30
}
```

```
 begin()          end()
   ↓                ↓
[ 10 | 20 | 30 | × ]
```

> `end()`는 마지막 원소의 **다음 위치**를 가리키며,
> 역참조(`*end()`)는 **미정의 동작**이다.

---
layout: two-cols-header
---

# `end()` — 이터레이터의 `nullptr`

포인터에서 "유효하지 않음"을 `nullptr`로 표현하듯, 이터레이터에서 **"원소가 없음 / 범위의 끝"**을 `end()`로 표현한다.

::left::

## 포인터의 `nullptr` vs 이터레이터의 `end()`

```cpp {}
// ── 포인터 패턴 ──────────────────────────────────
int* find_ptr(int* arr, int n, int val) {
    for (int i = 0; i < n; i++)
        if (arr[i] == val) return &arr[i];
    return nullptr;           // 못 찾으면 nullptr 반환
}

int arr[] = {10, 20, 30};
int* p = find_ptr(arr, 3, 99);
if (p != nullptr) {           // 항상 확인 후 사용
    std::cout << *p;
}

// ── 이터레이터 패턴 ──────────────────────────────
std::vector<int> v = {10, 20, 30};
auto it = std::find(v.begin(), v.end(), 99);
if (it != v.end()) {          // end() == nullptr 역할
    std::cout << *it;
}
```

| | 포인터 | 이터레이터 |
|---|---|---|
| "없음" 표현 | `nullptr` | `end()` |
| 역참조 전 확인 | `!= nullptr` | `!= end()` |
| 역참조 시 미정의 동작 | ✅ | ✅ |

::right::

## `end()`를 반환하는 대표 상황

```cpp {}
std::vector<int> v = {10, 20, 30};
std::map<std::string, int> m = {{"Alice", 95}};
std::set<int> s = {10, 20, 30};

// ① std::find — 값이 없으면 end() 반환
auto it1 = std::find(v.begin(), v.end(), 99);
if (it1 == v.end()) std::cout << "없음\n";

// ② map::find — 키가 없으면 end() 반환
auto it2 = m.find("Bob");
if (it2 == m.end()) std::cout << "키 없음\n";
else std::cout << it2->second;

// ③ set::find — 값이 없으면 end() 반환
auto it3 = s.find(99);
if (it3 == s.end()) std::cout << "없음\n";

// ④ std::find_if — 조건 불만족 시 end() 반환
auto it4 = std::find_if(v.begin(), v.end(),
    [](int x){ return x > 100; });
if (it4 == v.end()) std::cout << "조건 불만족\n";
```

<br>

> ⚠️ `end()`를 역참조하면 **미정의 동작(크래시)**.
> 이터레이터는 반드시 **`!= end()` 확인 후** 역참조한다.

---
layout: default
---

# 이터레이터 카테고리

이터레이터는 **지원하는 연산**에 따라 5가지 카테고리로 나뉜다. 상위로 갈수록 더 많은 연산을 지원한다.

| 카테고리 | 지원 연산 | 대표 컨테이너 |
|----------|-----------|---------------|
| **Input** | `*`, `++`, `==`, `!=` (읽기 전용, 1회) | `istream_iterator` |
| **Forward** | Input + 다중 패스 | `forward_list` |
| **Bidirectional** | Forward + `--` (역방향) | `list`, `set`, `map` |
| **Random Access** | Bidirectional + `+n`, `-n`, `[]`, `<` | `vector`, `array`, `deque` |
| **Output** | `*`, `++` (쓰기 전용) | `ostream_iterator` |

<br>

```cpp {}
std::vector<int> v = {1, 2, 3, 4, 5};

auto it = v.begin();        // random access iterator
it += 3;     // ✅ vector: 3칸 이동 가능
it[1];       // ✅ 인덱스 접근 가능

std::list<int> lst = {1, 2, 3, 4, 5};
auto it2 = lst.begin();     // bidirectional iterator
++it2;   // ✅
--it2;   // ✅
// it2 += 3;   // ❌ list는 random access 불가
```

> `std::sort()` 같은 알고리즘은 **random access iterator**를 요구한다.
> `list`를 `std::sort()`에 넘기면 컴파일 오류가 난다 — `list::sort()` 멤버를 사용한다.

---
layout: two-cols-header
---

# `range-based for` 와 `auto`

C++11부터 **범위 기반 for 루프**로 이터레이터를 명시하지 않고도 순회할 수 있다.

::left::

## 범위 기반 for

```cpp {}
std::vector<int> v = {10, 20, 30};

// 값으로 복사 — 원본 변경 안 됨
for (int x : v) {
    std::cout << x << " ";  // 10 20 30
}

// 참조로 순회 — 원본 수정 가능
for (int& x : v) {
    x *= 2;
}
// v: {20, 40, 60}

// const 참조 — 읽기 전용, 복사 비용 없음 (권장)
for (const int& x : v) {
    std::cout << x << " ";  // 20 40 60
}

// auto로 간결하게
for (const auto& x : v) {
    std::cout << x << " ";
}
```

::right::

## 모든 컨테이너에 적용 가능

```cpp {}
// set
std::set<std::string> names = {"Charlie", "Alice", "Bob"};
for (const auto& name : names) {
    std::cout << name << "\n";
    // Alice   ← 정렬 순서
    // Bob
    // Charlie
}

// map
std::map<std::string, int> score = {
    {"Alice", 95}, {"Bob", 88}
};
for (const auto& [name, s] : score) {   // C++17
    std::cout << name << ": " << s << "\n";
}

// array
std::array<int, 3> arr = {1, 2, 3};
for (const auto& x : arr) {
    std::cout << x << " ";
}
```

> 범위 기반 for는 내부적으로 `begin()` / `end()`를 호출한다.

---
layout: two-cols-header
---

# `const_iterator` / `reverse_iterator`

::left::

## `const_iterator` — 읽기 전용

```cpp {}
std::vector<int> v = {10, 20, 30};

// const_iterator: 원소 수정 불가
std::vector<int>::const_iterator cit = v.cbegin();
std::cout << *cit;   // 10
// *cit = 99;   // ❌ 컴파일 오류 — 읽기 전용

// auto 사용 (cbegin/cend 권장)
for (auto it = v.cbegin(); it != v.cend(); ++it) {
    std::cout << *it << " ";   // 10 20 30
}

// const 컨테이너 — 자동으로 const_iterator
const std::vector<int> cv = {1, 2, 3};
for (auto it = cv.begin(); it != cv.end(); ++it) {
    // it는 자동으로 const_iterator
}
```

::right::

## `reverse_iterator` — 역방향 순회

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

// rbegin(): 마지막 원소를 가리킴
// rend():   첫 번째 이전을 가리킴
for (auto it = v.rbegin(); it != v.rend(); ++it) {
    std::cout << *it << " ";
    // 50 40 30 20 10
}

// set도 역방향 순회 가능
std::set<int> s = {10, 20, 30};
for (auto it = s.rbegin(); it != s.rend(); ++it) {
    std::cout << *it << " ";  // 30 20 10
}
```

<br>

| 함수 | 반환 타입 | 방향 | 수정 |
|------|-----------|------|------|
| `begin()` / `end()` | `iterator` | 정방향 | ✅ |
| `cbegin()` / `cend()` | `const_iterator` | 정방향 | ❌ |
| `rbegin()` / `rend()` | `reverse_iterator` | 역방향 | ✅ |
| `crbegin()` / `crend()` | `const_reverse_iterator` | 역방향 | ❌ |
