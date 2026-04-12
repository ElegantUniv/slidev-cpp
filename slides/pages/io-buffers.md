---
layout: cover
---

# C++ 프로그래밍
## 표준 스트림 버퍼와 파일 디스크립터

---
layout: default
---

# 버퍼(Buffer)란?

프로그램이 출력을 요청할 때마다 즉시 OS에 시스템 콜을 보내면 **비효율적**이다.  
버퍼는 데이터를 모았다가 **한 번에** 전달하는 중간 저장소다.

```
프로그램
  │
  │ printf("A")   ← 시스템 콜 없음
  │ printf("B")   ← 시스템 콜 없음
  │ printf("C\n") ← \n 검출 → 버퍼 플러시 → 시스템 콜
  ▼
[ 유저 공간 버퍼 ]  →  시스템 콜  →  [ OS 커널 ]  →  터미널/파일
```

| 버퍼 있음 (기본) | 버퍼 없음 |
|----------------|----------|
| 여러 번의 `printf`를 모아 한 번에 전달 | `fprintf(stderr, ...)` → 즉시 전달 |
| I/O 횟수 감소 → **성능 향상** | 항상 즉시 출력 → **신뢰성** |

> stdout은 **버퍼링**, stderr는 **버퍼링 없음** — 이유는 뒤에서 설명한다.

---
layout: default
---

# 버퍼링의 세 가지 종류

| 종류 | 플러시 시점 | 적용 대상 |
|------|-----------|----------|
| **풀 버퍼링** (Fully Buffered) | 버퍼가 가득 찰 때 | stdout → 파일/파이프 |
| **라인 버퍼링** (Line Buffered) | `\n`을 만날 때 | stdout → 터미널, stdin |
| **언버퍼드** (Unbuffered) | 즉시 | **stderr** |

<<< @/snippets/io-buffers/buffering_types.c c

> 같은 `printf`라도 실행 환경(터미널·파이프·파일)에 따라 **버퍼링 방식이 바뀐다**.

---
layout: two-cols-header
---

# stdout — 터미널 vs 파이프/파일

버퍼링 방식은 stdout이 **어디에 연결되는지**에 따라 자동으로 결정된다.

::left::

### 터미널 연결 (라인 버퍼링)

<<< @/snippets/io-buffers/stdout_line_buffered.c c 

### 파이프/파일 연결 (풀 버퍼링)

```bash {}
./prog | cat       # stdout → 파이프 → 풀 버퍼링
./prog > out.txt   # stdout → 파일  → 풀 버퍼링
```

<<< @/snippets/io-buffers/stdout_full_buffered.c c

::right::

### 버퍼 모드 강제 변경

<<< @/snippets/io-buffers/setvbuf_modes.c c

| 상수 | 모드 |
|------|------|
| `_IONBF` | 언버퍼드 |
| `_IOLBF` | 라인 버퍼링 |
| `_IOFBF` | 풀 버퍼링 |

> 파이프/파일 환경에서도 실시간 출력이 필요하면  
> `setvbuf(stdout, NULL, _IOLBF, 0)` 또는 `fflush(stdout)`을 사용한다.

---
layout: two-cols-header
---

# stderr — 언버퍼드인 이유

stderr가 버퍼 없이 즉시 출력되는 이유는 **프로그램 크래시 시에도 메시지가 유실되지 않아야** 하기 때문이다.

::left::

### 크래시 시나리오

<<< @/snippets/io-buffers/stderr_crash.c c

```bash {}
실행 결과:
위험한 작업 시작       ← stderr (이미 출력됨)
# "프로그램 시작..."은 출력되지 않음
```

### 에러 출력 함수

```c
// C
fprintf(stderr, "Error: %s\n", msg);

// perror: errno를 자동 해석
perror("fopen 실패");
// → "fopen 실패: No such file or directory"
```

::right::

### C++ `std::cerr` vs `std::clog`

<<< @/snippets/io-buffers/cerr_vs_clog.cpp cpp

