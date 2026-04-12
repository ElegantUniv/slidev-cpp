#include <iostream>

// endl = '\n' 출력 + flush() 호출
std::cout << "결과: " << 42 << std::endl;
// ⚠️ flush가 포함 — 성능 저하

// "\n" = '\n' 출력만
std::cout << "결과: " << 42 << "\n";
// ✅ 빠름 — 버퍼링 그대로 유지
