#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

string cleanWord(const string& word) {
    string cleaned;
    for (char c : word) {
        if (isalpha(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

int main() {
    map<string, int> wordCount;
    string text;

    cout << "Enter text (enter 'END' from new line to end): \n";

    string word;
    while (cin >> word && word != "END") {
        string cWord = cleanWord(word);
        if (!cWord.empty()) {
            wordCount[cWord]++;
        }
    }

    cout << "\nResult (alphabet order):\n";
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}