// C++ 방법 1: ignore()
int age;
std::string name;

std::cin >> age;
std::cin.ignore();              // '\n' 하나 제거
std::getline(std::cin, name);   // ✅

// C++ 방법 2: 충분히 무시
std::cin.ignore(
    std::numeric_limits<std::streamsize>::max(), '\n');
