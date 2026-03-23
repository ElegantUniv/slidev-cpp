---
layout: cover
---

# C++ 프로그래밍
## 표준 스트림 — stdin / stdout / stderr

---
layout: default
---

# 세 가지 표준 스트림

모든 프로그램은 시작할 때 운영체제로부터 세 개의 스트림을 자동으로 받는다.

```
┌─────────────────────────────────────────────────────────────┐
│                         프로그램                             │
│                                                             │
│   stdin  ──────────────────────────────►  (입력 읽기)        │
│   (fd 0)   키보드 / 파일 / 파이프                             │
│                                                             │
│   stdout ◄──────────────────────────────  (정상 출력)        │
│   (fd 1)   터미널 / 파일 / 파이프                             │
│                                                             │
│   stderr ◄──────────────────────────────  (에러 출력)        │
│   (fd 2)   터미널 (stdout과 독립적)                           │
└─────────────────────────────────────────────────────────────┘
```

| 스트림 | 파일 기술자 | C | C++ | 기본 방향 |
|--------|------------|---|-----|-----------|
| **stdin** | `0` | `scanf`, `fgets`, `getchar` | `std::cin` | 키보드 |
| **stdout** | `1` | `printf`, `puts` | `std::cout` | 터미널 |
| **stderr** | `2` | `fprintf(stderr, …)`, `perror` | `std::cerr` | 터미널 |

> stdout은 **버퍼링**되고, stderr는 **버퍼링 없이** 즉시 출력된다.

---
layout: two-cols-header
---

# C vs C++ 표준 입출력 개요

::left::

## C 스타일

```c
#include <stdio.h>

int main(void) {
    int age;
    char name[32];

    // stdout 출력
    printf("이름을 입력하세요: ");

    // stdin 입력
    scanf("%s", name);
    scanf("%d", &age);

    printf("안녕하세요, %s님! 나이: %d\n",
           name, age);
    return 0;
}
```

- **형식 지정자** (`%d`, `%s`, …) 직접 작성
- 타입 불일치 시 **런타임 오류** (컴파일 오류 아님)
- `scanf`에 `&` 연산자 필요 (포인터 전달)

::right::

## C++ 스타일

```cpp
#include <iostream>
#include <string>

int main() {
    int age;
    std::string name;

    // stdout 출력
    std::cout << "이름을 입력하세요: ";

    // stdin 입력
    std::cin >> name >> age;

    std::cout << "안녕하세요, " << name
              << "님! 나이: " << age << "\n";
    return 0;
}
```

- **형식 지정자 없음** — 타입을 자동으로 인식
- 타입 불일치 시 **컴파일 오류** (더 안전)
- `&` 연산자 불필요

---
layout: two-cols-header
---

# `std::cout` — 기본 출력

`<<` 연산자(삽입 연산자)로 값을 출력 스트림에 밀어 넣는다.

::left::

## 기본 사용

```cpp {}
#include <iostream>

int main() {
    int    n = 42;
    double d = 3.14;
    bool   b = true;
    std::string s = "hello";

    std::cout << n << "\n";    // 42
    std::cout << d << "\n";    // 3.14
    std::cout << b << "\n";    // 1  (기본값)
    std::cout << s << "\n";    // hello

    // 연결(chaining) — 한 줄에 여러 값 출력
    std::cout << "n=" << n
              << ", d=" << d << "\n";
}
```

## `"\n"` vs `std::endl`

```cpp {}
std::cout << "줄 바꿈\n";           // ✅ 빠름
std::cout << "줄 바꿈" << std::endl; // ⚠️ flush 포함 — 느림
// endl은 버퍼를 즉시 비움 → 성능 저하
// 일반적으로 "\n" 사용 권장
```

::right::

## `using namespace std`

```cpp {}
// std:: 접두사를 생략할 수 있음
using namespace std;

cout << "hello\n";   // std::cout 대신
cin  >> n;           // std::cin  대신

// ⚠️ 헤더 파일에서는 사용하지 말 것
//    이름 충돌을 일으킬 수 있음
```

## `printf` vs `std::cout` 핵심 차이

