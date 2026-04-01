#include <iostream>
#include <string>
using namespace std;

struct List2 {
    string date;
    float temperature;
    List2* next;
    List2* prev;

    List2(string d, float t): date(d), temperature(t), next(NULL), prev(NULL) {}
};

class TemperatureList {
    public:
    List2* head;
    List2* tail;

    TemperatureList(): head(NULL), tail(NULL) {}

    void addList(string date, float temp) {
        List2* newList2 = new List2(date, temp);
        if (!head) {
            head = tail = newList2;
        } else {
            tail->next = newList2;
            newList2->prev = tail;
            tail = newList2;
        }
    }

    void merge(TemperatureList& other) {
        if (!other.head) return;
        if (!head) {
            head = other.head;
            tail = other.tail;
        } else {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
        }
        other.head=nullptr;
        other.tail=nullptr;
    }

    void printMinMax() {
        if (!head) return;
        double minT=head->temperature;
        string minD=head->date;
        double maxT=head->temperature;
        string maxD=head->date;

        List2* current = head->next;
        while (current!=nullptr) {
            if (current->temperature < minT) {
                minT = current->temperature;
                minD = current->date;
            }
            if (current->temperature > maxT) {
                maxT = current->temperature;
                maxD = current->date;
            }
            current = current->next;
        }
        cout<<"Max temperature: "<<maxT<<" on "<<maxD<<endl;
        cout<<"Min temperature: "<<minT<<" on "<<minD<<endl;
    }
    void clearMemory() {
        List2* current = head;
        while (current!=nullptr) {
            List2* nextList=current->next;
            delete current;
            current=nextList;
        }
        head=tail=nullptr;
    }
};

int main() {
    TemperatureList list1;
    TemperatureList list2;

    list1.addList("2026-01-01", -10);
    list2.addList("2026-01-10", -13);

    list1.addList("2026-02-01", -12);
    list2.addList("2026-02-10", -14);

    list1.merge(list2);
    list1.printMinMax();
    list1.clearMemory();

    return 0;
}