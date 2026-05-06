#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void gnomeSort(int arr[], int n) {
    int index = 0;
    while (index < n) {
        if (index == 0) {
            index++;
        }
        if (arr[index] >= arr[index - 1]) {
            index++;
        } else {
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

double measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    int* tempArr = new int[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[i];
    }

    auto start = high_resolution_clock::now();
    sortFunc(tempArr, n);
    auto stop = high_resolution_clock::now();

    delete[] tempArr;
    duration<double, std::milli> timeSpan = stop - start;
    return timeSpan.count();
}

struct Time {
    int hours;
    int minutes;
};

struct Train {
    string number;
    string destination;
    float distance;
    Time departure;
    Time arrival;
    int travelTimeMinutes;
};

struct TV {
    string manufacturer;
    int screenSize;
    float price;
};

void calculateTravelTimes(Train arr[], int n) {
    for (int i = 0; i < n; i++) {
        int depTime = arr[i].departure.hours * 60 + arr[i].departure.minutes;
        int arrTime = arr[i].arrival.hours * 60 + arr[i].arrival.minutes;
        arr[i].travelTimeMinutes = arrTime - depTime;
        if (arr[i].travelTimeMinutes < 0) {
            arr[i].travelTimeMinutes += 24 * 60;
        }
    }
}

void findLongestTravelTimeManual(Train arr[], int n) {
    int maxTimeIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].travelTimeMinutes > arr[maxTimeIdx].travelTimeMinutes) {
            maxTimeIdx = i;
        }
    }
    cout << "Longest travel time train (manual search):\n";
    cout << "Number: " << arr[maxTimeIdx].number << ", Destination: " << arr[maxTimeIdx].destination << "\n";
}

void selectionSortTrains(Train arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].travelTimeMinutes > arr[max_idx].travelTimeMinutes) {
                max_idx = j;
            }
        }
        Train temp = arr[max_idx];
        arr[max_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSortTVs(TV arr[], int n) {
    for (int i = 1; i < n; i++) {
        TV key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].screenSize > key.screenSize) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void gnomeSortTVsDesc(TV arr[], int left, int right) {
    int index = left + 1;
    while (index <= right) {
        if (index == left || arr[index].price <= arr[index - 1].price) {
            index++;
        } else {
            TV temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

void sortTVs(TV arr[], int n) {
    insertionSortTVs(arr, n);
    int startIdx = 0;
    for (int i = 1; i <= n; i++) {
        if (i == n || arr[i].screenSize != arr[i - 1].screenSize) {
            gnomeSortTVsDesc(arr, startIdx, i - 1);
            startIdx = i;
        }
    }
}

int main() {
    srand(12345);
    int sizes[] = {1000, 10000, 100000};

    cout << "Algorithm Time Analysis (ms):\n";
    cout << left << setw(20) << "Algorithm" << setw(15) << "n=1000" << setw(15) << "n=10000" << setw(15) << "n=100000" << "\n";

    double times[4][3];
    string algoNames[] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Gnome Sort"};
    void (*funcs[])(int[], int) = {bubbleSort, insertionSort, selectionSort, gnomeSort};

    for (int j = 0; j < 3; j++) {
        int n = sizes[j];
        int* randomArray = new int[n];
        for (int i = 0; i < n; i++) {
            randomArray[i] = rand() % 10000;
        }
        for (int k = 0; k < 4; k++) {
            times[k][j] = measureTime(funcs[k], randomArray, n);
        }
        delete[] randomArray;
    }

    for (int i = 0; i < 4; i++) {
        cout << left << setw(20) << algoNames[i];
        for (int j = 0; j < 3; j++) {
            cout << setw(15) << times[i][j];
        }
        cout << "\n";
    }

    cout << "\n";

    const int numTrains = 3;
    Train trains[numTrains] = {
        {"101A", "Kyiv", 500.0, {10, 30}, {18, 45}, 0},
        {"202B", "Lviv", 600.0, {22, 0}, {6, 30}, 0},
        {"303C", "Odesa", 450.0, {8, 15}, {14, 0}, 0}
    };

    calculateTravelTimes(trains, numTrains);
    findLongestTravelTimeManual(trains, numTrains);

    selectionSortTrains(trains, numTrains);
    cout << "Longest travel time train (selection sort top):\n";
    cout << "Number: " << trains[0].number << ", Destination: " << trains[0].destination << ", Time: " << trains[0].travelTimeMinutes << " min\n";

    const int numTVs = 5;
    TV tvs[numTVs] = {
        {"Samsung", 45, 15000.0},
        {"LG", 32, 8000.0},
        {"Sony", 60, 25000.0},
        {"Philips", 45, 12000.0},
        {"Panasonic", 32, 8500.0}
    };

    sortTVs(tvs, numTVs);

    cout << "\nSorted TVs:\n";
    for (int i = 0; i < numTVs; i++) {
        cout << tvs[i].manufacturer << " | " << tvs[i].screenSize << "\" | " << tvs[i].price << " UAH\n";
    }

    return 0;
}