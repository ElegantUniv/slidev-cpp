---
layout: cover
---
# C++ 프로그래밍

## Junho Kim
## Kookmin University

---
layout: section
---

# C++ 개발환경 구축

---

# 개발환경 개요

## 필요한 도구

```
소스코드 (.cpp)
      │
      ▼
  g++ (GCC C++ 컴파일러)
      │
      ▼
실행 파일 (a.out / .exe)
```

<br>

| 도구 | 역할 |
|------|------|
| **g++ (GCC)** | C++ 컴파일러 |
| **GDB** | GNU 디버거 |
| **VSCode** | 코드 편집기 |

---

# 개발환경 개요

## OS별 설치 방법

| OS | 설치 방법 |
|----|-----------|
| Windows | MSYS2 + MinGW-w64 |
| macOS | Homebrew |
| Linux | apt / dnf (패키지 매니저) |

<br>

> 💡 이 강의는 **MSVC(Visual Studio)를 사용하지 않습니다.**  
> 크로스 플랫폼 환경(GCC + VSCode)에 집중합니다.

---
layout: section
---

# Windows
## GCC (MinGW-w64) 설치

---

# Windows — GCC 설치 (1/2)

## Step 1 · MSYS2 설치

**https://www.msys2.org** 에서 설치 파일 직접 다운로드

<br>

## Step 2 · MSYS2 UCRT64 터미널에서 GCC 설치

```bash
# MSYS2 UCRT64 터미널 실행 후 입력

pacman -Syu                            # 패키지 DB 업데이트

pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain # 개발용 툴체인 설치
```

---

# Windows — GCC 설치 (2/2)

## Step 3 · 환경변수 PATH 추가

```
[Windows 검색] → "시스템 환경 변수 편집"
  → 환경 변수 → Path → 새로 만들기
  → C:\msys64\ucrt64\bin  입력 후 확인
```

<br>

## Step 4 · 설치 확인

```powershell
g++ --version
# g++ (Rev1, Built by MSYS2 project) 13.x.x

gdb --version
# GNU gdb (GDB) 13.x.x
```

<br>

> 💡 MSYS2 터미널은 반드시 **MSYS2 UCRT64** 항목으로 실행하세요.  
> UCRT64 환경이어야 `g++` 경로가 올바르게 잡힙니다.

---
layout: section
---

# macOS
## GCC 설치 (Homebrew)

---

# macOS — GCC 설치

## macOS의 기본 상황 주의

```bash
gcc --version
# Apple clang version 15.x.x  ← 실제로는 Apple Clang의 별칭(alias)!
```

macOS에서 `gcc`는 **Apple Clang의 별칭**입니다. 진짜 GCC는 Homebrew로 설치합니다.

<br>

## Step 1 · Homebrew 설치

```bash
/bin/bash -c "$(curl -fsSL \
  https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Step 2 · GCC & GDB 설치

```bash
brew install gcc
brew install gdb
```

---

# macOS — GCC 설치

## Step 3 · 설치 확인 및 alias 등록

```bash
# Homebrew GCC는 버전 번호가 붙은 이름으로 설치됨
g++-13 --version
# g++ (Homebrew GCC 13.x.x) 13.x.x
```

<br>

버전 번호 없이 `g++`로 사용하고 싶다면 `~/.zshrc`에 alias 추가:

```bash
alias g++='g++-13'
alias gcc='gcc-13'
```

<br>

> ⚠️ macOS에서 GDB는 **코드 서명(Code Signing)** 설정이 추가로 필요할 수 있습니다.  
> 번거롭다면 VSCode의 LLDB 디버거를 대신 사용하세요.

---
layout: section
---

# Linux
## GCC 설치 (apt / dnf)

---

# Linux — GCC 설치

## Ubuntu / Debian 계열 (apt)

```bash
sudo apt update
sudo apt install -y build-essential   # gcc, g++, make 묶음 패키지
sudo apt install -y gdb

g++ --version
# g++ (Ubuntu 13.x.x) 13.x.x
```

<br>

## Fedora / RHEL 계열 (dnf)

```bash
sudo dnf install -y gcc gcc-c++ gdb

