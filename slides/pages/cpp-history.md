---
layout: section
---
# C 언어의 탄생
## Bell Labs와 UNIX

---
layout: two-cols
---

# Bell Labs와 UNIX
- **1969년** — Ken Thompson, AT&T Bell Labs에서 UNIX 운영체제 개발 시작
- 당시 OS는 어셈블리어로 작성 → 이식성 없음, 유지보수 어려움

<img src="/images/Pdp7-oslo-2005.jpg" class="w-[350px] m-auto mt-4" />

::right::

<img src="/images/faces.KenThompson20449.web_.jpg" class="w-[350px] m-auto mt-4" />

---
layout: two-cols
---

# C 언어의 탄생

- **1972년** — Dennis Ritchie, B 언어를 발전시켜 **C 언어** 개발
- UNIX를 C로 재작성 → "시스템을 직접 제어할 수 있는 고수준 언어"의 시작

::right::

<img src="/images/Dennis_Ritchie_2011.jpg" class="w-[350px] m-auto mt-4" />

---
layout: default
---

# C 언어 설계 철학

>💡 C 언어: "하드웨어에 가깝지만, 사람이 읽을 수 있는 언어"를 목표로 설계

```
1969  UNIX 개발 시작 (Assembly)
 │
1972  Dennis Ritchie → C 언어 탄생
 │
1978  "The C Programming Language" 출판 (K&R C)
 │
1989  ANSI C (C89) 표준화
```

::right::

<img src="/images/The_C_Programming_Language_2nd_ed.jpg" class="w-[350px] m-auto mt-4" />


---
layout: section
---

# C에서 C++로 
## "C with Classes"

---
layout: two-cols
---

# Bjarne Stroustrup
- **1979년** — 덴마크 출신 컴퓨터 과학자, Bell Labs에서 연구
- 박사 논문 작업 중 **Simula**(최초의 OOP 언어)의 클래스 개념에 주목
- C의 성능 + Simula의 OOP → **"C with Classes"** 개발 시작

::right::

<img src="/images/Bjarne_Stroustrup_(2013).jpg" class="w-[350px] m-auto mt-4" />

---
layout: default
---

# C++로의 진화

```
1979  "C with Classes" 개발 시작 (Bjarne Stroustrup)
 │
1983  정식 명칭 "C++" 으로 변경
      (++ 는 C의 증가 연산자, "C를 한 단계 발전시킨 언어")
 │
1985  "The C++ Programming Language" 초판 출판
 │
1998  C++98 — 최초의 ISO 국제 표준
```

> 💡 `++`는 증가 연산자 — *"C보다 한 단계 나아간 언어"* 라는 의미를 담고 있습니다.

---
layout: default
---

# C++ 표준의 역사

```
C++98  ━━ 최초 ISO 표준. STL, 템플릿 도입
  │
C++03  ━━ C++98 버그 수정판
  │
C++11  ━━ ★ 대격변. auto, lambda, 스마트 포인터,
  │        move semantics, range-based for, nullptr
  │
C++14  ━━ C++11 개선 (generic lambda 등)
  │
C++17  ━━ structured bindings, if constexpr,
  │        std::optional, std::variant
  │
C++20  ━━ Concepts, Ranges, Coroutines, Modules
  │
C++23  ━━ std::print, std::expected 등 추가
```

---
layout: default
---
# 이 강의의 기준: **C++11, C++17**
- 현업에서 가장 널리 사용되는 표준
- Modern C++ 문법을 충분히 활용 가능

> 💡 C++11을 기점으로 "Modern C++"와 "Legacy C++"로 나뉩니다.

---
layout: default
---

# C와 C++의 차이점

### C는 C++에 포함되는가?
> "C++는 C의 상위 집합(superset)에 가깝지만, 완전히 동일하지는 않습니다."

| 항목 | C | C++ |
|------|---|-----|
| 패러다임 | 절차적(Procedural) | 절차적 + OOP + 제네릭 |
| 클래스 / 객체 | ❌ | ✅ |
| 함수 오버로딩 | ❌ | ✅ |
| 참조(Reference) | ❌ | ✅ |
| 표준 라이브러리 | 제한적 (stdio.h 등) | 방대한 STL |
| 메모리 관리 | `malloc` / `free` | `new` / `delete` + 스마트 포인터 |
| 타입 안전성 | 낮음 | 높음 |


---
layout: default
---
# 예시 비교

```c
/* C 스타일 */
#include <stdio.h>
int main() {
    printf("Hello, C!\n");
    return 0;
}
```
<br> </br>

```cpp
// C++ 스타일
#include <iostream>
int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

---
layout: default
---
# C++의 설계 철학

### "Zero-overhead Abstraction"
> *"What you don't use, you don't pay for."*
> — Bjarne Stroustrup

- 추상화(클래스, 템플릿 등)를 사용해도 **성능 손실이 없어야 한다**
- 직접 구현했을 때와 동일하거나 더 나은 성능을 목표로 함

<br> </br>

### 3가지 핵심 철학
| 철학 | 설명 |
|------|------|
| **Zero-overhead** | 쓰지 않는 기능에 비용을 지불하지 않는다 |
| **표현력** | 복잡한 개념을 간결하게 표현할 수 있어야 한다 |
| **하드웨어와의 근접성** | 하드웨어를 직접 제어할 수 있어야 한다 |

> 💡 Python, Java가 편의성을 위해 성능을 일부 희생하는 반면,  
> C++는 **성능을 포기하지 않는 추상화**를 지향합니다.

---
layout: default
---
# C++가 사용되는 분야 & 현업 사례

### 주요 사용 분야
| 분야 | 대표 사례 |
|------|-----------|
| 🎮 게임 엔진 | Unreal Engine, id Tech (Doom), CryEngine |
| 🌐 브라우저 / JS 엔진 | Chrome (V8), Firefox (SpiderMonkey) |
| 🖥️ 운영체제 | Windows 커널 일부, macOS 일부 |
| 💹 금융 / HFT | 초저지연 거래 시스템 |
| 🤖 AI / ML 프레임워크 | TensorFlow, PyTorch (C++ 백엔드) |
| 🔧 임베디드 / IoT | 자동차 ECU, 드론 펌웨어 |
| 🗄️ 데이터베이스 | MySQL, MongoDB, RocksDB |

> 💡 Python으로 작성된 TensorFlow도 내부 연산은 **C++로 구현**되어 있습니다.

---
layout: default
---
# 다른 언어와의 포지셔닝


### 언어별 포지셔닝 요약
| 언어 | 강점 | C++ 대비 |
|------|------|----------|
| Python | 생산성, 생태계 | 느림, 메모리 제어 어려움 |
| Java | 이식성, 안전성 | 느림, 저수준 제어 어려움 |
| Rust | 메모리 안전성 | 학습 난이도 높음, 생태계 작음 |
| **C++** | **성능 + 제어 + 생태계** | 학습 비용 있음 |

> 💡 "C++를 배우면 다른 언어가 **왜** 그렇게 설계되었는지 이해하게 됩니다."

---