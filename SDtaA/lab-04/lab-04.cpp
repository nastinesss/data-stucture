#include <iostream>
#include <string>
using namespace std;

struct School
{
    string name;
    int klas;
    int subj[5];
};

void excellent(School a[], int n)
{
    bool found=true;
    cout<<"Excellent students from graduate classes:"<<endl;

    for(int i=0;i<n;i++)
    {
        bool ok=true;
        for(int j=0;j<5;j++)
        {
            if(a[i].subj[j]!=5)
                ok=false;
            break;
        }

        if(ok && (a[i].klas==9 || a[i].klas==11))
        {
            cout<<a[i].name<<" class "<<a[i].klas<<endl;
            found=true;
        }
    }
    if(!found)
        cout<<"No excellent students in graduate classes"<<endl;
}

void badmark(School a[], int n)
{
    bool found=false;
    cout<<"Students with mark 2:"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(a[i].subj[j]==2)
            {
                cout<<a[i].name<<" class "<<a[i].klas<<endl;
                found=true;
                break;
            }
        }
    }
    if(!found)
        cout<<"No such students"<<endl;
}

void sortClass(School a[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i].klas<a[j].klas)
                swap(a[i],a[j]);
        }
    }
}

void delClass(School a[], int &n, int k)
{
    for(int i=0;i<n;i++)
    {
        if(a[i].klas==k)
        {
            for(int j=i;j<n-1;j++)
                a[j]=a[j+1];
            n--;
            i--;
        }
    }
}

void show(School a[], int n)
{
    cout<<"Students:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<a[i].name<<" class "<<a[i].klas<<" marks: ";
        for(int j=0;j<5;j++)
            cout<<a[i].subj[j]<<" ";
        cout<<endl;
    }
}

int main()
{
    int n;

    cout<<"Number of students: ";
    cin>>n;

    School a[100];

    for(int i=0;i<n;i++)
    {
        cout<<"Student "<<i+1<<endl;

        cout<<"Name: ";
        cin>>a[i].name;

        cout<<"Class: ";
        cin>>a[i].klas;

        cout<<"5 marks: "<<endl;

        for(int j=0;j<5;j++)
            cin>>a[i].subj[j];
    }

    excellent(a,n);
    badmark(a,n);

    sortClass(a,n);
    cout<<"Sorted by class:"<<endl;
    show(a,n);

    int k;
    cout<<"Enter class to delete: ";
    cin>>k;

    delClass(a,n,k);

    cout<<"After deleting: "<<endl;
    show(a,n);
    return 0;
}