---
layout: cover
---

# `std::vector`
## 동적 연속 메모리 공간의 시퀀스 컨테이너

---
layout: two-cols-header
---

# `std::vector` — 생성과 기본 조작

`vector`는 크기가 자동으로 늘어나는 **동적 배열**이다. STL에서 가장 자주 쓰는 컨테이너다.

::left::

## 생성

```cpp {}
#include <vector>

// 빈 벡터
std::vector<int> v1;

// 초기값 리스트
std::vector<int> v2 = {10, 20, 30};

// N개를 같은 값으로 채우기
std::vector<int> v3(5, 0);    // {0, 0, 0, 0, 0}

// 복사 생성
std::vector<int> v4 = v2;     // {10, 20, 30}
```

::right::

## 뒤에 추가·제거, 기본 조회

```cpp {}
std::vector<int> v;

v.push_back(10);   // v: {10}
v.push_back(20);   // v: {10, 20}
v.push_back(30);   // v: {10, 20, 30}

v.size();          // 3 — 원소 수
v.empty();         // false

v.front();         // 10 — 첫 번째 원소
v.back();          // 30 — 마지막 원소

v.pop_back();      // v: {10, 20}
```


---
layout: two-cols-header
---

# `std::vector` + 알고리즘: 검색

`<algorithm>`의 함수들은 **이터레이터 범위** `(begin, end)`를 받아 동작한다. 컨테이너 종류와 무관하게 같은 인터페이스를 쓴다.

::left::

## `std::find` — 값으로 검색

```cpp {}
#include <algorithm>

std::vector<int> v = {10, 30, 20, 50, 40};

// 30을 검색 — 첫 번째 이터레이터 반환
auto it = std::find(v.begin(), v.end(), 30);

if (it != v.end()) {
    std::cout << *it;                // 30
    std::cout << (it - v.begin());   // 1 (인덱스)
} else {
    std::cout << "없음";
}

// 없는 값 검색 → end() 반환
auto it2 = std::find(v.begin(), v.end(), 99);
if (it2 == v.end()) {
    std::cout << "99는 없음";        // ← 실행됨
}
```

::right::

## `std::find_if` — 조건으로 검색

```cpp {}
std::vector<int> v = {10, 30, 20, 50, 40};

// 30보다 큰 첫 번째 원소
auto it = std::find_if(v.begin(), v.end(),
    [](int x){ return x > 30; });
// *it == 50

// 짝수인 첫 번째 원소
auto it2 = std::find_if(v.begin(), v.end(),
    [](int x){ return x % 2 == 0; });
// *it2 == 10

// 조건을 만족하는 원소가 하나라도 있는가?
bool any = std::any_of(v.begin(), v.end(),
    [](int x){ return x > 45; });
// true (50이 있음)
```

> **핵심 패턴**: `algorithm(v.begin(), v.end(), 조건)`
> 조건이 필요하면 **람다**를 전달한다.

---
layout: two-cols-header
---

# `std::vector` + 알고리즘: 정렬·집계

::left::

## `std::sort` — 정렬

```cpp {}
std::vector<int> v = {30, 10, 50, 20, 40};

// 오름차순 정렬 (기본)
std::sort(v.begin(), v.end());
// v: {10, 20, 30, 40, 50}

// 내림차순 — 비교 람다 전달
std::sort(v.begin(), v.end(),
    [](int a, int b){ return a > b; });
// v: {50, 40, 30, 20, 10}

// 부분 정렬 — 앞 3개만
std::sort(v.begin(), v.begin() + 3);
```

<br>

## `std::count_if` — 조건에 맞는 개수

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

int cnt = std::count_if(v.begin(), v.end(),
    [](int x){ return x >= 30; });
// cnt == 3  (30, 40, 50)
```

::right::

## `std::accumulate` — 집계

```cpp {}
#include <numeric>

std::vector<int> v = {10, 20, 30, 40, 50};

