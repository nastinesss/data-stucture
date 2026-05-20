#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    map<string, string> phoneBook;
    int choice;

    do {
        cout << "\n--- Telephone directory ---\n";
        cout << "1. Add record\n";
        cout << "2. Search number by name\n";
        cout << "3. Delete record\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, number;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter number: ";
            cin >> number;
            phoneBook[name] = number;
            cout << "Record added!\n";
        } 
        else if (choice == 2) {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            auto it = phoneBook.find(name);
            if (it != phoneBook.end()) {
                cout << "Number " << name << ": " << it->second << endl;
            } else {
                cout << "Record was not found.\n";
            }
        } 
        else if (choice == 3) {
            string name;
            cout << "Enter name to delete: ";
            cin >> name;
            if (phoneBook.erase(name)) {
                cout << "Record deleted.\n";
            } else {
                cout << "Record was not found.\n";
            }
        }
    } while (choice != 4);

    return 0;
}