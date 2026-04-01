#include <iostream>
#include <string>
using namespace std;

enum Faculty
{
    IT,
    ECONOMY,
    LAW,
    MANAGEMENT
};

struct Student
{
    string surname;
    int course;
    double avg;
    Faculty faculty;
};

int main()
{
    int n=5;
    Student s[n];

    for(int i=0;i<n;i++)
    {
        cout<<"Student "<<i+1<<endl;

        cout<<"Surname: ";
        cin>>s[i].surname;

        cout<<"Course: ";
        cin>>s[i].course;

        cout<<"Average mark: ";
        cin>>s[i].avg;

        cout<<"Faculty (0-IT, 1-Economy, 2-Law, 3-Management): ";
        int f;
        cin>>f;
        s[i].faculty=(Faculty)f;
    }

    cout<<"Students of IT faculty: "<<endl;
    for(int i=0;i<n;i++)
    {
        if(s[i].faculty==IT)
            cout<<s[i].surname<<" course "<<s[i].course<<" average "<<s[i].avg<<endl;
    }

    double sum=0;
    for(int i=0;i<n;i++)
        sum+=s[i].avg;

    cout<<"Average mark of group: "<<sum/n<<endl;

    return 0;
}