#include <iostream>
#include <string>
using namespace std;

struct EmployeeList {
    string lastName;
    string department;
    double salary;
    EmployeeList* next;
    EmployeeList* prev;

    EmployeeList(string ln, string dept, double sal): lastName(ln), department(dept), salary(sal), next(NULL), prev(NULL) {}
};

class Employee {
    public:
    EmployeeList* head;
    EmployeeList* tail;

    Employee(): head(NULL), tail(NULL) {}

    void append(string ln, string dept, double sal) {
        EmployeeList* newList = new EmployeeList(ln, dept, sal);
        if (!head) {
            head = tail = newList;
        } else {
            tail->next=newList;
            newList->prev=tail;
            tail=newList;
        }
    }

    void printForward() {
        EmployeeList* current=head;
        while (current) {
            cout<<"["<<current->lastName<<", "<<current->department<<", "<<current->salary<<"]"<<endl;
            current=current->next;
        }
        cout<<endl;
    }

    void printBackward() {
        EmployeeList* current = tail;
        while (current) {
            cout<<"["<<current->lastName<<", "<<current->department<<", "<<current->salary<<"]"<<endl;
            current=current->prev;
        }
        cout<<endl;
    }

    double getAverageSalary() {
        if (!head) return 0;
        double sum=0;
        int count=0;
        EmployeeList* current=head;
        while (current) {
            sum+=current->salary;
            count++;
            current=current->next;
        }
        return sum/count;
    }

    void clearMemory() {
        EmployeeList* current=head;
        while (current) {
            EmployeeList* next=current->next;
            delete current;
            current=next;
        }
        head=tail=NULL;
    }
};

int main() {
    Employee mainList;
    int n;

    cout<<"Enter number of employees: ";
    cin>>n;

    for (int i=0; i<n; i++) {
        string ln,dept;
        double sal;
        cout<<"Employee "<<i+1<<": ";
        cin>>ln>>dept>>sal;
        mainList.append(ln,dept,sal);
    }
    double avg=mainList.getAverageSalary();
    cout<<"Average salary: "<<avg<<endl;
    Employee aboveAvg;
    Employee belowEqAvg;

    EmployeeList* current=mainList.head;
    while (current) {
        if (current->salary > avg) {
            aboveAvg.append(current->lastName,current->department,current->salary);
        }
        else
            belowEqAvg.append(current->lastName,current->department,current->salary);
        current=current->next;
    }

    cout<<"\n--- List 1: Above Average ---" << endl;
    cout << "Forward: "; aboveAvg.printForward();
    cout << "Backward: "; aboveAvg.printBackward();

    cout << "\n--- List 2: Below or Equal Average ---" << endl;
    cout << "Forward: "; belowEqAvg.printForward();
    cout << "Backward: "; belowEqAvg.printBackward();

    cout << "\nAdding a new employee to the first list..." << endl;
    aboveAvg.append("New", "IT", 9999.9);
    cout << "Updated List 1 Forward: "; aboveAvg.printForward();

    mainList.clearMemory();
    aboveAvg.clearMemory();
    belowEqAvg.clearMemory();

    return 0;
}