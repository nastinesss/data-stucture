#include <iostream>
#include <string>
using namespace std;

// task 1
struct List1
{
    int number;
    List1* next;
};

void addFront(List1*& first, int val)
{
    List1* temp = new List1{val,first};
    first = temp;
}

void addBack(List1*& first, int val) {
    List1* temp = new List1{val, nullptr};
    if (!first) {
        first = temp;
        return;
    }
    List1* cur = first;
    while (cur->next) cur = cur->next;
    cur->next = temp;
}

void addMiddle(List1*& first, int val) {
    if (!first) return;
    List1* cur = first;
    int count = 0;
    while (cur) {
        count++;
        cur = cur->next;
    }
    int mid = count / 2;

    cur = first;
    for (int i = 0; i < mid - 1; i++)
        cur = cur->next;

    List1* temp = new List1{val, cur->next};
    cur->next = temp;
}

double average(List1* first) {
    int sum = 0, count = 0;
    while (first) {
        sum += first->number;
        count++;
        first = first->next;
    }
    return sum / count;
}

void deleteFirstEven(List1*& first) {
    if (!first) return;

    if (first->number % 2 == 0) {
        List1* temp = first;
        first = first->next;
        delete temp;
        return;
    }

    List1* cur = first;
    while (cur->next && cur->next->number % 2 != 0)
        cur = cur->next;

    if (cur->next) {
        List1* temp = cur->next;
        cur->next = temp->next;
        delete temp;
    }
}

void freeList(List1*& first) {
    while (first) {
        List1* temp = first;
        first = first->next;
        delete temp;
    }
}

// task 2
struct List2 {
    string city;
    int distance;
    List2* next;
};

void addCity(List2*& first, string city, int dist) {
    List2* temp = new List2{city, dist, first};
    first = temp;
}

void printTwoFarthest(List2* first) {
    List2 *max1 = nullptr, *max2 = nullptr;

    while (first) {
        if (!max1 || first->distance > max1->distance) {
            max2 = max1;
            max1 = first;
        } else if (!max2 || first->distance > max2->distance) {
            max2 = first;
        }
        first = first->next;
    }

    if (max1) cout << "1: " << max1->city << endl;
    if (max2) cout << "2: " << max2->city << endl;
}

void freeList2(List2*& first) {
    while (first) {
        List2* temp = first;
        first = first->next;
        delete temp;
    }
}

// task 3
struct List3 {
    string car;
    int year;
    double price;
    List3* next;
};

void addCar(List3*& first, string car, int year, double price) {
    List3* temp = new List3{car, year, price, first};
    first = temp;
}

void printCars(List3* first) {
    int currentYear = 2026;

    while (first) {
        if ((currentYear - first->year > 10) && (first->price < 5000)) {
            cout << first->car << " | " << first->year << " | " << first->price << endl;
        }
        first = first->next;
    }
}

void freeList3(List3*& first) {
    while (first) {
        List3* temp = first;
        first = first->next;
        delete temp;
    }
}

int main() {

    // task 1
    List1* list1 = nullptr;

    addFront(list1, 5);
    addBack(list1, 10);
    addMiddle(list1, 7);
    addBack(list1, 8);

    cout << "Average: " << average(list1) << endl;

    deleteFirstEven(list1);

    freeList(list1);

    //task 2
    List2* list2 = nullptr;

    addCity(list2, "Lviv", 540);
    addCity(list2, "Kharkiv", 480);
    addCity(list2, "Odesa", 470);

    printTwoFarthest(list2);

    addCity(list2, "Berlin", 1200);

    freeList2(list2);

    // task 3
    List3* list3 = nullptr;

    addCar(list3, "BMW", 2005, 4500);
    addCar(list3, "Audi", 2018, 7000);
    addCar(list3, "Opel", 2008, 3000);

    cout << "\nCars:\n";
    printCars(list3);

    freeList3(list3);

    return 0;
}