g++ --version
```

<br>

> 💡 실습 환경으로 **Ubuntu 22.04 LTS** 사용을 권장합니다.

---

# Linux — 여러 GCC 버전 관리

## 여러 버전 동시 설치 (Ubuntu)

```bash
sudo apt install -y g++-11 g++-12 g++-13
```

<br>

## update-alternatives로 기본 버전 설정

```bash
sudo update-alternatives \
  --install /usr/bin/g++ g++ /usr/bin/g++-13 100

sudo update-alternatives \
  --install /usr/bin/g++ g++ /usr/bin/g++-12  90

# 대화형으로 기본 버전 선택
sudo update-alternatives --config g++
```

---
layout: section
---

# g++ 컴파일 옵션
## & 첫 번째 빌드

---

# 첫 번째 빌드

## hello.cpp 작성

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

## 컴파일 & 실행

```bash
# 컴파일
g++ hello.cpp -o hello

# 실행
./hello           # Linux / macOS
.\hello.exe       # Windows PowerShell
```

---

# 주요 g++ 컴파일 옵션

| 옵션 | 의미 | 사용 시점 |
|------|------|-----------|
| `-std=c++17` | C++17 표준 사용 | 항상 |
| `-Wall` | 주요 경고 활성화 | 항상 |
| `-Wextra` | 추가 경고 활성화 | 항상 |
| `-g` | 디버그 정보 포함 | 개발 중 |
| `-O0` | 최적화 끔 (기본값) | 디버깅 시 |
| `-O2` | 최적화 레벨 2 | 릴리즈 빌드 |
| `-o <이름>` | 출력 파일명 지정 | 항상 |

<br>

### 권장 개발용 빌드 명령어

```bash
g++ -std=c++17 -Wall -Wextra -g -o hello hello.cpp
```

> 💡 `-Werror`를 추가하면 경고를 오류로 처리합니다.

---

# 컴파일 4단계

```bash
# 1단계: 전처리 (.cpp → .i)
g++ -E hello.cpp -o hello.i

# 2단계: 컴파일 (.i → .s 어셈블리)
g++ -S hello.cpp -o hello.s

# 3단계: 어셈블 (.s → .o 오브젝트)
g++ -c hello.cpp -o hello.o

