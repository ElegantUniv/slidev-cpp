#include <iostream>
#include <string>

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
