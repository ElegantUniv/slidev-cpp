// test_associative.cpp — verifies stl-associative.md code blocks
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

int main() {
    std::cout << "=== stl-associative.md ===\n";

    // ── std::set ──
    {
        std::set<int> s;
        s.insert(30);
        s.insert(10);
        s.insert(20);
        s.insert(10);  // duplicate, ignored
        std::cout << "[set] elements: ";
        for (int x : s) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 10 20 30
        std::cout << "[set] size=" << s.size() << " empty=" << s.empty() << "\n";
        // Expected: 3 0
    }
    {
        std::set<int> s = {10, 20, 30, 40, 50};
        auto it = s.find(30);
        if (it != s.end()) std::cout << "[set-find] found: " << *it << "\n";
        // Expected: 30
        std::cout << "[set-find] count(30)=" << s.count(30) << "\n";
        // Expected: 1

        s.erase(20);
        std::cout << "[set-erase] after erase(20): ";
        for (int x : s) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 30 40 50

        // erase range [find(30), find(50)) — erases 30, 40
        s.erase(s.find(30), s.find(50));
        std::cout << "[set-erase] after erase [30,50): ";
        for (int x : s) std::cout << x << " "; std::cout << "\n";
        // Expected: 10 50
    }

    // ── std::map 생성과 삽입 ──
    {
        std::map<std::string, int> m1;
        std::map<std::string, int> score = {
            {"Alice", 95},
            {"Bob",   88},
            {"Carol", 72}
        };
        std::cout << "[map-gen] score[Alice]=" << score["Alice"] << "\n";
        // Expected: 95
    }
    {
        std::map<std::string, int> m;
        m.insert({"Dave", 85});
        std::cout << "[map-insert] Dave=" << m["Dave"] << "\n";
        // Expected: 85

        auto [it, ok] = m.insert({"Dave", 99});
        std::cout << "[map-insert] re-insert Dave: ok=" << ok << " val=" << it->second << "\n";
        // Expected: ok=0 val=85 (not overwritten)
    }
    {
        std::map<std::string, int> m;
        m.emplace("Alice", 95);
        std::cout << "[map-emplace] Alice=" << m["Alice"] << "\n";
        // Expected: 95

        m.try_emplace("Alice", 0);   // already exists, ignored
        std::cout << "[map-try_emplace] Alice after try(0)=" << m["Alice"] << "\n";
        // Expected: 95 (unchanged)

        m.try_emplace("Bob", 88);    // new key
        std::cout << "[map-try_emplace] Bob=" << m["Bob"] << "\n";
        // Expected: 88

        m.insert_or_assign("Alice", 100);  // overwrites
        std::cout << "[map-insert_or_assign] Alice after assign(100)=" << m["Alice"] << "\n";
        // Expected: 100
    }

    // ── std::map [] 연산자 ──
    {
        std::map<std::string, int> m;
        m["Alice"] = 95;
        m["Bob"]   = 88;
        std::cout << "[map-bracket] Alice=" << m["Alice"] << "\n";
        // Expected: 95
        m["Alice"] = 100;
        std::cout << "[map-bracket] Alice after update=" << m["Alice"] << "\n";
        // Expected: 100
    }
    {
        std::map<std::string, int> m;
        m["Alice"] = 95;
        std::cout << "[map-trap] Nobody=" << m["Nobody"] << "\n";
        // Expected: 0 (auto-inserted)
        std::cout << "[map-trap] size after Nobody=" << m.size() << "\n";
        // Expected: 2 (Alice + Nobody)
    }
    {
        std::map<std::string, int> m = {{"Alice", 95}, {"Bob", 88}};
        std::cout << "[map-at] Alice=" << m.at("Alice") << "\n";
        // Expected: 95
        try {
            m.at("Nobody");
        } catch (const std::out_of_range&) {
            std::cout << "[map-at] Nobody throws out_of_range: OK\n";
        }
        auto it = m.find("Bob");
        if (it != m.end()) std::cout << "[map-find] Bob=" << it->second << "\n";
        // Expected: 88
    }

    // ── std::map 검색·범위 조회 ──
    {
        std::map<std::string, int> score = {
            {"Alice", 95}, {"Bob", 88},
            {"Carol", 72}, {"Dave", 85}
        };
        auto it = score.find("Bob");
        if (it != score.end()) {
            std::cout << "[map-find] " << it->first << "=" << it->second << "\n";
            // Expected: Bob=88
            it->second = 90;
            std::cout << "[map-find] Bob after modify=" << score["Bob"] << "\n";
            // Expected: 90
        }
        std::cout << "[map-count] Alice=" << score.count("Alice") << " Nobody=" << score.count("Nobody") << "\n";
        // Expected: 1 0
    }
    {
        std::map<int, std::string> m = {{10,"A"},{20,"B"},{30,"C"},{40,"D"}};
        auto lb = m.lower_bound(20);
        std::cout << "[lb/ub] lower_bound(20)=" << lb->first << "," << lb->second << "\n";
        // Expected: 20,B
        auto ub = m.upper_bound(30);
        std::cout << "[lb/ub] upper_bound(30)=" << ub->first << "," << ub->second << "\n";
        // Expected: 40,D
        std::cout << "[lb/ub] range [20,30]: ";
        for (auto i = m.lower_bound(20); i != m.upper_bound(30); ++i)
            std::cout << i->first << " ";
        std::cout << "\n";
        // Expected: 20 30
    }

    // ── std::map 이터레이터와 순회 ──
    {
        std::map<std::string, int> score = {
            {"Alice", 95}, {"Bob", 88}, {"Carol", 72}
        };
        std::cout << "[map-iter] forward:\n";
        for (auto it = score.begin(); it != score.end(); ++it)
            std::cout << "  " << it->first << ": " << it->second << "\n";
        // Expected: Alice:95, Bob:88, Carol:72

        std::cout << "[map-iter] reverse keys: ";
        for (auto it = score.rbegin(); it != score.rend(); ++it)
            std::cout << it->first << " ";
        std::cout << "\n";
        // Expected: Carol Bob Alice
    }
    {
        std::map<std::string, int> score = {
            {"Alice", 95}, {"Bob", 88}, {"Carol", 72}
        };
        std::cout << "[map-structured] C++17 bindings:\n";
        for (const auto& [name, s] : score)
            std::cout << "  " << name << ": " << s << "\n";

        for (auto& [name, s] : score) s += 5;
        std::cout << "[map-structured] after +5: Alice=" << score["Alice"] << "\n";
        // Expected: 100
    }

    // ── std::map 삭제와 활용 패턴 ──
    {
        std::map<std::string, int> m = {{"Alice",95},{"Bob",88},{"Carol",72}};
        m.erase("Bob");
        std::cout << "[map-erase] after erase(Bob): ";
        for (const auto& [k,v]: m) std::cout << k << " ";
        std::cout << "\n";
        // Expected: Alice Carol

        auto it = m.find("Carol");
        if (it != m.end()) m.erase(it);
        std::cout << "[map-erase] after erase Carol by it: ";
        for (const auto& [k,v]: m) std::cout << k << " ";
        std::cout << "\n";
        // Expected: Alice

        m.erase(m.begin(), m.end());
        std::cout << "[map-erase] after clear: size=" << m.size() << "\n";
        // Expected: 0
    }
    {
        std::vector<std::string> words = {
            "apple", "banana", "apple",
            "cherry", "banana", "apple"
        };
        std::map<std::string, int> freq;
        for (const auto& w : words) freq[w]++;
        std::cout << "[freq] counts:\n";
        for (const auto& [word, cnt] : freq)
            std::cout << "  " << word << ": " << cnt << "\n";
        // Expected: apple:3, banana:2, cherry:1

        auto max_it = std::max_element(freq.begin(), freq.end(),
            [](const auto& a, const auto& b){ return a.second < b.second; });
        std::cout << "[freq] most frequent: " << max_it->first << "\n";
        // Expected: apple
    }

    // ── std::multiset ──
    {
        std::multiset<int> ms = {10, 20, 10, 20, 20};
        std::cout << "[multiset] elements: ";
        for (int x : ms) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 10 10 20 20 20
        std::cout << "[multiset] count(20)=" << ms.count(20) << "\n";
        // Expected: 3

        auto it = ms.find(20);
        ms.erase(it);  // erase one 20
        std::cout << "[multiset] after erase one 20: ";
        for (int x : ms) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 10 10 20 20

        ms.erase(10);  // erase all 10s
        std::cout << "[multiset] after erase all 10s: ";
        for (int x : ms) std::cout << x << " ";
        std::cout << "\n";
        // Expected: 20 20
    }

    // ── std::multimap ──
    {
        std::multimap<std::string, int> scores;
        scores.insert({"Alice", 90});
        scores.insert({"Alice", 85});
        scores.insert({"Bob",   88});

        auto [lo, hi] = scores.equal_range("Alice");
        std::cout << "[multimap] Alice scores: ";
        for (auto it = lo; it != hi; ++it) std::cout << it->second << " ";
        std::cout << "\n";
        // Expected: 90 85 (insertion order)
        std::cout << "[multimap] count(Alice)=" << scores.count("Alice") << "\n";
        // Expected: 2
    }

    return 0;
}
