#include <iostream>
#include <iomanip>

int main() {
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
}
