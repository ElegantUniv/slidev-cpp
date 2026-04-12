#include <iostream>
#include <string>

int main() {
    int age;
    std::string name;

    std::cin >> age;
    // ⚠️ 버퍼에 '\n' 이 남음

    std::cin.ignore();              // '\n' 제거
    std::getline(std::cin, name);   // ✅ 정상 동작
}
