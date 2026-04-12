#include <iostream>
#include <string>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << "\n";
    }
    // 파일 리다이렉션이나 파이프로 전달된
    // 모든 내용을 처리할 때 유용
}