# 4단계: 링크 (.o → 실행파일)
g++ hello.o -o hello
```

<br>

```
.cpp  →(전처리)→  .i  →(컴파일)→  .s  →(어셈블)→  .o  →(링크)→  실행파일
```

---
layout: section
---

# VSCode
## 설치 & C++ 환경 설정

---

# VSCode 설치 & 확장

## 설치

| OS | 설치 방법 |
|----|-----------|
| Windows | https://code.visualstudio.com 에서 다운로드 |
| macOS | `brew install --cask visual-studio-code` |
| Ubuntu | `sudo snap install code --classic` |

<br>

## 필수 확장(Extension) 설치

`Ctrl+Shift+X` → Extensions 탭

| 확장 이름 | 역할 |
|-----------|------|
| **C/C++** (Microsoft) | IntelliSense, 구문 강조, GDB 연동 |
| **C/C++ Extension Pack** (Microsoft) | C/C++ + CMake Tools 묶음 **(권장)** |

---

# VSCode — c_cpp_properties.json

`Ctrl+Shift+P` → **C/C++: Edit Configurations (UI)** 선택

```json
// .vscode/c_cpp_properties.json
{
  "configurations": [
    {
      "name": "Linux",
      "compilerPath": "/usr/bin/g++",
      "cppStandard": "c++17",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
```

<!-- <br> -->

## OS별 `compilerPath`

| OS | 경로 |
|----|------|
| Windows | `C:/msys64/ucrt64/bin/g++.exe` |
| macOS | `/opt/homebrew/bin/g++-13` |
| Linux | `/usr/bin/g++` |

---

# VSCode — tasks.json

`Ctrl+Shift+B`로 g++ 빌드를 자동 실행하는 설정 파일  


```json
// .vscode/tasks.json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build with g++",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17", "-Wall", "-Wextra", "-g",
        "${file}",
        "-o", "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "group": { "kind": "build", "isDefault": true },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```
---

# VSCode — tasks.json


| 변수 | 의미 |
|------|------|
| `${file}` | 현재 열린 파일 전체 경로 |
| `${fileDirname}` | 현재 파일의 디렉토리 |
| `${fileBasenameNoExtension}` | 확장자 없는 파일명 |

---

# VSCode — launch.json (GDB)

`F5` 키로 GDB 디버거를 실행하는 설정 파일  

```json
// .vscode/launch.json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug with GDB",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/${fileBasenameNoExtension}",
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/gdb",
      "preLaunchTask": "Build with g++"
    }
  ]
}
```

> 💡 `preLaunchTask`의 값은 tasks.json의 `label`과 **정확히 일치**해야 합니다.

---

# VSCode — 디버그 단축키

| 단축키 | 동작 |
|--------|------|
| `F5` | 디버그 시작 / 계속 |
| `F9` | 브레이크포인트 토글 |
| `F10` | 한 줄 실행 (Step Over) |
| `F11` | 함수 내부로 진입 (Step Into) |
| `Shift+F11` | 함수에서 빠져나오기 (Step Out) |
| `Shift+F5` | 디버그 중지 |

<br>

## OS별 `miDebuggerPath`

| OS | 경로 |
|----|------|
| Linux | `/usr/bin/gdb` |
| macOS | `/opt/homebrew/bin/gdb` |
| Windows | `C:/msys64/ucrt64/bin/gdb.exe` |

---
layout: section
---

# 기본 Linux Shell 명령어
---

# Shell 명령어 (1) — 파일 & 디렉토리

자세한 사항은 [**missing-semester**](https://missing-semester-kr.github.io/)를 방문해서 공부하도록 한다.


## 탐색 & 이동

```bash
pwd               # 현재 경로 출력
ls                # 파일 목록
ls -al            # 숨김 파일 포함 상세 출력
cd ~/projects     # 디렉토리 이동
cd ..             # 상위 디렉토리로
cd -              # 이전 디렉토리로
```

## 생성 / 복사 / 삭제

```bash
mkdir my_project          # 디렉토리 생성
mkdir -p src/utils        # 중간 경로 포함 생성
touch main.cpp            # 빈 파일 생성
cp main.cpp backup.cpp    # 파일 복사
cp -r src/ src_backup/    # 디렉토리 복사
mv main.cpp src/main.cpp  # 이동 / 이름 변경
rm main.cpp               # 파일 삭제
rm -rf build/             # 디렉토리 삭제 ⚠️ 복구 불가
```

---

# Shell 명령어 (2) — 컴파일 & 검색

## g++ 컴파일 패턴

```bash
g++ -std=c++17 -Wall -g main.cpp -o main && ./main

# 여러 파일
g++ -std=c++17 -Wall main.cpp utils.cpp -o app

# 오브젝트 파일 분리 빌드
g++ -std=c++17 -c main.cpp  -o main.o
g++ -std=c++17 -c utils.cpp -o utils.o
g++ main.o utils.o -o app
```

## 검색 & 파이프

```bash
grep "main" main.cpp           # 문자열 검색
grep -rn "cout" ./src          # 재귀 검색 + 줄번호
find . -name "*.cpp"           # .cpp 파일 검색
find . -name "*.o" -delete     # .o 파일 전부 삭제

ls -al | grep ".cpp"           # 파이프: .cpp 파일만 필터
```

---

# Shell 명령어 (3) — 편집기 & 권한

## 터미널 편집기

```bash
nano main.cpp     # 저장: Ctrl+O  /  종료: Ctrl+X

vim main.cpp
# i       → 입력 모드
# ESC     → 명령 모드
# :wq     → 저장 후 종료
# :q!     → 저장 없이 종료
```

## 파일 권한

```bash
ls -l main
# -rwxr-xr-x  (소유자 rwx / 그룹 r-x / 기타 r-x)

chmod +x main        # 실행 권한 추가
chmod 755 main       # rwxr-xr-x
chmod 644 main.cpp   # rw-r--r--
```

## 유용한 단축키

```
Ctrl+C  강제 종료    Ctrl+L  화면 지우기
Tab     자동완성     ↑/↓    히스토리 탐색
```

---

# Shell 명령어 — 한눈에 보기

| 카테고리 | 핵심 명령어 |
|----------|------------|
| 탐색 | `pwd`, `ls`, `cd` |
| 파일 조작 | `touch`, `cp`, `mv`, `rm`, `mkdir` |
| 내용 확인 | `cat`, `less`, `grep`, `find` |
| 빌드 & 실행 | `g++ -std=c++17 -Wall -g`, `./실행파일` |
| 편집 | `nano`, `vim` |
| 권한 | `chmod`, `ls -l` |
| 기타 | `which`, `man`, `history` |

---
layout: section
---

# Q&A