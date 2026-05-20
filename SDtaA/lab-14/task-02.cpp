#include <iostream>
#include <string>
#include <map>

using namespace std;

void printWarehouse(const map<string, int>& warehouse) {
    cout << "\n--- Warehouse (Alphabet order) ---\n";
    if (warehouse.empty()) {
        cout << "Warehouse is empty.\n";
        return;
    }
    for (const auto& item : warehouse) {
        cout << "Item: " << item.first << " | Number: " << item.second << " pcs.\n";
    }
    cout << "----------------------------------\n";
}

int main() {
    map<string, int> warehouse;
    int choice;

    do {
        cout << "\n1. Add item / Change number\n";
        cout << "2. Delete item\n";
        cout << "3. Search item\n";
        cout << "4. Show all list\n";
        cout << "5. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int quantity;
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter number: ";
            cin >> quantity;
            warehouse[name] = quantity;
            cout << "Information saved!\n";
        }
        else if (choice == 2) {
            string name;
            cout << "Enter item name to delete: ";
            cin >> name;
            if (warehouse.erase(name)) cout << "Item deleted.\n";
            else cout << "Item was not found.\n";
        }
        else if (choice == 3) {
            string name;
            cout << "Enter item name to search: ";
            cin >> name;
            auto it = warehouse.find(name);
            if (it != warehouse.end()) cout << "Available: " << it->second << " pcs.\n";
            else cout << "Item was not found.\n";
        }
        else if (choice == 4) {
            printWarehouse(warehouse);
        }
    } while (choice != 5);

    return 0;
}