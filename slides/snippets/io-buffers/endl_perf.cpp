// ❌ 느림 — 매 줄마다 flush
for (int i = 0; i < 100000; i++) {
    std::cout << i << std::endl;
}

// ✅ 빠름 — 버퍼링 활용
for (int i = 0; i < 100000; i++) {
    std::cout << i << "\n";
}
// 마지막에 한 번 flush (또는 자동)
