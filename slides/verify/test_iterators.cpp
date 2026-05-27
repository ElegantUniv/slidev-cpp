// test_iterators.cpp — verifies stl-iterators.md code blocks
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <array>
#include <string>

int main() {
    std::cout << "=== stl-iterators.md ===\n";

    // ── 이터레이터란? — 포인터처럼 사용 ──
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        std::vector<int>::iterator it = v.begin();
        std::cout << "[iter] *begin=" << *it;
        ++it;
        std::cout << " ++it=" << *it;
        it += 2;
        std::cout << " +=2: " << *it << "\n";
        // Expected: 10 20 40

        auto it2 = v.begin();
        std::cout << "[iter] *it2=" << *it2 << "\n";
        // Expected: 10
    }

    // ── begin / end ──
    {
        std::vector<int> v = {10, 20, 30};
        auto first = v.begin();
        auto last  = v.end();
        std::cout << "[begin/end] first=" << *first << "\n";
        // Expected: 10
        // last cannot be dereferenced safely

        std::cout << "[begin/end] loop: ";
        for (auto i = v.begin(); i != v.end(); ++i)
            std::cout << *i << " ";
        std::cout << "\n";
        // Expected: 10 20 30
    }

    // ── end() — nullptr 역할 ──
    {
        // pointer pattern
        auto find_ptr = [](int* arr, int n, int val) -> int* {
            for (int i = 0; i < n; i++)
                if (arr[i] == val) return &arr[i];
            return nullptr;
        };

        int arr[] = {10, 20, 30};
        int* p = find_ptr(arr, 3, 99);
        std::cout << "[ptr-null] found 99: " << (p != nullptr) << "\n";
        // Expected: 0 (false, not found)

        std::vector<int> v = {10, 20, 30};
        auto it = std::find(v.begin(), v.end(), 99);
        std::cout << "[iter-end] found 99: " << (it != v.end()) << "\n";
        // Expected: 0 (false, not found)
    }
    {
        std::vector<int> v = {10, 20, 30};
        std::map<std::string, int> m = {{"Alice", 95}};
        std::set<int> s = {10, 20, 30};

        auto it1 = std::find(v.begin(), v.end(), 99);
        std::cout << "[end-cases] std::find 99: " << (it1 == v.end() ? "없음" : "있음") << "\n";
        // Expected: 없음

        auto it2 = m.find("Bob");
        std::cout << "[end-cases] map::find Bob: " << (it2 == m.end() ? "키 없음" : std::to_string(it2->second)) << "\n";
        // Expected: 키 없음

        auto it3 = s.find(99);
        std::cout << "[end-cases] set::find 99: " << (it3 == s.end() ? "없음" : "있음") << "\n";
        // Expected: 없음

        auto it4 = std::find_if(v.begin(), v.end(), [](int x){ return x > 100; });
        std::cout << "[end-cases] find_if >100: " << (it4 == v.end() ? "조건 불만족" : "있음") << "\n";
        // Expected: 조건 불만족
    }

    // ── 이터레이터 카테고리 ──
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        auto it = v.begin();
        it += 3;
        std::cout << "[random-access] +=3: " << *it << "\n";
        // Expected: 4
        std::cout << "[random-access] it[1]=" << it[1] << "\n";
        // Expected: 5

        std::list<int> lst = {1, 2, 3, 4, 5};
        auto it2 = lst.begin();
        ++it2;
        --it2;
        std::cout << "[bidir] after ++--: " << *it2 << "\n";
        // Expected: 1
        // it2 += 3 would be a compile error for list
    }

    // ── range-based for ──
    {
        std::vector<int> v = {10, 20, 30};
        std::cout << "[range-for] value copy: ";
        for (int x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 10 20 30

        for (int& x : v) x *= 2;
        std::cout << "[range-for] after *=2 (ref): ";
        for (const int& x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 20 40 60

        std::cout << "[range-for] const auto&: ";
        for (const auto& x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 20 40 60
    }
    {
        std::set<std::string> names = {"Charlie", "Alice", "Bob"};
        std::cout << "[range-for-set] sorted:\n";
        for (const auto& name : names) std::cout << "  " << name << "\n";
        // Expected: Alice, Bob, Charlie

        std::map<std::string, int> score = {{"Alice", 95}, {"Bob", 88}};
        std::cout << "[range-for-map] C++17:\n";
        for (const auto& [name, s] : score)
            std::cout << "  " << name << ": " << s << "\n";

        std::array<int, 3> arr = {1, 2, 3};
        std::cout << "[range-for-array]: ";
        for (const auto& x : arr) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 1 2 3
    }

    // ── const_iterator / reverse_iterator ──
    {
        std::vector<int> v = {10, 20, 30};
        std::vector<int>::const_iterator cit = v.cbegin();
        std::cout << "[const-iter] *cit=" << *cit << "\n";
        // Expected: 10
        // *cit = 99;  // compile error — not tested

        std::cout << "[const-iter] cbegin loop: ";
        for (auto it = v.cbegin(); it != v.cend(); ++it) std::cout << *it << " ";
        std::cout << "\n";
        // Expected: 10 20 30

        const std::vector<int> cv = {1, 2, 3};
        std::cout << "[const-iter] const vec: ";
        for (auto it = cv.begin(); it != cv.end(); ++it) std::cout << *it << " ";
        std::cout << "\n";
        // Expected: 1 2 3
    }
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        std::cout << "[rev-iter] vector reverse: ";
        for (auto it = v.rbegin(); it != v.rend(); ++it) std::cout << *it << " ";
        std::cout << "\n";
        // Expected: 50 40 30 20 10

        std::set<int> s = {10, 20, 30};
        std::cout << "[rev-iter] set reverse: ";
        for (auto it = s.rbegin(); it != s.rend(); ++it) std::cout << *it << " ";
        std::cout << "\n";
        // Expected: 30 20 10
    }

    return 0;
}
