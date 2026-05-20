#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct Car {
    string name;
    int year;
    int mileage;
};

void printList(const list<Car>& cars) {
    if (cars.empty()) {
        cout << "List is empty.\n";
        return;
    }
    cout << "\nCar list:\n";
    for (const auto& car : cars) {
        cout << "Name: " << car.name << " | Year: " << car.year << " | Mileage: " << car.mileage << " км\n";
    }
}

Car inputCar() {
    Car c;
    cout << "Enter name of auto: ";
    cin >> ws;
    getline(cin, c.name);
    cout << "Enter year: ";
    cin >> c.year;
    cout << "Enter mileage (km): ";
    cin >> c.mileage;
    return c;
}

int main() {
    list<Car> cars;
    int choice = 0;

    while (choice != 9) {
        cout << "\n------- MENU FOR WORKING WITH LIST -------\n";
        cout << "1. Enter first element to list\n";
        cout << "2. Insert element at the beginning of list\n";
        cout << "3. Insert element at the end of list\n";
        cout << "4. Insert element after target element\n";
        cout << "5. Insert element before target element\n";
        cout << "6. Search target node\n";
        cout << "7. Delete node with target value\n";
        cout << "8. View list\n";
        cout << "9. Exit\n";
        cout << "Enter operation number: ";
        cin >> choice;

        if (choice == 1) {
            cars.clear();
            cars.push_back(inputCar());
        } else if (choice == 2) {
            cars.push_front(inputCar());
        } else if (choice == 3) {
            cars.push_back(inputCar());
        } else if (choice == 4 || choice == 5) {
            string targetName;
            cout << "Enter auto name: ";
            cin >> ws;
            getline(cin, targetName);

            auto it = find_if(cars.begin(), cars.end(), [&](const Car& c) { return c.name == targetName; });
            
            if (it != cars.end()) {
                Car newCar = inputCar();
                if (choice == 4) {
                    cars.insert(next(it), newCar); // після
                } else {
                    cars.insert(it, newCar); // перед
                }
            } else {
                cout << "Car was not found!\n";
            }
        } else if (choice == 6) {
            string searchName;
            cout << "Enter name to search: ";
            cin >> ws;
            getline(cin, searchName);

            auto it = find_if(cars.begin(), cars.end(), [&](const Car& c) { return c.name == searchName; });
            if (it != cars.end()) cout << "Car named " << searchName << " is in list.\n";
            else cout << "Car named " << searchName << " is not in list.\n";
        } else if (choice == 7) {
            int targetYear;
            cout << "Enter year (older cars will be deleted): ";
            cin >> targetYear;
            
            cars.remove_if([&](const Car& c) { return c.year < targetYear; });
            cout << "Deleting was finished.\n";
        } else if (choice == 8) {
            printList(cars);
        }
    }
    return 0;
}