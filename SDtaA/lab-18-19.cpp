#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cctype>

using namespace std;

string readInput(bool fromFile, const string& filepath = "") {
    if (fromFile) {
        ifstream file(filepath);
        if (!file.is_open()) return "";
        string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        return str;
    }
    string input;
    cin.ignore();
    getline(cin, input);
    return input;
}

void writeOutput(const string& text, bool toFile, const string& filepath = "") {
    if (toFile) {
        ofstream file(filepath);
        if (file.is_open()) {
            file << text;
        }
    } else {
        cout << text << endl;
    }
}

string caesarCipher(string text, int shift, bool encrypt) {
    if (!encrypt) shift = -shift;
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shifted = (c - base + shift) % 26;
            if (shifted < 0) shifted += 26;
            result += (base + shifted);
        } else {
            result += c;
        }
    }
    return result;
}

string vigenereCipher(string text, string key, bool encrypt) {
    string result = "";
    int keyIndex = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char keyBase = isupper(key[keyIndex]) ? 'A' : 'a';
            int shift = key[keyIndex] - keyBase;
            if (!encrypt) shift = -shift;
            int shifted = (c - base + shift) % 26;
            if (shifted < 0) shifted += 26;
            result += (base + shifted);
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += c;
        }
    }
    return result;
}

void printVigenereTable() {
    cout << "  ";
    for (char c = 'A'; c <= 'Z'; ++c) cout << c << " ";
    cout << endl;
    for (char i = 'A'; i <= 'Z'; ++i) {
        cout << i << " ";
        for (char j = 'A'; j <= 'Z'; ++j) {
            char c = (i - 'A' + j - 'A') % 26 + 'A';
            cout << c << " ";
        }
        cout << endl;
    }
}

string polybiusSquare(string text, bool encrypt) {
    char square[5][5] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'K'},
        {'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U'},
        {'V', 'W', 'X', 'Y', 'Z'}
    };
    string result = "";
    if (encrypt) {
        for (char c : text) {
            if (isalpha(c)) {
                c = toupper(c);
                if (c == 'J') c = 'I';
                for (int r = 0; r < 5; ++r) {
                    for (int col = 0; col < 5; ++col) {
                        if (square[r][col] == c) {
                            result += to_string(r + 1) + to_string(col + 1) + " ";
                        }
                    }
                }
            }
        }
    } else {
        for (size_t i = 0; i < text.length(); i += 3) {
            if (i + 1 < text.length() && isdigit(text[i]) && isdigit(text[i+1])) {
                int r = text[i] - '1';
                int col = text[i+1] - '1';
                if (r >= 0 && r < 5 && col >= 0 && col < 5) {
                    result += square[r][col];
                }
            }
        }
    }
    return result;
}

void getMorseMaps(map<char, string>& mToS, map<string, char>& sToM) {
    mToS['A'] = ".-";    mToS['B'] = "-...";  mToS['C'] = "-.-.";  mToS['D'] = "-..";
    mToS['E'] = ".";     mToS['F'] = "..-.";  mToS['G'] = "--.";   mToS['H'] = "....";
    mToS['I'] = "..";    mToS['J'] = ".---";  mToS['K'] = "-.-";   mToS['L'] = ".-..";
    mToS['M'] = "--";    mToS['N'] = "-.";    mToS['O'] = "---";   mToS['P'] = ".--.";
    mToS['Q'] = "--.-";  mToS['R'] = ".-.";   mToS['S'] = "...";   mToS['T'] = "-";
    mToS['U'] = "..-";   mToS['V'] = "...-";  mToS['W'] = ".--";   mToS['X'] = "-..-";
    mToS['Y'] = "-.--";  mToS['Z'] = "--..";  mToS[' '] = "/";
    for (auto const& [key, val] : mToS) {
        sToM[val] = key;
    }
}

string morseCipher(string text, bool encrypt) {
    map<char, string> morseToCode;
    map<string, char> codeToMorse;
    getMorseMaps(morseToCode, codeToMorse);
    string result = "";
    if (encrypt) {
        for (char c : text) {
            c = toupper(c);
            if (morseToCode.find(c) != morseToCode.end()) {
                result += morseToCode[c] + " ";
            }
        }
    } else {
        string current = "";
        for (char c : text) {
            if (c == ' ' || c == '\n') {
                if (!current.empty()) {
                    if (codeToMorse.find(current) != codeToMorse.end()) {
                        result += codeToMorse[current];
                    }
                    current = "";
                }
            } else {
                current += c;
            }
        }
        if (!current.empty() && codeToMorse.find(current) != codeToMorse.end()) {
            result += codeToMorse[current];
        }
    }
    return result;
}

int main() {
    int choice;
    cout << "Select Cipher:\n1. Caesar\n2. Vigenere\n3. Polybius\n4. Morse\nEnter choice: ";
    cin >> choice;

    bool encrypt;
    cout << "1. Encrypt\n2. Decrypt\nEnter choice: ";
    int mode;
    cin >> mode;
    encrypt = (mode == 1);

    int inputSource;
    cout << "1. Keyboard\n2. File\nEnter choice: ";
    cin >> inputSource;
    
    string text = "";
    if (inputSource == 2) {
        string path;
        cout << "Enter file path: ";
        cin >> path;
        text = readInput(true, path);
    } else {
        cout << "Enter text: ";
        text = readInput(false);
    }

    string output = "";
    if (choice == 1) {
        int shift;
        cout << "Enter shift: ";
        cin >> shift;
        output = caesarCipher(text, shift, encrypt);
    } else if (choice == 2) {
        string key;
        cout << "Enter key word: ";
        cin >> key;
        printVigenereTable();
        output = vigenereCipher(text, key, encrypt);
    } else if (choice == 3) {
        output = polybiusSquare(text, encrypt);
    } else if (choice == 4) {
        output = morseCipher(text, encrypt);
    }

    int outputTarget;
    cout << "1. Screen\n2. File\nEnter choice: ";
    cin >> outputTarget;

    if (outputTarget == 2) {
        string path;
        cout << "Enter output file path: ";
        cin >> path;
        writeOutput(output, true, path);
    } else {
        cout << "Result: " << endl;
        writeOutput(output, false);
    }

    return 0;
}