// 합계 (초기값 0)
int sum = std::accumulate(v.begin(), v.end(), 0);
// sum == 150

// 곱 (초기값 1, 커스텀 연산)
int product = std::accumulate(v.begin(), v.end(), 1,
    [](int acc, int x){ return acc * x; });
// product == 12'000'000
```

<br>

## `std::max_element` / `std::min_element`

```cpp {}
auto max_it = std::max_element(v.begin(), v.end());
auto min_it = std::min_element(v.begin(), v.end());

std::cout << *max_it;   // 50
std::cout << *min_it;   // 10
// (max_it - v.begin()) → 인덱스도 구할 수 있음
```

---
layout: two-cols-header
---

# `std::vector` — 원소 접근과 수정

::left::

## 원소 접근

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

// [] — 경계 검사 없음 (빠름)
v[0];      // 10
v[4];      // 50
// v[10];  // ❌ 미정의 동작

// at() — 경계 검사 있음
v.at(2);   // 30
try {
    v.at(10);  // std::out_of_range 예외
} catch (const std::out_of_range& e) {
    std::cout << e.what();
}

v.front();   // 10
v.back();    // 50
```

::right::

## 값 변경

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

// 인덱스로 직접 변경
v[1] = 99;
// v: {10, 99, 30, 40, 50}

// at()으로 변경 (경계 검사 포함)
v.at(3) = 77;
// v: {10, 99, 30, 77, 50}

// 범위 기반 for로 일괄 수정
for (auto& x : v) x *= 2;
// v: {20, 198, 60, 154, 100}

// assign: 전체를 새 값으로 교체
v.assign(3, 0);   // v: {0, 0, 0}
```

---
layout: two-cols-header
---

# `std::vector` — 삽입과 삭제

::left::

## 뒤에 추가·제거 — O(1) amortized

```cpp {}
std::vector<int> v = {10, 20, 30};

// push_back: 값을 복사·이동해 뒤에 추가
v.push_back(40);        // {10, 20, 30, 40}

// emplace_back: 인자를 받아 제자리 생성 (더 효율적)
v.emplace_back(50);     // {10, 20, 30, 40, 50}

// pop_back: 마지막 원소 제거
v.pop_back();           // {10, 20, 30, 40}
```

## 중간·앞에 삽입 — O(n)

```cpp {}
std::vector<int> v = {10, 30, 40};

// insert(위치, 값) — 위치 앞에 삽입
v.insert(v.begin() + 1, 20);
// v: {10, 20, 30, 40}

// 여러 개 한 번에 삽입
v.insert(v.end(), {50, 60});
// v: {10, 20, 30, 40, 50, 60}
```

::right::

## 삭제 — O(n) (뒤 제거는 O(1))

```cpp {}
std::vector<int> v = {10, 20, 30, 40, 50};

// 이터레이터 위치 삭제 — 다음 이터레이터 반환
auto it = v.begin() + 2;
it = v.erase(it);      // 30 삭제
// v: {10, 20, 40, 50},  *it == 40

// 범위 삭제 [first, last)
v.erase(v.begin() + 1, v.begin() + 3);
// v: {10, 50}

// 전체 삭제 (capacity는 유지됨)
v.clear();
```

## 왜 중간 삽입·삭제가 O(n)인가?

```
insert(begin+1, 20):
  [ 10 | 30 | 40 ]  →  [ 10 | 20 | 30 | 40 ]
           30, 40이 한 칸씩 오른쪽으로 이동

erase(begin+2):
  [ 10 | 20 | 30 | 40 | 50 ]  →  [ 10 | 20 | 40 | 50 ]
                40, 50이 한 칸씩 왼쪽으로 이동
