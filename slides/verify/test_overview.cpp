// test_overview.cpp — verifies stl-overview.md code blocks
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cassert>
#include <string>

int main() {
    std::cout << "=== stl-overview.md ===\n";

    // Block 1: STL이란? (complete program fragment)
    {
        std::vector<int> scores = {85, 92, 78, 95, 88};
        std::sort(scores.begin(), scores.end());
        std::cout << "[B1] sorted scores: ";
        for (int s : scores) std::cout << s << " ";
        std::cout << "\n";
        // Expected: 78 85 88 92 95

        std::map<std::string, int> student;
        student["Alice"] = 95;
        student["Bob"]   = 88;
        std::cout << "[B1] Alice score: " << student["Alice"] << "\n";
        // Expected: 95
    }

    // Block 2: 컨테이너 예시
    {
        std::vector<int> v = {1, 2, 3};
        std::set<int>    s = {3, 1, 2};
        std::map<std::string, int> m;
        m["one"] = 1;
        std::cout << "[B2] v[0]=" << v[0] << " s.size=" << s.size() << " m[one]=" << m["one"] << "\n";
        // Expected: v[0]=1 s.size=3 m[one]=1
    }

    // Block 3: 이터레이터 예시
    {
        std::vector<int> v = {10, 20, 30};
        auto it = v.begin();
        std::cout << "[B3] *it=" << *it;  // 10
        ++it;
        std::cout << " ++it=" << *it << "\n";  // 20
    }

    // Block 4: 알고리즘 예시
    {
        std::vector<int> v = {3, 1, 4, 1, 5};
        std::sort(v.begin(), v.end());
        std::cout << "[B4] sorted: ";
        for (int x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 1 1 3 4 5

        auto it = std::find(v.begin(), v.end(), 3);
        std::cout << "[B4] found 3: " << *it << "\n";  // 3

        int sum = std::accumulate(v.begin(), v.end(), 0);
        std::cout << "[B4] sum: " << sum << "\n";  // 14
    }

    // Block 5: 람다/함수객체 예시
    {
        std::vector<int> v = {3, 1, 4, 1, 5};
        std::sort(v.begin(), v.end(), std::greater<int>());
        std::cout << "[B5] descending: ";
        for (int x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 5 4 3 1 1

        auto it2 = std::find_if(v.begin(), v.end(),
            [](int x){ return x > 3; });
        std::cout << "[B5] first >3: " << *it2 << "\n";  // 4 or 5
    }

    return 0;
}
