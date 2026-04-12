#include <iostream>
#include <string>

int main() {
    int age;
    std::string name;

    // C++ 에서도 동일한 문제 발생
    std::cin >> age;                
    // 입력: "25\n"
    // age = 25, 버퍼에 '\n' 남음   
    std::getline(std::cin, name);   // '\n'만 읽고 끝남
    // name = ""  ← 의도와 다름
}






