// grader.cpp — stdin에서 점수를 읽어 stdout/stderr로 분리 출력
#include <iostream>
#include <string>

int main() {
    std::string name;
    int score;

    while (std::cin >> name >> score) {
        if (score < 0 || score > 100) {
            // 잘못된 데이터 → stderr
            std::cerr << "[오류] " << name
                      << ": 범위 초과 점수 " << score << "\n";
        } else {
            // 정상 데이터 → stdout
            std::cout << name << " "
                      << (score >= 60 ? "합격" : "불합격") << "\n";
        }
    }
}
