// test_algorithms.cpp — verifies stl-algorithms.md code blocks
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <cassert>

int main() {
    std::cout << "=== stl-algorithms.md ===\n";

    // ── 알고리즘 — 컨테이너에 독립적 ──
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
        std::list<int>   l = {3, 1, 4, 1, 5, 9, 2, 6};
        std::sort(v.begin(), v.end());
        l.sort();
        std::cout << "[algo] vector sorted: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 1 2 3 4 5 6 9
        std::cout << "[algo] list sorted:   "; for (int x: l) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 1 2 3 4 5 6 9
    }

    // ── 람다 기본 문법 ──
    {
        auto f1 = [](int x){ return x * 2; };
        auto f2 = [](int a, int b){ return a > b; };
        auto f3 = [](int x) -> bool { return x > 0; };
        auto f4 = []{ return 42; };
        std::cout << "[lambda] f1(5)=" << f1(5) << " f2(3,1)=" << f2(3,1) << " f3(-1)=" << f3(-1) << " f4()=" << f4() << "\n";
        // Expected: 10 1 0 42
    }

    // ── 알고리즘에 바로 전달 ──
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9};
        auto it = std::find_if(v.begin(), v.end(), [](int x){ return x > 4; });
        std::cout << "[pass-lambda] find_if >4: " << *it << "\n";
        // Expected: 5

        std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });
        std::cout << "[pass-lambda] sorted desc: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 9 5 4 3 1 1

        std::vector<int> sq(v.size());
        std::transform(v.begin(), v.end(), sq.begin(), [](int x){ return x * x; });
        std::cout << "[pass-lambda] squares: "; for (int x: sq) std::cout << x << " "; std::cout << "\n";
        // Expected: 81 25 16 9 1 1

        int sum = std::accumulate(v.begin(), v.end(), 0, [](int acc, int x){ return acc + x; });
        std::cout << "[pass-lambda] sum: " << sum << "\n";
        // Expected: 23
    }

    // ── 람다 캡처 — 값 캡처 ──
    {
        int threshold = 30;
        std::vector<int> v = {10, 20, 30, 40, 50};
        auto it = std::find_if(v.begin(), v.end(), [threshold](int x){ return x > threshold; });
        std::cout << "[capture-val] first > 30: " << *it << "\n";
        // Expected: 40

        threshold = 100;  // doesn't affect the lambda (value capture at creation)
        auto it2 = std::find_if(v.begin(), v.end(), [threshold](int x){ return x > threshold; });
        std::cout << "[capture-val] first > 100 (threshold=100): " << (it2 == v.end() ? "없음" : std::to_string(*it2)) << "\n";
        // Expected: 없음
    }

    // ── 람다 캡처 — 참조 캡처 ──
    {
        int cnt = 0;
        std::vector<int> v = {10, 20, 30, 40, 50};
        std::for_each(v.begin(), v.end(), [&cnt](int x){ if (x > 25) cnt++; });
        std::cout << "[capture-ref] cnt (>25): " << cnt << "\n";
        // Expected: 3 (30, 40, 50)
    }

    // ── 검색 알고리즘 ──
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        auto it = std::find(v.begin(), v.end(), 30);
        if (it != v.end()) {
            std::cout << "[search] find 30: val=" << *it << " idx=" << (it - v.begin()) << "\n";
            // Expected: val=30 idx=2
        }

        auto it2 = std::find_if(v.begin(), v.end(), [](int x){ return x > 25; });
        std::cout << "[search] find_if >25: " << *it2 << "\n";
        // Expected: 30

        auto it3 = std::find_if_not(v.begin(), v.end(), [](int x){ return x < 40; });
        std::cout << "[search] find_if_not <40: " << *it3 << "\n";
        // Expected: 40
    }
    {
        std::vector<int> v = {1, 3, 5, 2, 4, 3, 3};
        std::cout << "[count] count(3)=" << std::count(v.begin(), v.end(), 3) << "\n";
        // Expected: 3
        std::cout << "[count] count_if(even)=" << std::count_if(v.begin(), v.end(), [](int x){ return x%2==0; }) << "\n";
        // Expected: 2
        std::cout << "[count] any_of(>4)=" << std::any_of(v.begin(), v.end(), [](int x){ return x>4; }) << "\n";
        // Expected: 1
        std::cout << "[count] all_of(>0)=" << std::all_of(v.begin(), v.end(), [](int x){ return x>0; }) << "\n";
        // Expected: 1
        std::cout << "[count] none_of(>10)=" << std::none_of(v.begin(), v.end(), [](int x){ return x>10; }) << "\n";
        // Expected: 1
    }

    // ── 정렬 알고리즘 ──
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
        std::sort(v.begin(), v.end());
        std::cout << "[sort] asc: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 1 2 3 4 5 6 9

        std::sort(v.begin(), v.end(), std::greater<int>());
        std::cout << "[sort] std::greater desc: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 9 6 5 4 3 2 1 1

        std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });
        std::cout << "[sort] lambda desc: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 9 6 5 4 3 2 1 1

        struct Student { std::string name; int score; };
        std::vector<Student> students = {{"A",90},{"B",90},{"C",80}};
        std::stable_sort(students.begin(), students.end(),
            [](const Student& a, const Student& b){ return a.score > b.score; });
        std::cout << "[sort] stable_sort by score desc: ";
        for (auto& s: students) std::cout << s.name << "(" << s.score << ") ";
        std::cout << "\n";
        // Expected: A(90) B(90) C(80) — A before B maintained (stable)
    }
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
        std::partial_sort(v.begin(), v.begin() + 3, v.end());
        std::cout << "[sort] partial_sort(3): "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 1 2 ... (first 3 sorted)

        std::vector<int> v2 = {3, 1, 4, 1, 5, 9, 2, 6};
        std::nth_element(v2.begin(), v2.begin() + 3, v2.end());
        std::cout << "[sort] nth_element(3): 4th smallest=" << v2[3] << "\n";
        // Expected: 3 (4th smallest of {1,1,2,3,4,5,6,9})

        std::vector<int> a = {1, 2, 3, 4, 5};
        std::vector<int> b = {3, 1, 2};
        std::cout << "[sort] is_sorted(a)=" << std::is_sorted(a.begin(), a.end())
                  << " is_sorted(b)=" << std::is_sorted(b.begin(), b.end()) << "\n";
        // Expected: 1 0
    }

    // ── 변환 알고리즘 ──
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int> result(v.size());
        std::transform(v.begin(), v.end(), result.begin(), [](int x){ return x * x; });
        std::cout << "[transform] squares: "; for (int x: result) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 4 9 16 25

        std::transform(v.begin(), v.end(), v.begin(), [](int x){ return x * 2; });
        std::cout << "[transform] double in-place: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 2 4 6 8 10

        std::vector<int> aa = {1, 2, 3};
        std::vector<int> bb = {4, 5, 6};
        std::vector<int> c(3);
        std::transform(aa.begin(), aa.end(), bb.begin(), c.begin(), [](int x, int y){ return x + y; });
        std::cout << "[transform] add two: "; for (int x: c) std::cout << x << " "; std::cout << "\n";
        // Expected: 5 7 9
    }
    {
        std::vector<int> src = {1, 2, 3, 4, 5};
        std::vector<int> dst(5);
        std::copy(src.begin(), src.end(), dst.begin());
        std::cout << "[copy] copy: "; for (int x: dst) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 2 3 4 5

        std::vector<int> evens;
        std::copy_if(src.begin(), src.end(), std::back_inserter(evens), [](int x){ return x % 2 == 0; });
        std::cout << "[copy] copy_if even: "; for (int x: evens) std::cout << x << " "; std::cout << "\n";
        // Expected: 2 4

        std::fill(dst.begin(), dst.end(), 0);
        std::cout << "[copy] fill 0: "; for (int x: dst) std::cout << x << " "; std::cout << "\n";
        // Expected: 0 0 0 0 0

        int n = 0;
        std::generate(dst.begin(), dst.end(), [&n]{ return n++; });
        std::cout << "[copy] generate: "; for (int x: dst) std::cout << x << " "; std::cout << "\n";
        // Expected: 0 1 2 3 4
    }

    // ── 집계 알고리즘 ──
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        int sum = std::accumulate(v.begin(), v.end(), 0);
        std::cout << "[accum] sum=" << sum << "\n";
        // Expected: 15

        int product = std::accumulate(v.begin(), v.end(), 1, [](int acc, int x){ return acc * x; });
        std::cout << "[accum] product=" << product << "\n";
        // Expected: 120

        std::vector<std::string> words = {"C++", " ", "STL"};
        std::string sentence = std::accumulate(words.begin(), words.end(), std::string{});
        std::cout << "[accum] string join: '" << sentence << "'\n";
        // Expected: 'C++ STL'
    }
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
        auto max_it = std::max_element(v.begin(), v.end());
        std::cout << "[minmax] max=" << *max_it << " idx=" << (max_it - v.begin()) << "\n";
        // Expected: max=9 idx=5

        auto min_it = std::min_element(v.begin(), v.end());
        std::cout << "[minmax] min=" << *min_it << "\n";
        // Expected: 1

        auto [lo, hi] = std::minmax_element(v.begin(), v.end());
        std::cout << "[minmax] minmax: " << *lo << ", " << *hi << "\n";
        // Expected: 1, 9
    }
    {
        std::vector<int> v(5);
        std::iota(v.begin(), v.end(), 1);
        std::cout << "[iota] iota(1): "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 2 3 4 5
    }

    // ── 알고리즘 조합 예제 (완전한 프로그램) ──
    {
        struct Student { std::string name; int score; };

        std::vector<Student> students = {
            {"Alice", 85}, {"Bob", 92}, {"Carol", 78},
            {"Dave", 96},  {"Eve", 70}, {"Frank", 88}
        };

        // ① 점수 내림차순 정렬
        std::sort(students.begin(), students.end(),
            [](const Student& a, const Student& b){
                return a.score > b.score;
            });
        std::cout << "[combo] sorted desc: ";
        for (auto& s: students) std::cout << s.name << "(" << s.score << ") ";
        std::cout << "\n";
        // Expected: Dave(96) Bob(92) Frank(88) Alice(85) Carol(78) Eve(70)

        // ② 80점 이상인 학생 수
        int pass = std::count_if(students.begin(), students.end(),
            [](const Student& s){ return s.score >= 80; });
        std::cout << "[combo] 합격: " << pass << "명\n";
        // Expected: 4명 (Dave, Bob, Frank, Alice)

        // ③ 전체 평균 점수
        int total = std::accumulate(students.begin(), students.end(), 0,
            [](int acc, const Student& s){ return acc + s.score; });
        double avg = static_cast<double>(total) / students.size();
        std::cout << "[combo] 평균: " << avg << "\n";
        // Expected: 84.8333...

        // ④ 90점 이상 학생 추출
        std::vector<Student> top;
        std::copy_if(students.begin(), students.end(),
            std::back_inserter(top),
            [](const Student& s){ return s.score >= 90; });
        std::cout << "[combo] 90점 이상:\n";
        for (const auto& s : top)
            std::cout << "  " << s.name << "(" << s.score << ")\n";
        // Expected: Dave(96) Bob(92)
    }

    return 0;
}
