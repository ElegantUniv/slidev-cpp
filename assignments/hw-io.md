# C++ 프로그래밍 과제
## 표준입출력과 파일 디스크립터 분석

### 과제 목적

이 과제의 목적은 **C/C++ 프로그램의 표준입출력 구조와 운영체제의 파일 디스크립터(File Descriptor) 개념을 이해하는 것**이다.

본 과제를 통해 다음을 이해하는 것을 목표로 한다.

- 표준입출력 (`stdin`, `stdout`, `stderr`)
- Unix 파일 디스크립터(File Descriptor)
- Shell 리다이렉션
- 파이프(pipe)
- C++ 표준입출력과 OS IO 시스템의 관계

### 제출 형식

보고서 (PDF)

보고서는 다음 구조를 포함해야 한다.

1. 이론 설명
2. 실험 과정
3. 실행 결과
4. 분석 및 결론

코드는 **Appendix**에 첨부한다.

---

# 1. 이론 조사

다음 질문에 답하시오.

### (1) 파일 디스크립터란 무엇인가

다음을 설명하시오.

- File Descriptor 정의
- 왜 정수(integer)로 표현되는가
- 운영체제 내부에서 어떤 역할을 하는가

---

### (2) 표준입출력의 파일 디스크립터

Unix 시스템에서 다음 값이 의미하는 것을 설명하시오.

| 이름 | File Descriptor |
|-----|-----|
|`stdin`| 0 |
|`stdout`| 1 |
|`stderr`| 2 |

다음을 설명하시오.

- 프로그램이 시작될 때 왜 이미 열려 있는가
- 누가 생성하는가 (OS / Shell)

---

### (3) C/C++ IO와 파일 디스크립터

다음 관계를 설명하시오.

| C++ | C | OS |
|----|----|----|
| `std::cin` |`stdin`| fd 0 |
| `std::cout` |`stdout`| fd 1 |
| `std::cerr` |`stderr`| fd 2 |

다음을 설명하시오.

- C++ iostream과 OS IO 시스템의 관계
- `printf` / `cout` 의 내부 구조 차이

---

# 2. 파일 디스크립터 확인 실험

다음 프로그램을 작성하시오.

```cpp
#include <iostream>
#include <unistd.h>

int main() {

    std::cout << "STDIN FD  : " << STDIN_FILENO << std::endl;
    std::cout << "STDOUT FD : " << STDOUT_FILENO << std::endl;
    std::cout << "STDERR FD : " << STDERR_FILENO << std::endl;

}
```

프로그램을 실행하고 결과를 보고서에 포함하시오.


# 3. 표준입출력 프로그램 작성

다음 프로그램을 작성하시오.

```cpp
#include <iostream>
#include <string>

int main() {

    std::string line;

    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
    }

}
```

이 프로그램은 `stdin`에서 입력을 읽고 `stdout`으로 출력한다.

# Part 4. `stdout`/`stderr` 리다이렉션 실험

다음 프로그램을 작성하고, 실행파일명이 `test`가 되도록 빌드하시오.

```cpp
#include <iostream>

int main() {

    std::cout << "This is stdout message" << std::endl;
    std::cerr << "This is stderr message" << std::endl;

}
```

## 실험 1. 기본 실행
```bash
./test
```
출력 결과를 확인하고 설명하시오.

## 실험 2.`stdout`리다이렉션
```bash
./test > out.txt
```

다음을 설명하시오.
- `stdout`은 어디로 연결되는가
- `stderr`는 어디로 출력되는가

## 실험 3.`stderr`리다이렉션
```bash
./test 2> err.txt
```

다음을 설명하시오.
- `2>` 의 의미
- 숫자 `2`의 의미

## 4. `stdout`과 `stderr` 분리
```bash
./test > out.txt 2> err.txt
```

각 파일의 내용을 확인하고 설명하시오.

## 5. `stdout`과 `stderr`를 하나로 합치기
```bash
./test > all.txt 2>&1
```

다음을 설명하시오.
- `2>&1`의 의미
- 파일 디스크립터 관점에서 설명

# 5. `stdin` 리다이렉션 실험

다음 프로그램을 작성하고, 실행파일명이 `read_input`이 되도록 빌드하시오.
```cpp
#include <iostream>
#include <string>

int main() {

    std::string line;

    std::cout << "Reading from STDIN..." << std::endl;

    while (std::getline(std::cin, line)) {
        std::cout << "Input : " << line << std::endl;
    }

}
```


## 실험 1. 키보드 입력

```bash
./read_input
```

입력 예
```txt
apple
banana
orange
```
결과를 기록하시오.

## 실험 2. 파일로 `stdin` 대체

다음 파일을 생성한다.
```bash
input.txt
```

내용
```txt
apple
banana
orange
```

실행
```bash
./read_input < input.txt
```

다음을 설명하시오.

- 프로그램 코드를 수정하지 않았는데 파일을 읽는 이유
- Shell이 어떤 파일 디스크립터를 변경했는가

# 6. 파이프 실험

다음 명령을 실행하시오.

```bash
cat input.txt | ./read_input  # Unix/Linux/MacOS의 경우
type input.txt | ./read_input  # Windows의 경우
```



또는

```bash
echo "hello world" | ./read_input
```

다음을 설명하시오.
1. pipe의 동작 원리
2. 프로그램의 `stdin`이 무엇과 연결되는가
3. 파일 디스크립터 관점에서 설명

# 결론

보고서 마지막에 다음 질문에 답하시오.
1. 프로그램은 파일을 읽는 것이 아니라 무엇을 읽는가?
2. `stdin`/`stdout`/`stderr`는 무엇인가?
3. 다음 명령이 가능한 이유를 설명하시오.