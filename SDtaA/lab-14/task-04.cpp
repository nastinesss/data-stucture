#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    multimap<int, string> wordGroups;
    string word;

    cout << "Enter words (enter 'END' to end enter):\n";
    while (cin >> word && word != "END") {
        wordGroups.insert({word.length(), word});
    }

    cout << "\n--- Grouped words by length ---\n";

    for (auto it = wordGroups.begin(); it != wordGroups.end(); ) {
        int length = it->first;
        int count = wordGroups.count(length);

        cout << "\nLength " << length << " (Number of words: " << count << "):\n";

        auto range = wordGroups.equal_range(length);
        for (auto i = range.first; i != range.second; ++i) {
            cout << " - " << i->second << "\n";
        }

        it = range.second;
    }

    return 0;
}