| 스트림 | 버퍼링 | 언제 사용 |
|--------|--------|----------|
| `std::cout` | 있음 | 정상 출력 |
| `std::cerr` | **없음** | 에러, 경고 |
| `std::clog` | 있음 | 진단, 로그 |

<br>

```bash {}
# stdout과 stderr를 분리해서 처리
./prog > result.txt 2> error.txt

# stdout + stderr 같은 파일로
./prog > all.txt 2>&1
```

---
layout: two-cols-header
---

# 버퍼 플러시 제어

일반적으로 `"\n"` 을 사용하고, 즉시 출력이 **반드시 필요한 경우**에만 `std::endl` 또는 `fflush`를 쓴다.

::left::

### `fflush()` — 강제 플러시

<<< @/snippets/io-buffers/fflush_demo.c c

### `\n` 활용 (라인 버퍼링 환경)

```c
// 터미널에서는 \n이 즉시 플러시를 유발
printf("1단계 완료\n");   // ✅ 즉시 출력 (터미널)
printf("2단계 완료\n");   // ✅ 즉시 출력 (터미널)

// 파이프/파일에서는 \n도 즉시 플러시 안 함
// → setvbuf 또는 fflush 필요
```

::right::

### C++ `std::endl` vs `"\n"`

<<< @/snippets/io-buffers/endl_vs_newline.cpp cpp

### 성능 비교

<<< @/snippets/io-buffers/endl_perf.cpp cpp



---
layout: two-cols-header
---

# stdin 버퍼 잔류 문제

`scanf`와 `getchar`/`getline`을 혼용할 때 **버퍼에 남은 `\n`** 때문에 예상치 못한 동작이 발생한다.

::left::

### 문제 상황: C

<<< @/snippets/io-buffers/stdin_residue_c.c c

::right::


### 문제 상황: C++

<<< @/snippets/io-buffers/stdin_residue_cpp.cpp cpp


---
layout: two-cols-header
---

# stdin 잔류 문제 — 실전 권장 패턴

**줄 전체를 먼저 읽고 파싱**하면 잔류 자체가 발생하지 않는다.

::left::

### C: `fgets` + `sscanf`

<<< @/snippets/io-buffers/stdin_fix_pattern_c.c c

> `fgets`는 `\n`을 포함해 줄 끝까지 읽으므로  
> 버퍼가 항상 깨끗하게 비워진다.

::right::

### C++: `getline` + `istringstream`

<<< @/snippets/io-buffers/stdin_fix_pattern_cpp.cpp cpp

> 모든 입력을 `getline`으로 통일하면  
> `ignore()`나 `getchar()` 없이도 혼용 문제가 원천 차단된다.

---
layout: default
---

# 파일 디스크립터 — 두 개의 레이어

C/C++ I/O는 **유저 공간 레이어**와 **OS 레이어** 두 겹으로 이루어진다.

```
┌──────────────────────────────────────────────────────────────┐
│                      유저 공간 (User Space)                    │
│                                                              │
│  FILE* stdin   FILE* stdout   FILE* stderr                   │
│  (유저 버퍼 포함)  (유저 버퍼 포함)  (버퍼 없음)                │
│      │               │               │                       │
│      └───────────────┼───────────────┘                       │
│                      │  fread / fwrite / fprintf ...         │
│                      ▼  (버퍼 가득 차거나 fflush 시)           │
│                  [ 시스템 콜 ]                                 │
├──────────────────────────────────────────────────────────────┤
│                      OS 커널 (Kernel Space)                   │
│                                                              │
│   파일 디스크립터 테이블 (프로세스마다 존재)                      │
│   FD 0 (stdin)  → 키보드 드라이버                              │
│   FD 1 (stdout) → 터미널 드라이버 (또는 파일/파이프)             │
│   FD 2 (stderr) → 터미널 드라이버 (또는 파일/파이프)             │
└──────────────────────────────────────────────────────────────┘
```

