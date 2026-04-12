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