```

> 삽입·삭제 위치 뒤의 원소가 **모두 이동** → O(n).
> 중간 삽입·삭제가 잦다면 `std::list`를 고려한다.

---
layout: two-cols-header
---

# `std::vector` — size와 capacity

`vector`는 내부에 **동적 배열**을 갖는다. 공간이 부족하면 더 큰 배열로 **재할당**한다.

::left::

## size vs capacity

```cpp {}
std::vector<int> v;

v.size();      // 0 — 현재 원소 수
v.capacity();  // 0 — 할당된 공간

v.push_back(1);
v.push_back(2);
v.push_back(3);
v.size();      // 3
v.capacity();  // 4 (구현마다 다름, 보통 2배씩 확장)

v.push_back(4);
v.push_back(5);   // 용량 초과 → 재할당
v.capacity();     // 8
```

```
push_back 시 capacity 초과 → 재할당
  ① 더 큰 배열 할당
  ② 기존 원소 전부 복사
  ③ 기존 배열 해제
```

::right::

## `reserve`로 재할당 방지

```cpp {}
// ❌ push_back마다 재할당 가능
std::vector<int> v1;
for (int i = 0; i < 1000; i++)
    v1.push_back(i);   // 재할당: 1→2→4→8→...

// ✅ 미리 공간 확보 → 재할당 0회
std::vector<int> v2;
v2.reserve(1000);
for (int i = 0; i < 1000; i++)
    v2.push_back(i);
```

<br>

## `resize` — 크기 직접 조정

```cpp {}
std::vector<int> v = {1, 2, 3, 4, 5};

v.resize(3);        // v: {1, 2, 3}  (뒤가 잘림)
v.resize(6, 0);     // v: {1, 2, 3, 0, 0, 0}
v.clear();          // v: {}  (size=0, capacity 유지)
```

> 원소 수를 미리 알면 `reserve()`로 재할당을 방지해 성능을 높인다.

---
layout: cover
---

# `std::list`
## '이중 연결 리스트' 구조의 시퀀스 컨테이너

---
layout: two-cols-header
---

# `std::list` — 구조와 생성

`list`는 각 원소가 **앞뒤 원소를 가리키는 포인터**를 갖는 이중 연결 리스트다. 메모리가 불연속이다.

::left::

## 메모리 구조

```
vector  [ 10 | 20 | 30 | 40 ]   연속 메모리
           ↑                     한 블록

list    [·|10|·] ↔ [·|20|·] ↔ [·|30|·] ↔ [·|40|·]
        prev next   prev next   prev next   prev next
                              각 노드 개별 힙 할당
```

## 생성

```cpp {}
#include <list>

std::list<int> lst1;                   // 빈 리스트
std::list<int> lst2 = {10, 20, 30};   // 초기화
std::list<int> lst3(4, 0);            // {0, 0, 0, 0}
```

::right::

## 앞·뒤 추가·제거와 기본 조회

```cpp {}
std::list<int> lst = {20, 30};

lst.push_front(10);   // {10, 20, 30}
lst.push_back(40);    // {10, 20, 30, 40}

lst.pop_front();      // {20, 30, 40}
lst.pop_back();       // {20, 30}

lst.front();          // 20
lst.back();           // 30
lst.size();           // 2
lst.empty();          // false
```

> `push_front` / `pop_front`는 `vector`에 없는 기능이다.
> 앞·뒤 모두 **O(1)**이다.


---
layout: two-cols-header
---

# `std::list` — 삽입·삭제: O(1)

`list`의 핵심 장점 — 이터레이터가 가리키는 위치에 삽입·삭제가 **O(1)**이다. 포인터만 변경하고 원소 이동은 없다.

::left::

## `insert` — O(1) 중간 삽입

```cpp {}
std::list<int> lst = {10, 30, 40};

auto it = std::find(lst.begin(), lst.end(), 30);

// it 앞에 20 삽입 — O(1)
lst.insert(it, 20);
// lst: {10, 20, 30, 40}

