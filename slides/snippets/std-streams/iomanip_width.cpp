#include <iostream>
#include <iomanip>

int main() {
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
}
