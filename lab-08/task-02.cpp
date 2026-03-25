#include <iostream>
#include <string>
using namespace std;

struct Course {
    string courseName;
    int hours;
    int students;
    Course *next, *prev;
};

class CourseList {
    public:
    Course *head,*tail;
    CourseList():head(0), tail(0) {}

    void addCourse(string courseName, int hours, int students) {
        Course *newCourse = new Course{courseName, hours, students};
        if (!head) head = tail = newCourse;
        else {
            tail->next = newCourse;
            newCourse->prev = tail;
            tail=newCourse;
        }
    }

    void displayForward() {
        Course* temp=head;
        while (temp) {
            cout << "[" << temp->courseName << " | H: " << temp->hours << " | S: " << temp->students << "] ";
            temp = temp->next;
        }
        cout << endl;
    }

    void displayBackward() {
        Course* temp=tail;
        while (temp) {
            cout<<"["<<temp->courseName<< " | H: " << temp->hours << " | S: " << temp->students << "] ";
            temp = temp->prev;
        }
        cout << endl;
    }

    void clear() {
        while (head) {
            Course* temp=head;
            head=head->next;
            delete temp;
        }
        tail=0;
    }
};

int main() {
    CourseList mainList, highList, lowList;
    int n;

    cout<<"Enter number of courses: ";
    cin>>n;

    double totalStudents=0;
    for (int i=0;i<n;i++) {
        string courseName;
        int hours, students;
        cout<<"Course "<<i+1<<" name, hours, students: ";
        cin>>courseName>>hours>>students;
        mainList.addCourse(courseName, hours, students);
        totalStudents+=students;
    }

    double average=totalStudents/n;
    cout<<"Average students: "<<average<<endl;
    Course* current=mainList.head;
    while (current) {
        if (current->students>average) {
            highList.addCourse(current->courseName, current->hours, current->students);
        } else {
            lowList.addCourse(current->courseName, current->hours, current->students);
        }
        current=current->next;
    }

    cout << "--- High Attendance List (Forward & Backward) ---"<<endl;
    highList.displayForward();
    highList.displayBackward();

    cout << "\n--- Low/Average Attendance List (Forward & Backward) ---" <<endl;
    lowList.displayForward();
    lowList.displayBackward();

    mainList.clear();
    highList.clear();
    lowList.clear();
    return 0;
}