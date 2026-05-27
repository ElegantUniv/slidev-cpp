// test_sequence.cpp — verifies stl-sequence.md code blocks
#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <deque>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <string>

void print_vec(const std::vector<int>& v, const char* label="") {
    std::cout << label << "{ ";
    for (int x : v) std::cout << x << " ";
    std::cout << "}\n";
}
void print_list(const std::list<int>& lst, const char* label="") {
    std::cout << label << "{ ";
    for (int x : lst) std::cout << x << " ";
    std::cout << "}\n";
}

int main() {
    std::cout << "=== stl-sequence.md ===\n";

    // ── vector 생성과 기본 조작 ──
    {
        std::vector<int> v1;
        std::vector<int> v2 = {10, 20, 30};
        std::vector<int> v3(5, 0);
        std::vector<int> v4 = v2;
        std::cout << "[vec-gen] v2: "; for (int x: v2) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30
        std::cout << "[vec-gen] v3: "; for (int x: v3) std::cout << x << " "; std::cout << "\n";
        // Expected: 0 0 0 0 0
    }
    {
        std::vector<int> v;
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);
        std::cout << "[vec-ops] size=" << v.size() << " empty=" << v.empty() << "\n";
        // Expected: size=3 empty=0
        std::cout << "[vec-ops] front=" << v.front() << " back=" << v.back() << "\n";
        // Expected: front=10 back=30
        v.pop_back();
        std::cout << "[vec-ops] after pop_back size=" << v.size() << "\n";
        // Expected: size=2
    }

    // ── vector 이터레이터와 순회 ──
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        auto it = v.begin();
        std::cout << "[vec-iter] *begin=" << *it;
        ++it;
        std::cout << " ++it=" << *it << "\n";
        // Expected: 10 20

        std::cout << "[vec-iter] forward: ";
        for (auto i = v.begin(); i != v.end(); ++i) std::cout << *i << " ";
        std::cout << "\n";
        // Expected: 10 20 30 40 50
    }
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        std::cout << "[vec-rangefor] copy: ";
        for (int x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 10 20 30 40 50

        for (auto& x : v) x *= 2;
        std::cout << "[vec-rangefor] after *=2: ";
        for (const auto& x : v) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 20 40 60 80 100
    }

    // ── vector + 알고리즘: 검색 ──
    {
        std::vector<int> v = {10, 30, 20, 50, 40};
        auto it = std::find(v.begin(), v.end(), 30);
        if (it != v.end()) {
            std::cout << "[find] val=" << *it << " idx=" << (it - v.begin()) << "\n";
            // Expected: val=30 idx=1
        }
        auto it2 = std::find(v.begin(), v.end(), 99);
        std::cout << "[find] 99 found=" << (it2 != v.end()) << "\n";
        // Expected: 0 (false)
    }
    {
        std::vector<int> v = {10, 30, 20, 50, 40};
        auto it = std::find_if(v.begin(), v.end(), [](int x){ return x > 30; });
        std::cout << "[find_if] first>30: " << *it << "\n";
        // Expected: 50

        auto it2 = std::find_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
        std::cout << "[find_if] first even: " << *it2 << "\n";
        // Expected: 10

        bool any = std::any_of(v.begin(), v.end(), [](int x){ return x > 45; });
        std::cout << "[any_of] any>45: " << any << "\n";
        // Expected: 1 (true, 50>45)
    }

    // ── vector + 알고리즘: 정렬·집계 ──
    {
        std::vector<int> v = {30, 10, 50, 20, 40};
        std::sort(v.begin(), v.end());
        std::cout << "[sort] asc: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40 50

        std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });
        std::cout << "[sort] desc: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 50 40 30 20 10

        // partial sort first 3 of {50, 40, 30, 20, 10}
        std::sort(v.begin(), v.begin() + 3);
        std::cout << "[sort] partial3: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 30 40 50 20 10
    }
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        int cnt = std::count_if(v.begin(), v.end(), [](int x){ return x >= 30; });
        std::cout << "[count_if] >=30: " << cnt << "\n";
        // Expected: 3
    }
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        int sum = std::accumulate(v.begin(), v.end(), 0);
        std::cout << "[accum] sum: " << sum << "\n";
        // Expected: 150

        int product = std::accumulate(v.begin(), v.end(), 1,
            [](int acc, int x){ return acc * x; });
        std::cout << "[accum] product: " << product << "\n";
        // Expected: 12000000

        auto max_it = std::max_element(v.begin(), v.end());
        auto min_it = std::min_element(v.begin(), v.end());
        std::cout << "[max/min] max=" << *max_it << " min=" << *min_it << "\n";
        // Expected: max=50 min=10
    }

    // ── vector 원소 접근과 수정 ──
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        std::cout << "[access] v[0]=" << v[0] << " v[4]=" << v[4] << " v.at(2)=" << v.at(2) << "\n";
        // Expected: 10 50 30
        try {
            v.at(10);
        } catch (const std::out_of_range& e) {
            std::cout << "[access] out_of_range caught: " << e.what() << "\n";
        }
        std::cout << "[access] front=" << v.front() << " back=" << v.back() << "\n";
        // Expected: 10 50
    }
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        v[1] = 99;
        v.at(3) = 77;
        std::cout << "[modify] after set [1]=99 [3]=77: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 99 30 77 50
        for (auto& x : v) x *= 2;
        std::cout << "[modify] after *=2: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 20 198 60 154 100
        v.assign(3, 0);
        std::cout << "[modify] after assign(3,0): "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 0 0 0
    }

    // ── vector 삽입과 삭제 ──
    {
        std::vector<int> v = {10, 20, 30};
        v.push_back(40);
        v.emplace_back(50);
        std::cout << "[insert] after push+emplace: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40 50
        v.pop_back();
        std::cout << "[insert] after pop_back: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40
    }
    {
        std::vector<int> v = {10, 30, 40};
        v.insert(v.begin() + 1, 20);
        std::cout << "[insert-mid] after insert(1,20): "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40
        v.insert(v.end(), {50, 60});
        std::cout << "[insert-mid] after insert(end,50,60): "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40 50 60
    }
    {
        std::vector<int> v = {10, 20, 30, 40, 50};
        auto it = v.begin() + 2;
        it = v.erase(it);
        std::cout << "[erase] after erase(2): "; for (int x: v) std::cout << x << " "; std::cout << " next=" << *it << "\n";
        // Expected: 10 20 40 50, next=40
        v.erase(v.begin() + 1, v.begin() + 3);
        std::cout << "[erase] after erase(1,3): "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 50
        v.clear();
        std::cout << "[erase] after clear: size=" << v.size() << "\n";
        // Expected: 0
    }

    // ── vector size와 capacity ──
    {
        std::vector<int> v;
        std::cout << "[cap] empty: size=" << v.size() << " cap=" << v.capacity() << "\n";
        v.push_back(1); v.push_back(2); v.push_back(3);
        std::cout << "[cap] 3 elements: size=" << v.size() << " cap=" << v.capacity() << "\n";
        v.push_back(4); v.push_back(5);
        std::cout << "[cap] 5 elements: size=" << v.size() << " cap=" << v.capacity() << "\n";
    }
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        v.resize(3);
        std::cout << "[resize] to 3: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 2 3
        v.resize(6, 0);
        std::cout << "[resize] to 6 with 0: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 2 3 0 0 0
        v.clear();
        std::cout << "[resize] after clear: size=" << v.size() << "\n";
        // Expected: 0
    }

    // ── std::list ──
    {
        std::list<int> lst1;
        std::list<int> lst2 = {10, 20, 30};
        std::list<int> lst3(4, 0);
        std::cout << "[list-gen] lst2: "; for (int x: lst2) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30
        std::cout << "[list-gen] lst3: "; for (int x: lst3) std::cout << x << " "; std::cout << "\n";
        // Expected: 0 0 0 0
    }
    {
        std::list<int> lst = {20, 30};
        lst.push_front(10);
        lst.push_back(40);
        std::cout << "[list-ops] after push: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40
        lst.pop_front();
        lst.pop_back();
        std::cout << "[list-ops] after pop: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 20 30
        std::cout << "[list-ops] front=" << lst.front() << " back=" << lst.back() << " size=" << lst.size() << "\n";
        // Expected: 20 30 2
    }
    {
        std::list<int> lst = {10, 20, 30, 40, 50};
        std::cout << "[list-iter] forward: "; for (const auto& x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40 50
        std::cout << "[list-iter] reverse: ";
        for (auto it = lst.rbegin(); it != lst.rend(); ++it) std::cout << *it << " ";
        std::cout << "\n";
        // Expected: 50 40 30 20 10
    }
    {
        std::list<int> lst = {10, 20, 30, 40, 50};
        auto it = lst.begin();
        ++it; --it;
        std::cout << "[list-bidir] after ++-- : " << *it << "\n";
        // Expected: 10
        lst.sort();
        std::cout << "[list-sort] sorted: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40 50
    }
    {
        std::list<int> lst = {10, 30, 40};
        auto it = std::find(lst.begin(), lst.end(), 30);
        lst.insert(it, 20);
        std::cout << "[list-insert] after insert 20 before 30: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40

        std::vector<int> v = {10, 30, 40};
        auto it2 = std::find(v.begin(), v.end(), 30);
        v.insert(it2, 20);
        std::cout << "[vec-insert-compare] after insert 20 before 30: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40
    }
    {
        std::list<int> lst = {10, 20, 30, 20, 40};
        auto it = std::find(lst.begin(), lst.end(), 30);
        auto next = lst.erase(it);
        std::cout << "[list-erase] after erase 30: "; for (int x: lst) std::cout << x << " "; std::cout << " next=" << *next << "\n";
        // Expected: 10 20 20 40, next=20
        lst.remove(20);
        std::cout << "[list-remove] after remove(20): "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 40
        lst.remove_if([](int x){ return x > 15; });
        std::cout << "[list-remove_if] after remove_if(>15): "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10
    }
    {
        std::list<int> lst = {30, 10, 40, 20, 10, 30};
        lst.sort();
        std::cout << "[list-mem] sorted: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 10 20 30 30 40
        lst.unique();
        std::cout << "[list-mem] unique: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30 40
        lst.reverse();
        std::cout << "[list-mem] reversed: "; for (int x: lst) std::cout << x << " "; std::cout << "\n";
        // Expected: 40 30 20 10
    }
    {
        std::list<int> a = {1, 2, 3, 4, 5};
        std::list<int> b = {10, 20, 30};
        auto pos = std::find(a.begin(), a.end(), 3);
        a.splice(pos, b);
        std::cout << "[splice] a after splice(before3, b): "; for (int x: a) std::cout << x << " "; std::cout << "\n";
        // Expected: 1 2 10 20 30 3 4 5
        std::cout << "[splice] b size after splice: " << b.size() << "\n";
        // Expected: 0

        std::list<int> c = {100, 200, 300};
        auto from = std::find(c.begin(), c.end(), 200);
        a.splice(a.begin(), c, from);
        std::cout << "[splice] a after splice single(200): "; for (int x: a) std::cout << x << " "; std::cout << "\n";
        // Expected: 200 1 2 10 20 30 3 4 5
    }

    // ── std::array ──
    {
        std::array<int, 5> a = {1, 2, 3, 4, 5};
        std::cout << "[array] a[0]=" << a[0] << " a.at(2)=" << a.at(2) << " front=" << a.front() << " back=" << a.back() << " size=" << a.size() << "\n";
        // Expected: 1 3 1 5 5
        std::cout << "[array] elements: ";
        for (const auto& x : a) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 1 2 3 4 5

        std::sort(a.begin(), a.end());  // already sorted
        auto it = std::find(a.begin(), a.end(), 3);
        std::cout << "[array] find 3: " << *it << "\n";
        // Expected: 3

        try {
            a.at(10);
        } catch (const std::out_of_range& e) {
            std::cout << "[array] at(10) out_of_range: " << e.what() << "\n";
        }
        std::cout << "[array] size(): " << a.size() << "\n";
        // Expected: 5
    }

    // ── std::deque ──
    {
        std::deque<int> dq = {10, 20, 30};
        dq.push_front(5);
        dq.push_back(40);
        std::cout << "[deque] after push: "; for (int x: dq) std::cout << x << " "; std::cout << "\n";
        // Expected: 5 10 20 30 40
        dq.pop_front();
        dq.pop_back();
        std::cout << "[deque] after pop: "; for (int x: dq) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 20 30
        std::cout << "[deque] dq[1]=" << dq[1] << " front=" << dq.front() << " back=" << dq.back() << "\n";
        // Expected: 20 10 30
    }
    {
        std::vector<int> v = {10, 20, 30};
        v.insert(v.begin(), 5);
        std::cout << "[deque-vs-vec] vec after insert front: "; for (int x: v) std::cout << x << " "; std::cout << "\n";
        // Expected: 5 10 20 30

        std::deque<int> dq = {10, 20, 30};
        dq.push_front(5);
        std::cout << "[deque-vs-vec] deque after push_front: "; for (int x: dq) std::cout << x << " "; std::cout << "\n";
        // Expected: 5 10 20 30
    }

    return 0;
}