// 삽입 전:  ··· ↔ [10] ↔ [30] ↔ ···
// 삽입 후:  ··· ↔ [10] ↔ [20] ↔ [30] ↔ ···
//           (포인터 4개만 수정, 원소 이동 없음)
```

vector와 비교:

```cpp {}
std::vector<int> v = {10, 30, 40};
auto it2 = std::find(v.begin(), v.end(), 30);

// 삽입 — O(n): 30, 40이 오른쪽으로 이동
v.insert(it2, 20);
// [10] [20←30] [30←40] [40←?]  원소 전체 시프트
```

::right::

## `erase` · `remove` · `remove_if`

```cpp {}
std::list<int> lst = {10, 20, 30, 20, 40};

// 이터레이터 위치 삭제 — O(1)
auto it = std::find(lst.begin(), lst.end(), 30);
auto next = lst.erase(it);   // 30 삭제
// lst: {10, 20, 20, 40},  *next == 20

// 값으로 전체 삭제
lst.remove(20);
// lst: {10, 40}

// 조건으로 전체 삭제
lst.remove_if([](int x){ return x > 15; });
// lst: {10}
```

<br>

| 연산 | `vector` | `list` |
|------|----------|--------|
| 중간 삽입 | O(n) 이동 | **O(1)** 포인터 |
| 중간 삭제 | O(n) 이동 | **O(1)** 포인터 |
| 삽입 후 기존 이터레이터 | ❌ 무효화 | ✅ 유지 |

---
layout: two-cols-header
---

# `std::list` — 멤버 알고리즘

`list`는 구조 특성을 활용한 **전용 멤버 함수**를 제공한다. 포인터만 바꾸기 때문에 원소 복사 없이 동작한다.

::left::

## `sort` / `reverse` / `unique`

```cpp {}
std::list<int> lst = {30, 10, 40, 20, 10, 30};

// 오름차순 정렬 (std::sort 대신)
lst.sort();
// lst: {10, 10, 20, 30, 30, 40}

// 내림차순
lst.sort([](int a, int b){ return a > b; });
// lst: {40, 30, 30, 20, 10, 10}

// 역순으로 뒤집기
lst.reverse();
// lst: {10, 10, 20, 30, 30, 40}

// 정렬 후 연속 중복 제거
lst.sort();
lst.unique();
// lst: {10, 20, 30, 40}
```

::right::

## `splice` — O(1) 구간 이동

다른 리스트의 원소를 **포인터 연결만 바꿔** 이동한다. 원소 복사가 없다.

```cpp {}
std::list<int> a = {1, 2, 3, 4, 5};
std::list<int> b = {10, 20, 30};

// b 전체를 a의 3 앞으로 이동 — O(1)
auto pos = std::find(a.begin(), a.end(), 3);
a.splice(pos, b);
// a: {1, 2, 10, 20, 30, 3, 4, 5}
// b: {}  (b는 비워짐)

// b의 원소 하나만 이동
std::list<int> c = {100, 200, 300};
auto from = std::find(c.begin(), c.end(), 200);
a.splice(a.begin(), c, from);
// a: {200, 1, 2, 10, 20, 30, 3, 4, 5}
```

> `splice`는 `vector`에 없는 `list` 고유 기능이다.
> 노드 포인터만 재연결 — **복사·이동 없이 O(1)**.

---
layout: section
---

# `std::array` / `std::deque`

---
layout: two-cols-header
---

# `std::array` — 고정 크기 배열

컴파일 타임에 크기가 고정된 배열. C 배열과 성능은 같고, STL 인터페이스를 추가로 제공한다.

::left::

## 기본 사용

```cpp {}
#include <array>

std::array<int, 5> a = {1, 2, 3, 4, 5};

a[0];        // 1
a.at(2);     // 3  (경계 검사)
a.front();   // 1
a.back();    // 5
a.size();    // 5 — 항상 고정

for (const auto& x : a) {
    std::cout << x << " ";   // 1 2 3 4 5
}

