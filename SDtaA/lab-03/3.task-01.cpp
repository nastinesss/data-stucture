#include <iostream>
#include <string>
using namespace std;

struct Worker
{
    string name;
    string position;
    int year;
    double salary;
};

int experience(Worker w)
{
    return 2026-w.year;
}

double salary(Worker w)
{
    return w.salary-w.salary*0.33;
}

int main()
{
    int n;
    cout<<"Number of workers: ";
    cin>>n;
    Worker w[100];
    for(int i=0;i<n;i++)
    {
        cout<<"Worker "<<i+1<<endl;

        cout<<"Name: ";
        cin>>w[i].name;

        cout<<endl;

        cout<<"Year: ";
        cin>>w[i].year;

        cout<<endl;

        cout<<"Position: ";
        cin>>w[i].position;

        cout<<endl;

        cout<<"Salary: ";
        cin>>w[i].salary;
    }

    cout<<endl<<"Information:";

    for(int i=0;i<n;i++)
    {
        cout<<"\n"<<w[i].name<<endl;
        cout<<"Position: "<<w[i].position<<endl;
        cout<<"Experience: "<<experience(w[i])<<" years"<<endl;
        cout<<"Salary after tax: "<<salary(w[i])<<endl;
    }

    return 0;
}