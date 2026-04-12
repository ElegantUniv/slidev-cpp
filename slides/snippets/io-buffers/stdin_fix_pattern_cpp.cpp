#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line;
    std::string name;
    int age;

    // getline: 줄 전체 소비 — '\n'이 버퍼에 남지 않음
    if (std::getline(std::cin, line))
        std::istringstream(line) >> name;

    if (std::getline(std::cin, line))
        std::istringstream(line) >> age;

    std::cout << "이름: " << name << ", 나이: " << age << "\n";
}