// STL 알고리즘 그대로 사용 가능
std::sort(a.begin(), a.end());
auto it = std::find(a.begin(), a.end(), 3);
```

::right::

## C 배열 vs `std::array`

```cpp {}
// C 배열 — 위험
int c[5] = {1, 2, 3, 4, 5};
// c[10];       // ❌ 미정의 동작
// c.size();    // ❌ 컴파일 오류

// std::array — 안전
std::array<int, 5> arr = {1, 2, 3, 4, 5};
arr.at(10);  // ❌ std::out_of_range (안전)
arr.size();  // 5 — 언제나 정확
```

<br>

| | C 배열 | `std::array` |
|---|---|---|
| 크기 정보 | ❌ | `size()` ✅ |
| 경계 검사 | ❌ | `at()` ✅ |
| STL 알고리즘 | ❌ | ✅ |
| 런타임 오버헤드 | 없음 | 없음 |

---
layout: two-cols-header
---

# `std::deque` — 양방향 큐

**앞·뒤 모두 O(1)으로 삽입·삭제**할 수 있는 컨테이너. `vector`처럼 임의 접근도 가능하다.

::left::

## 기본 사용

```cpp {}
#include <deque>

std::deque<int> dq = {10, 20, 30};

// 앞·뒤 모두 O(1)
dq.push_front(5);    // {5, 10, 20, 30}
dq.push_back(40);    // {5, 10, 20, 30, 40}

dq.pop_front();      // {10, 20, 30, 40}
dq.pop_back();       // {10, 20, 30}

dq[1];               // 20 — 임의 접근 ✅
dq.front();          // 10
dq.back();           // 30
```

::right::

## `vector` vs `deque`

```cpp {}
// vector — 앞 삽입 O(n): 전체 원소 이동
std::vector<int> v = {10, 20, 30};
v.insert(v.begin(), 5);   // ❌ 느림

// deque — 앞 삽입 O(1)
std::deque<int> dq = {10, 20, 30};
dq.push_front(5);         // ✅ 빠름
```

<br>

| | `vector` | `deque` |
|---|---|---|
| 앞 삽입 | O(n) | **O(1)** ✅ |
| 뒤 삽입 | O(1) | O(1) |
| 임의 접근 | O(1) | O(1) |
| 메모리 | 연속 | 청크 분산 |

> `deque`를 쓰는 경우: 큐(Queue) 구현, 앞뒤 양방향 삽입이 필요할 때.

---
layout: default
---

# 시퀀스 컨테이너 선택 가이드

```
순서 있는 데이터를 저장해야 한다
│
├─ 크기가 컴파일 타임에 고정인가?
│      → std::array<T, N>
│
├─ 끝에서만 추가·삭제하는가?                    ← 대부분의 경우
│      → std::vector<T>                         ← 기본 선택
│
├─ 앞·뒤 모두 O(1) 삽입·삭제가 필요한가?
│      → std::deque<T>
│
└─ 중간 삽입·삭제가 잦고, 이터레이터를 유지해야 하는가?
       → std::list<T>
         (임의 접근 없음, 캐시 효율 낮음 — 실제 성능은 측정 필요)
```

<br>

| 컨테이너 | 이터레이터 | 임의 접근 | 앞 삽입 | 중간 삽입 | 삽입 후 이터레이터 |
|----------|-----------|-----------|---------|-----------|-------------------|
| `vector` | Random Access | O(1) ✅ | O(n) | O(n) | ❌ 무효화 |
| `array` | Random Access | O(1) ✅ | — | — | — |
| `deque` | Random Access | O(1) ✅ | O(1) ✅ | O(n) | ❌ 무효화 |
| `list` | Bidirectional | ❌ | O(1) ✅ | O(1) ✅ | ✅ 유지 |

> **결론**: 이유 없이 `vector`를 써도 거의 틀리지 않는다.
> 삽입·삭제 중 이터레이터를 살려야 한다면 `list`를 고려한다.
