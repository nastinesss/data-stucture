#include <iostream>
#include <string>

using namespace std;

struct Student {
    string lastName;
    double exam1;
    double exam2;
    double exam3;
    double average;
};

struct Product {
    string name;
    double protein;
    double fat;
    double carb;
    double calories;
};

void calculateAverages(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i].average = (arr[i].exam1 + arr[i].exam2 + arr[i].exam3) / 3.0;
    }
}

void findMaxAverages(Student arr[], int n) {
    double maxAvg = arr[0].average;
    for (int i = 1; i < n; i++) {
        if (arr[i].average > maxAvg) {
            maxAvg = arr[i].average;
        }
    }

    int countMaxAvg = 0;
    cout << "Max average indices: ";
    for (int i = 0; i < n; i++) {
        if (arr[i].average == maxAvg) {
            countMaxAvg++;
            cout << i << " ";
        }
    }
    cout << "\nCount: " << countMaxAvg << "\n";
}

void sortStudents(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].average > arr[j + 1].average) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void binarySearchStudents(Student arr[], int n, double targetAvg) {
    int left = 0;
    int right = n - 1;
    bool foundAvg = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].average == targetAvg) {
            foundAvg = true;
            int temp = mid;
            while (temp >= 0 && arr[temp].average == targetAvg) {
                cout << arr[temp].lastName << " ";
                temp--;
            }
            temp = mid + 1;
            while (temp < n && arr[temp].average == targetAvg) {
                cout << arr[temp].lastName << " ";
                temp++;
            }
            cout << "\n";
            break;
        }
        if (arr[mid].average < targetAvg) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!foundAvg) {
        cout << "Not found\n";
    }
}

void calculateCalories(Product arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i].calories = 4 * arr[i].protein + 9 * arr[i].fat + 4 * arr[i].carb;
    }
}

void findMaxCalories(Product arr[], int n) {
    double maxCal = arr[0].calories;
    for (int i = 1; i < n; i++) {
        if (arr[i].calories > maxCal) {
            maxCal = arr[i].calories;
        }
    }

    int countMaxCal = 0;
    cout << "Max calories indices: ";
    for (int i = 0; i < n; i++) {
        if (arr[i].calories == maxCal) {
            countMaxCal++;
            cout << i << " ";
        }
    }
    cout << "\nCount: " << countMaxCal << "\n";
}

void findCaloriesInRange(Product arr[], int n, double A, double B) {
    bool foundRange = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].calories >= A && arr[i].calories <= B) {
            cout << arr[i].name << " ";
            foundRange = true;
        }
    }
    cout << "\n";

    if (!foundRange) {
        cout << "Not found\n";
    }
}

int main() {
    const int n1 = 4;
    Student students[n1] = {
        {"Oleg", 90.0, 85.0, 92.0, 0.0},
        {"Petro", 95.0, 95.0, 95.0, 0.0},
        {"Ivan", 70.0, 75.0, 80.0, 0.0},
        {"Oksana", 95.0, 95.0, 95.0, 0.0}
    };

    calculateAverages(students, n1);
    findMaxAverages(students, n1);
    sortStudents(students, n1);

    double targetAvg = 95.0;
    cout << "Target average search: " << targetAvg << "\n";
    binarySearchStudents(students, n1, targetAvg);

    const int n2 = 3;
    Product products[n2] = {
        {"Apple", 0.3, 0.2, 14.0, 0.0},
        {"Chicken", 31.0, 3.6, 0.0, 0.0},
        {"Bread", 9.0, 3.0, 49.0, 0.0}
    };

    calculateCalories(products, n2);
    findMaxCalories(products, n2);

    double rangeA = 50.0;
    double rangeB = 200.0;
    cout << "Calories in range [" << rangeA << "; " << rangeB << "]: ";
    findCaloriesInRange(products, n2, rangeA, rangeB);

    return 0;
}