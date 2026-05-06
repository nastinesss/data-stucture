#include <iostream>
#include <string>
using namespace std;
struct Student {
    string name;
    int group;
    int grades[4];
    double avg;
};

void calculateAvg(Student arr[], int n) {
    for (int i=0; i<n; i++) {
        double sum=0;
        for (int j=0; j<4; j++) {
            sum+=arr[i].grades[j];
        }
        arr[i].avg=sum/4;
    }
}

void sort(Student arr[], int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (arr[j].avg > arr[j+1].avg) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void insertionSort(Student arr[], int n) {
    for (int i=0; i<n; i++) {
        Student key = arr[i];
        int j=i-1;
        while (j>=0 && arr[j].group < key.group) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void printArray(Student arr[], int n) {
    for (int i=0; i<n; i++) {
        cout<<arr[i].name<<" "<<arr[i].group<<" "<<arr[i].avg<<endl;
    }
    cout<<endl;
}

void binarySearch(Student arr[], int n, double targetAvg) {
    int left=0, right=n-1;
    bool found=false;

    while (left<=right) {
        int mid=left+(right-left)/2;
        if (arr[mid].avg == targetAvg) {
            found=true;
            int temp=mid;
            while (temp>=0 && arr[temp].avg == targetAvg) {
                cout<<arr[temp].name<<" "<<arr[temp].group<<endl;
                temp--;
            }
            temp=mid+1;
            while (temp<n && arr[temp].avg == targetAvg) {
                cout<<arr[temp].name<<" "<<arr[temp].group<<endl;
                temp++;
            }
            break;
        }
        if (arr[mid].avg < targetAvg) {
            left=mid+1;
        } else {
            right=mid-1;
        }
    }

    if (!found) {
        cout<<"No students found with avg grade "<<targetAvg<<endl;
    }

}

int main() {
    int n=5;
    Student students[5]={
        {"Oleg", 101, {4, 5, 3, 4}, 0.0},
        {"Ivan", 102, {3, 4, 2, 4}, 0.0},
        {"Petro", 100, {5, 3, 1, 4}, 0.0},
        {"Inna", 115, {3, 5, 4, 5}, 0.0},
        {"Oksana", 108, {2, 5, 3, 4}, 0.0},
    };

    Student studentsCopy[5];

    calculateAvg(students, n);

    for (int i=0; i<n; i++) {
        studentsCopy[i]=students[i];
    }

    sort(students, n);
    cout<<"Sorted by avg:"<<endl;
    printArray(students, n);

    insertionSort(studentsCopy, n);
    cout<<"Sorted by group:"<<endl;
    printArray(studentsCopy, n);

    double targetAvg=3.5;
    cout<<"Search result for avg grade:"<<targetAvg<<endl;
    binarySearch(students, n, targetAvg);

    return 0;
}