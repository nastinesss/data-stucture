#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    string text;
    cout << "Enter line: ";
    getline(cin, text);

    map<char, int> charCounts;

    for (char c : text) {
        charCounts[c]++;
    }

    cout << "\nSymbols and their numbers:\n";
    char mostFrequentChar = '\0';
    int maxCount = 0;

    for (const auto& pair : charCounts) {
        cout << "'" << pair.first << "' : " << pair.second << endl;

        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentChar = pair.first;
        }
    }

    if (maxCount > 0) {
        cout << "\nSymbol occurs more often '" << mostFrequentChar
             << "' (" << maxCount << " times)." << endl;
    }

    return 0;
}