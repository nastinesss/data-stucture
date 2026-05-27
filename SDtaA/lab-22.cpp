#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <list>
#include <random>
#include <ctime>
#include <queue>

bool isVowel(char ch) {
    ch = std::tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y');
}

int countUnique(std::list<int> l) {
    l.sort();
    l.unique();
    return l.size();
}

struct Request {
    int priority;
    std::string category;
    std::string text;

    bool operator<(const Request& other) const {
        return priority < other.priority;
    }
};

int main() {
    {
        std::ifstream file("numbers.txt");
        if (file.is_open()) {
            std::vector<int> all_numbers;
            int num;
            while (file >> num) {
                all_numbers.push_back(num);
            }
            file.close();

            size_t n;
            std::cin >> n;
            if (n > all_numbers.size()) n = all_numbers.size();

            std::vector<int> vec(all_numbers.begin(), all_numbers.begin() + n);

            size_t third = vec.size() / 3;
            std::sort(vec.begin(), vec.begin() + third, std::greater<int>());
            std::sort(vec.begin() + 2 * third, vec.end());

            auto it_unique = std::unique(vec.begin(), vec.end());
            vec.erase(it_unique, vec.end());

            std::stable_partition(vec.begin(), vec.end(), [](int x) { return x > 10; });

            std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return x + 100; });

            if (!vec.empty()) {
                int max_val = *std::max_element(vec.begin(), vec.end());
                int min_val = *std::min_element(vec.begin(), vec.end());
                std::transform(vec.begin(), vec.end(), vec.begin(), [max_val, min_val](int x) {
                    if (x > 100) return max_val;
                    if (x < -100) return min_val;
                    return x;
                });
            }

            auto it_remove = std::remove_if(vec.begin(), vec.end(), [](int x) { return x >= -5 && x <= 5; });
            vec.erase(it_remove, vec.end());
        }
    }

    {
        std::ifstream file("names.txt");
        if (file.is_open()) {
            std::vector<std::string> vec;
            std::string word;
            while (file >> word) {
                vec.push_back(word);
            }
            file.close();

            std::string search_name;
            std::cin >> search_name;
            auto count = std::count(vec.begin(), vec.end(), search_name);
            std::cout << count << std::endl;

            for (auto& s : vec) {
                std::transform(s.begin(), s.end(), s.begin(), ::toupper);
            }
            for (auto& s : vec) {
                std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            }

            std::stable_partition(vec.begin(), vec.end(), [](const std::string& s) {
                return !s.empty() && isVowel(s[0]);
            });
        }
    }

    {
        std::list<int> list1;
        for (int i = 0; i < 10; ++i) {
            int val;
            std::cin >> val;
            list1.push_back(val);
        }

        for (auto it = list1.begin(); it != list1.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        std::list<int> list2;
        std::mt19937 gen(std::time(nullptr));
        std::uniform_int_distribution<> dis(1, 100);
        for (int i = 0; i < 10; ++i) {
            list2.push_back(dis(gen));
        }
        list2.sort();

        list1.sort();
        std::list<int> merged;
        std::merge(list1.begin(), list1.end(), list2.begin(), list2.end(), std::back_inserter(merged));
        merged.sort(std::greater<int>());

        int unique_count = countUnique(list1);
        std::cout << unique_count << std::endl;
    }

    {
        std::priority_queue<Request> pq;

        pq.push({3, "high", "Server error"});
        pq.push({1, "low", "Password reset request"});
        pq.push({2, "medium", "UI bug"});

        while (!pq.empty()) {
            Request current = pq.top();
            pq.pop();
            std::cout << current.category << ": " << current.text << std::endl;
        }
    }

    return 0;
}