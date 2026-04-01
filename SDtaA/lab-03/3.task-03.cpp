#include <iostream>
using namespace std;

enum PaymentType
{
    CASH,
    CARD,
    TRANSFER,
};

union PaymentData
{
    int cash_id;
    char card_num[20];
    char account [20];
};

struct Payment
{
    int number;
    PaymentType type;
    PaymentData data;
};

int main()
{
    int n;
    cout<<"Number of payments: ";
    cin>>n;

    Payment p[100];

    int cash_count=0, card_count=0, transfer_count=0;

    for(int i=0;i<n;i++)
    {
        cout<<"Payment "<<i+1<<endl;

        cout<<"Number: ";
        cin>>p[i].number;

        cout<<"Type (0-Cash, 1-Card, 2-Transfer): ";
        int t;
        cin>>t;

        p[i].type=(PaymentType)t;

        if(p[i].type==CASH)
        {
            cout<<"Cash ID: ";
            cin>>p[i].data.cash_id;
            cash_count++;
        }

        else if(p[i].type==CARD)
        {
            cout<<"Card number: ";
            cin>>p[i].data.card_num;
            card_count++;
        }

        else if(p[i].type==TRANSFER)
        {
            cout<<"Account number: ";
            cin>>p[i].data.account;
            transfer_count++;
        }
    }

    cout<<"Payment information:"<<endl;

    for(int i=0;i<n;i++)
    {
        cout<<"Payment "<<p[i].number<<endl;

        if(p[i].type==CASH)
            cout<<"Cash ID: "<<p[i].data.cash_id<<endl;

        else if(p[i].type==CARD)
            cout<<"Card number: "<<p[i].data.card_num<<endl;

        else if(p[i].type==TRANSFER)
            cout<<"Account number: "<<p[i].data.account<<endl;
    }

    cout<<"Statistics:"<<endl;
    cout<<"Cash: "<<cash_count<<endl;
    cout<<"Card: "<<card_count<<endl;
    cout<<"Transfer: "<<transfer_count<<endl;

    return 0;
}