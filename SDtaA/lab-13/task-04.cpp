#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    multimap<char, string> wordGroups;
    string word;

    cout << "Enter word list (enter 'END' to end): \n";
    while (cin >> word && word != "END") {
        char firstLetter = tolower(word[0]);
        wordGroups.insert({firstLetter, word});
    }

    cout << "\nGrouped words:\n";
    char currentLetter = '\0';
    
    for (const auto& pair : wordGroups) {
        if (pair.first != currentLetter) {
            currentLetter = pair.first;
            cout << "\n[" << (char)toupper(currentLetter) << "]:\n";
        }
        cout << " - " << pair.second << endl;
    }

    return 0;
}