```cpp {}
int n = 42; double d = 3.14159;

// printf: 형식 지정자 필요
printf("%.2f\n", d);
printf("%10d\n", n);

// cout: 조작자로 서식 제어
std::cout << std::fixed
          << std::setprecision(2) << d << "\n";
std::cout << std::setw(10) << n << "\n";

// ❌ printf 타입 불일치 → 런타임 UB
printf("%d\n", d);
// ✅ cout 타입 불일치 → 컴파일 오류
```

---
layout: two-cols-header
---

# `std::cout` — 서식 조작자 (`<iomanip>`)

`printf`의 형식 지정자에 대응하는 C++의 출력 서식 제어 도구다.

::left::

## 숫자 서식

```cpp {}
#include <iostream>
#include <iomanip>

double pi = 3.141592653589793;
int    n  = 255;

// 소수점 자릿수
std::cout << std::fixed
          << std::setprecision(2) << pi << "\n"; // 3.14
std::cout << std::setprecision(5) << pi << "\n"; // 3.14159

// 진법 출력
std::cout << std::dec << n << "\n";  // 255  (10진수)
std::cout << std::hex << n << "\n";  // ff   (16진수)
std::cout << std::oct << n << "\n";  // 377  (8진수)
std::cout << std::hex << std::uppercase
          << n << "\n";              // FF   (대문자)

// 부호 강제 출력
std::cout << std::showpos << 42 << "\n";  // +42
```

::right::

## 폭(width)과 정렬

```cpp {}
#include <iomanip>

// setw: 다음 출력 한 번에만 적용
std::cout << std::setw(10) << 42   << "\n";
// "        42"  (오른쪽 정렬, 기본)

std::cout << std::left
          << std::setw(10) << "hi" << "|\n";
// "hi        |"  (왼쪽 정렬)

// 빈 자리 채우기
std::cout << std::setfill('0')
          << std::setw(6) << 42 << "\n";  // 000042

// 표 형식 출력
std::cout << std::left
          << std::setw(12) << "이름"
          << std::setw(6)  << "나이"
          << std::setw(8)  << "점수" << "\n";
std::cout << std::setw(12) << "홍길동"
          << std::setw(6)  << 20
          << std::setw(8)  << 95.5  << "\n";
```

---
layout: two-cols-header
---

# stderr — 에러 스트림

정상 출력(stdout)과 에러 출력(stderr)을 분리하면 **리다이렉션으로 각각 따로 처리**할 수 있다.

::left::

## C — `fprintf(stderr, …)` / `perror`

```c
#include <stdio.h>
#include <errno.h>   // errno
#include <string.h>  // strerror

FILE* fp = fopen("없는파일.txt", "r");

if (fp == NULL) {
    // fprintf(stderr, ...): 에러 스트림에 직접 출력
    fprintf(stderr, "오류: 파일을 열 수 없음\n");

    // perror: errno를 해석해 자동으로 stderr에 출력
    perror("fopen 실패");
    // 출력 예: "fopen 실패: No such file or directory"

    // strerror: errno 코드를 문자열로 변환
    fprintf(stderr, "errno %d: %s\n",
            errno, strerror(errno));
    return 1;
}
```

- `perror(msg)` = `fprintf(stderr, "%s: %s\n", msg, strerror(errno))`
- `errno`: 마지막 시스템 호출의 오류 코드 (전역 변수)

::right::

## C++ — `std::cerr` / `std::clog`

```cpp
#include <iostream>
#include <cerrno>    // errno
#include <cstring>   // strerror
#include <fstream>

std::ifstream file("없는파일.txt");

if (!file) {
    // cerr: 버퍼링 없이 즉시 출력 (unbuffered)
    std::cerr << "오류: 파일을 열 수 없음\n";

    // errno 활용
    std::cerr << "errno " << errno
              << ": " << std::strerror(errno) << "\n";
}

// clog: 버퍼링 있는 에러 스트림 (진단 로그용)
std::clog << "[DEBUG] 파일 열기 시도\n";
```

| 스트림 | 버퍼링 | 용도 |
|--------|--------|------|
| `std::cout` | 있음 | 정상 출력 |
| `std::cerr` | **없음** | 즉시 에러 출력 |
| `std::clog` | 있음 | 진단·로그 출력 |

---
layout: two-cols-header
---

# `std::cin` — 기본 입력

`>>` 연산자(추출 연산자)로 입력 스트림에서 값을 읽는다.

::left::

## 기본 사용

