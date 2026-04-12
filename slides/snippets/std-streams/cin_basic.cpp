#include <iostream>
#include <string>

int main() {
    int    age;
    double score;
    std::string name;

    // 공백/줄바꿈으로 구분된 값 읽기
    std::cin >> age;          // 정수 읽기
    std::cin >> score;        // 실수 읽기
    std::cin >> name;         // 단어 읽기 (공백 전까지)

    // 연결(chaining)
    std::cin >> age >> score >> name;

    // 입력 성공 여부 확인
    if (!(std::cin >> age)) {
        std::cerr << "잘못된 입력\n";
        std::cin.clear();            // 에러 플래그 초기화
        std::cin.ignore(1000, '\n'); // 버퍼 비우기
    }
}
