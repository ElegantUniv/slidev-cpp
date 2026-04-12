#include <iostream>

// cerr: 언버퍼드 — 즉시 출력 (에러용)
std::cerr << "치명적 오류: 메모리 부족\n";

// clog: 버퍼링 있음 — 성능 우선 (로그용)
std::clog << "[DEBUG] 함수 진입\n";