> `FILE*`은 파일 디스크립터(정수)를 **감싼(wrap) 구조체**다.  
> 유저 공간에서 버퍼를 관리하고, OS에 넘길 때만 시스템 콜을 호출한다.

---
layout: two-cols-header
---

# `FILE*`과 파일 디스크립터의 관계

`FILE*` 구조체 안에는 **파일 디스크립터 번호**가 포함되어 있다.



::left::

### `FILE*` 내부 구조 (개념)

```
FILE* stdout 구조체
┌─────────────────────────┐
│ fd = 1                  │  ← 파일 디스크립터 번호
│ buf_start = 0x...       │  ← 유저 버퍼 시작
│ buf_end   = 0x...       │  ← 유저 버퍼 끝
│ write_pos = 0x...       │  ← 현재 쓰기 위치
│ ...                     │
└─────────────────────────┘
```

::right::


### `fileno()` — FD 번호 확인

<<< @/snippets/io-buffers/fileno_demo.c c

> `fileno()`는 C 표준 함수로 모든 플랫폼에서 동작한다.  
> FD 번호 0 / 1 / 2 는 OS에 관계없이 동일하게 예약되어 있다.


---
layout: two-cols-header
---

# 리다이렉션과 파일 디스크립터

쉘의 `>`, `<`, `|` 기호는 **FD가 가리키는 대상을 바꿔** 스트림 방향을 전환한다.

::left::

### 쉘 리다이렉션

```bash {}
# FD 1(stdout) → 파일
./prog > out.txt

# FD 0(stdin) ← 파일
./prog < input.txt

# FD 2(stderr) → 파일
./prog 2> error.txt

# FD 1과 FD 2 모두 같은 파일로
./prog > out.txt 2>&1

# FD 1 → 파이프 → 다음 프로그램의 FD 0
./prog | ./next
```

프로그램 코드는 변경 없이 `printf`/`scanf`를 그대로 쓴다.  
**OS가 FD의 연결 대상만 바꾸면** 데이터 흐름이 달라진다.

::right::

### 프로그램 내 스트림 분리 활용

<<< @/snippets/io-buffers/fd_grader.cpp cpp

```bash {}
./grader < scores.txt              # 터미널에 모두 출력
./grader < scores.txt > result.txt # 정상 결과만 파일로
./grader < scores.txt 2> err.txt   # 에러만 파일로
```

---
layout: two-cols-header
---

# 요약

::left::

### 버퍼링

```txt {}
stdout (터미널)    : 라인 버퍼링  → \n 또는 fflush(stdout) 로 플러시
stdout (파일/파이프): 풀 버퍼링   → 버퍼가 차거나 프로그램 종료 시 플러시
stderr             : 언버퍼드    → 항상 즉시 출력 (크래시에도 안전)
stdin              : 라인 버퍼링  → Enter 입력 시 프로그램에 전달
```

### 버퍼 제어

```c {}
// C
fflush(stdout);                    // 즉시 플러시
setvbuf(stdout, NULL, _IONBF, 0);  // 언버퍼드로 변경
```

```cpp {}
// C++
std::cout << "..." << "\n";        // ✅ 빠름
std::cout << "..." << std::endl;   // ⚠️ flush 포함 — 루프 안에서 주의
```

### stdin 잔류 문제

```c {}
// C
scanf("%d", &n);   getchar();       // '\n' 제거 후 다음 입력
scanf(" %c", &c);                   // 포맷 앞 공백으로 해결
```

```cpp 
// C++
std::cin >> n;   std::cin.ignore(); // '\n' 제거
std::getline(std::cin, s);          // ✅ 한 줄 입력
```

::right::

### 파일 디스크립터와의 관계

```
FILE* (유저 공간, 버퍼링 있음)
  ↕  fileno() / fdopen() / freopen()   ← C 표준, 모든 플랫폼 동작
파일 디스크립터 0 / 1 / 2 (OS 커널, 버퍼링 없음)
  ↕  쉘 리다이렉션 (>, <, 2>, |)
실제 디바이스: 키보드 / 터미널 / 파일 / 파이프
```
