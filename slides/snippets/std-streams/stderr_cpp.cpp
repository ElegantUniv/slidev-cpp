#include <iostream>
#include <cerrno>    // errno
#include <cstring>   // strerror
#include <fstream>

int main() {
    std::ifstream file("없는파일.txt");
    if (!file) {
        // cerr: 버퍼링 없이 즉시 출력 (unbuffered)
        std::cerr << "오류: 파일을 열 수 없음\n";
        // errno 활용
        std::cerr << "errno " << errno
                  << ": " << std::strerror(errno) << "\n";
    }
    // clog: 버퍼링 있는 에러 스트림 (진단 로그용)
    std::clog << "[DEBUG] 파일 열기 시도\n";
}
