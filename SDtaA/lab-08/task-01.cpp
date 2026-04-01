#include <iostream>
using namespace std;

struct List {
    int data;
    List* next;
};

class Stack {
    List* top;
    public:
    Stack():top(0) {}
    void push(int value) {
        List* newList=new List();
        newList->data=value;
        newList->next=top;
        top=newList;
    }

    void display() {
        if (!top) {
            cout<<"\nStack is empty";
            return;
        }
        List* temp=top;
        cout<<"Stack elements: ";
        while(temp) {
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }

    double calculateAverage() {
        if (!top) return 0;
        int sum=0;
        int count=0;
        List* temp=top;
        while(temp) {
            sum=sum+temp->data;
            count++;
            temp=temp->next;
        }
        return sum/count;
    }

    void clear() {
        while (top) {
            List* temp=top;
            top=top->next;
            delete temp;
        }
        cout<<"Stack cleared."<<endl;
    }
    ~Stack() {
        clear();
    }
};

int main() {
    Stack gradesStack;
    int n, val;
    cout<<"Enter number of grades: ";
    cin>>n;

    for(int i=0;i<n;i++) {
        cout<<"Enter grade "<<i+1<<": ";
        cin>>val;
        gradesStack.push(val);
    }

    gradesStack.display();
    cout<<"Average grade: "<<gradesStack.calculateAverage()<<endl;
    gradesStack.clear();

    return 0;
}