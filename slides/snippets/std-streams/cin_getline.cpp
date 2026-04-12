#include <iostream>
#include <string>

int main() {
    std::string s;

    // >> 는 공백 전까지만 읽음
    std::cin >> s;
    // 입력: "홍 길동"
    // s = "홍"  (길동은 버퍼에 남음)

    // getline은 줄 전체 읽음
    std::getline(std::cin, s);
    // 입력: "홍 길동"
    // s = "홍 길동" ✅
}
