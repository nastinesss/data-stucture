#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    string fullName;
    string group;
    double averageScore;
};

void printStudents(const vector<Student>& students) {
    for (const auto& s : students) {
        cout << "PIB: " << s.fullName << " | Group: " << s.group << " | Mark: " << s.averageScore << "\n";
    }
}

int main() {
    vector<Student> students = {
        {"Ivanov I.I.", "144", 85.5},
        {"Petrenko P.P", "117", 90.0},
        {"Kovalenko K.K.", "122", 78.0}
    };

    students.push_back({"Sydorenko S.S.", "110", 92.5});

    string nameToRemove = "Kovalenko K.K.";
    students.erase(remove_if(students.begin(), students.end(), [&](const Student& s){
        return s.fullName == nameToRemove;
    }), students.end());

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.averageScore > b.averageScore;
    });

    cout << "--- Sorted list by average mark ---\n";
    printStudents(students);

    string targetGroup = "144";
    cout << "\n--- Group student " << targetGroup << " ---\n";
    for (const auto& s : students) {
        if (s.group == targetGroup) cout << s.fullName << "\n";
    }

    double targetScore = 88.0;
    cout << "\n--- Students with mark above " << targetScore << " ---\n";
    for (const auto& s : students) {
        if (s.averageScore > targetScore) cout << s.fullName << " (" << s.averageScore << ")\n";
    }

    return 0;
}