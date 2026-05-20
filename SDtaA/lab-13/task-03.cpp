#include <iostream>
#include <string>
#include <map>

using namespace std;

void updateGrade(map<string, int>& grades, const string& name, int newGrade) {
    grades[name] = newGrade; 
    cout << "Information for student " << name << " updated (Mark: " << newGrade << ").\n";
}

int main() {
    map<string, int> studentGrades = {
        {"Oleksiy", 85},
        {"Maria", 92}
    };

    cout << "Current marks:\n";
    for (const auto& s : studentGrades) cout << s.first << ": " << s.second << endl;

    cout << "\nUpdating Maria`s mark to 98...\n";
    updateGrade(studentGrades, "Maria", 98);

    cout << "Adding new student Ivan with mark 75...\n";
    updateGrade(studentGrades, "Ivan", 75);

    cout << "\nFinal list:\n";
    for (const auto& s : studentGrades) cout << s.first << ": " << s.second << endl;

    return 0;
}