```cpp {}
#include <iostream>
#include <string>

int    age;
double score;
std::string name;

// 공백/줄바꿈으로 구분된 값 읽기
std::cin >> age;          // 정수 읽기
std::cin >> score;        // 실수 읽기
std::cin >> name;         // 단어 읽기 (공백 전까지)

// 연결(chaining)
std::cin >> age >> score >> name;

// 입력 성공 여부 확인
if (!(std::cin >> age)) {
    std::cerr << "잘못된 입력\n";
    std::cin.clear();            // 에러 플래그 초기화
    std::cin.ignore(1000, '\n'); // 버퍼 비우기
}
```

::right::

## `scanf` vs `std::cin`

```cpp {}
// C: scanf — 형식 지정자 + & 연산자 필요
int a; double b;
scanf("%d %lf", &a, &b);

// ❌ & 빠뜨리면 런타임 크래시
scanf("%d", a);   // *a 에 쓰려 함 → UB

// C++: cin — & 불필요, 타입 자동 인식
int a; double b;
std::cin >> a >> b;

// ✅ 타입 안전 — 잘못된 타입은 컴파일러가 잡음
```

<br>

## `>>` 후 `getline` 주의

```cpp {}
int age;
std::string name;

std::cin >> age;
// ⚠️ 버퍼에 '\n' 이 남음

std::cin.ignore();              // '\n' 제거
std::getline(std::cin, name);   // ✅ 정상 동작
```

---
layout: two-cols-header
---

# `std::cin` — 한 줄 입력 (`getline`)

`>>` 연산자는 **공백에서 멈춘다**. 공백 포함 한 줄을 읽으려면 `std::getline`을 사용한다.

::left::

## `>>` vs `getline`

```cpp {}
std::string s;

// >> 는 공백 전까지만 읽음
std::cin >> s;
// 입력: "홍 길동"
// s = "홍"  (길동은 버퍼에 남음)

// getline은 줄 전체 읽음
std::getline(std::cin, s);
// 입력: "홍 길동"
// s = "홍 길동" ✅
```

## EOF까지 모든 줄 읽기

```cpp {}
std::string line;
while (std::getline(std::cin, line)) {
    std::cout << line << "\n";
}
// 파일 리다이렉션이나 파이프로 전달된
// 모든 내용을 처리할 때 유용
```

::right::

## `scanf` 한 줄 읽기 vs `getline`

```cpp {}
// C: 크기 제한 필요, 문법 복잡
char buf[64];
scanf(" %63[^\n]", buf);   // 공백 먹고 줄 끝까지
// ⚠️ 버퍼 크기 초과 시 UB

// C (fgets — 더 안전)
fgets(buf, sizeof(buf), stdin);
// '\n'이 버퍼에 포함될 수 있음 (직접 제거 필요)

// C++: 간단하고 안전
std::string line;
std::getline(std::cin, line);  // 크기 제한 없음 ✅
```

---
layout: two-cols-header
---

# 커맨드라인 스트림 리다이렉션

쉘에서 `<`, `>`, `2>` 기호로 **스트림의 방향을 파일이나 다른 프로그램으로** 바꿀 수 있다.

::left::

## 기본 리다이렉션

```bash
# stdout을 파일로 저장 (덮어쓰기)
./prog > output.txt

# stdout을 파일에 추가 (append)
./prog >> output.txt

# stdin을 파일에서 읽기
./prog < input.txt

# stderr를 파일로 저장
./prog 2> error.txt

# stdout과 stderr 모두 같은 파일로
./prog > output.txt 2>&1

# stderr만 버리기 (Linux/macOS)
./prog 2> /dev/null

# stdout과 stderr 모두 버리기
./prog > /dev/null 2>&1
```

::right::

## 파이프 (`|`)

```bash
# 첫 번째 프로그램의 stdout을
# 두 번째 프로그램의 stdin으로 연결
./producer | ./consumer

# 여러 프로그램 연결
./prog | sort | uniq > result.txt

# stdin/stdout/stderr 모두 제어
./prog < in.txt > out.txt 2> err.txt
```

## 프로그램 내에서 활용

```cpp
// stdin이 파일 리다이렉션인지 확인
// (터미널에서 입력받는 게 아닐 때)
#include <iostream>

int main() {
    std::string line;
    // ./prog < data.txt 로 실행하면
    // 파일의 내용이 cin으로 들어옴
    while (std::getline(std::cin, line)) {
        std::cout << "[처리됨] " << line << "\n";
    }
}
```

