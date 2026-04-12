#include <iostream>
#include <string>

int main() {
    std::string line;
    // ./prog < data.txt 로 실행하면
    // 파일의 내용이 cin으로 들어옴
    while (std::getline(std::cin, line)) {
        std::cout << "[처리됨] " << line << "\n";
    }
}
