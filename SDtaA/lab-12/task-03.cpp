#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Order {
    int id;
    string clientSurname;
    string address;
    double price;
    bool isUrgent;
    string timeCreated;
    string status;
};

void printOrder(const Order& o) {
    cout << "ID: " << setw(4) << o.id 
         << " | Client: " << setw(10) << o.clientSurname
         << " | Price: " << setw(6) << o.price
         << " | Priority: " << (o.isUrgent ? "Urgent" : "Normal")
         << " | Status: " << o.status << endl;
}

void printAllOrders(const deque<Order>& orders) {
    cout << "\n--- Order list ---\n";
    for (const auto& o : orders) printOrder(o);
    cout << "------------------------\n";
}

int main() {
    deque<Order> orders;

    Order o1 = {1, "Ivanov", "str. Holovna 10", 350.0, false, "10:00", "Waiting"};
    orders.push_back(o1);
    
    Order o2 = {2, "Petrenko", "str. Franka 5", 800.0, true, "10:15", "Waiting"};
    orders.push_front(o2);

    Order o3 = {3, "Kovalenko", "str. Sadova 1", 150.0, false, "10:30", "Completed"};
    orders.push_back(o3);

    Order o4 = {4, "Sydorenko", "str. Myru 12", 500.0, true, "10:45", "Canceled"};
    orders.push_front(o4);

    printAllOrders(orders);

    orders.erase(remove_if(orders.begin(), orders.end(), [](const Order& o) {
        return o.status == "Completed" || o.status == "Canceled";
    }), orders.end());

    cout << "\nAfter deleting completed/canceled:";
    printAllOrders(orders);

    int searchId = 2;
    auto it = find_if(orders.begin(), orders.end(), [&](const Order& o) { return o.id == searchId; });
    if (it != orders.end()) {
        it->status = "Completed";
        cout << "\nOrder status ID " << searchId << " changed to 'Completed'.\n";
    }

    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return a.price < b.price;
    });
    
    cout << "\nAfter sorting by price:";
    printAllOrders(orders);

    return 0;
}