---
layout: default
---

# 리다이렉션 실습 예제

```cpp
// grader.cpp — stdin에서 점수를 읽어 stdout/stderr로 분리 출력
#include <iostream>
#include <string>

int main() {
    std::string name;
    int score;

    while (std::cin >> name >> score) {
        if (score < 0 || score > 100) {
            // 잘못된 데이터 → stderr
            std::cerr << "[오류] " << name
                      << ": 범위 초과 점수 " << score << "\n";
        } else {
            // 정상 데이터 → stdout
            std::cout << name << " "
                      << (score >= 60 ? "합격" : "불합격") << "\n";
        }
    }
}
```

```bash
# input.txt 내용:
# 홍길동 85
# 이순신 110
# 강감찬 55

./grader < input.txt             # stdout + stderr 모두 터미널에 출력
./grader < input.txt > result.txt          # 정상 결과만 파일로
./grader < input.txt 2> errors.txt         # 에러만 파일로
./grader < input.txt > result.txt 2> errors.txt  # 각각 분리
```

> stdout과 stderr를 처음부터 **분리해서 작성**하면 리다이렉션으로 유연하게 처리할 수 있다.

---
layout: default
---

# `printf` / `scanf` vs `std::cout` / `std::cin` 비교표

| 항목 | `printf` / `scanf` | `std::cout` / `std::cin` |
|------|--------------------|--------------------------|
| 헤더 | `<cstdio>` | `<iostream>` |
| 형식 지정자 | 직접 작성 (`%d`, `%f`, …) | 불필요 — 타입 자동 인식 |
| 타입 안전성 | ❌ 런타임에서야 오류 발견 | ✅ 컴파일 타임 오류 |
| `scanf` `&` 연산자 | 필요 (`&a`) | 불필요 (`cin >> a`) |
| 에러 출력 | `fprintf(stderr, …)` / `perror` | `std::cerr <<` |
| 사용자 정의 타입 출력 | 불가 | ✅ `operator<<` 오버로딩 |
| 공백 포함 문자열 입력 | `fgets` / `scanf("%[^\n]", …)` | `std::getline(cin, s)` |
| 성능 | 빠름 | 기본적으로 약간 느림\* |
| 서식 제어 | 형식 지정자 인라인 | `<iomanip>` 조작자 사용 |

<br>

> \* `std::ios::sync_with_stdio(false); std::cin.tie(nullptr);`를 `main` 시작에 추가하면
> `printf`/`scanf`와 동등한 속도를 낼 수 있다. 단, 이후 `printf`/`scanf`와 **혼용 금지**.

---
layout: default
---

# 요약

```cpp {}
#include <iostream>   // cout, cin, cerr, clog
#include <iomanip>    // setw, setprecision, setfill, ...
#include <string>     // std::string + getline

// stdout 출력
std::cout << 값 << "\n";
std::cout << std::fixed << std::setprecision(2) << 3.14 << "\n";

// stderr 출력 (에러)
std::cerr << "에러 메시지\n";          // C++
fprintf(stderr, "에러: %s\n", msg);    // C
perror("시스템 호출 실패");             // C — errno 자동 해석

// stdin 입력
std::cin >> 변수 >> 변수;          // 공백 구분
std::getline(std::cin, str);       // 한 줄 전체
std::cin.ignore();                 // >> 후 getline 전 '\n' 제거
```

```bash
# 커맨드라인 리다이렉션
./prog < input.txt              # stdin  ← 파일
./prog > output.txt             # stdout → 파일
./prog 2> error.txt             # stderr → 파일
./prog > out.txt 2>&1           # stdout + stderr → 같은 파일
./prog < in.txt | ./next        # stdout → 다음 프로그램의 stdin
```

| 상황 | 권장 |
|------|------|
| 정상 출력 | `std::cout` / `printf` |
| 에러·경고 출력 | `std::cerr` / `fprintf(stderr, …)` |
| 시스템 에러 출력 | `perror(msg)` (C) |
| 공백 포함 한 줄 입력 | `std::getline(std::cin, str)` |
| 파일 전체 줄 처리 | `while (std::getline(std::cin, line))` |
