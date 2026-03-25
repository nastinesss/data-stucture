#include <iostream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

// TASK 1
struct Stack1 {
    double data;
    Stack1* next;
};

void push1(Stack1*& top, double val) {
    top = new Stack1{val, top};
}

double pop1(Stack1*& top) {
    if (!top) return 0.0;
    double val = top->data;
    Stack1* temp = top;
    top = top->next;
    delete temp;
    return val;
}

bool isEmpty1(Stack1* top) {
    return top == nullptr;
}

void freeStack1(Stack1*& top) {
    while (top) pop1(top);
}

// TASK 2
struct MusicRecord {
    string medium;
    string title;
    string artist;
    double duration;
    int count;
    double price;
};

struct MusicStack {
    MusicRecord data;
    MusicStack* next;
};

void pushMusic(MusicStack*& top, MusicRecord record) {
    top = new MusicStack{record, top};
}

MusicRecord popMusic(MusicStack*& top) {
    MusicRecord val = top->data;
    MusicStack* temp = top;
    top = top->next;
    delete temp;
    return val;
}

bool isEmptyMusic(MusicStack* top) {
    return top == nullptr;
}

void freeMusicStack(MusicStack*& top) {
    while (top) popMusic(top);
}

// TASK 3
struct Queue3 {
    int data;
    Queue3* next;
};

void enqueue3(Queue3*& head, Queue3*& tail, int val) {
    Queue3* temp = new Queue3{val, nullptr};
    if (!head) {
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

int dequeue3(Queue3*& head, Queue3*& tail) {
    if (!head) return 0;
    int val = head->data;
    Queue3* temp = head;
    head = head->next;
    if (!head)
    delete temp;
    return val;
}

bool isEmpty3(Queue3* head) {
    return head == nullptr;
}

void freeQueue3(Queue3*& head, Queue3*& tail) {
    while (head) dequeue3(head, tail);
}

// TASK 4
struct Team {
    string name;
    string city;
    int points;
};

struct TeamQueue {
    Team data;
    TeamQueue* next;
};

void enqueueTeam(TeamQueue*& head, TeamQueue*& tail, Team team) {
    TeamQueue* temp = new TeamQueue{team, nullptr};
    if (!head) {
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

Team dequeueTeam(TeamQueue*& head, TeamQueue*& tail) {
    Team val = head->data;
    TeamQueue* temp = head;
    head = head->next;
    if (!head)
    delete temp;
    return val;
}

bool isEmptyTeam(TeamQueue* head) {
    return head == nullptr;
}

bool cityExists(TeamQueue* head, const string& city) {
    TeamQueue* current = head;
    while (current) {
        if (current->data.city == city) return true;
        current = current->next;
    }
    return false;
}

void freeTeamQueue(TeamQueue*& head, TeamQueue*& tail) {
    while (head) dequeueTeam(head, tail);
}

int main() {
    srand(time(0));

    //Task 1
    cout << "=== Task 1 ===" << endl;
    Stack1* stack1 = nullptr;
    cout << "Initial stack: ";
    for (int i = 0; i < 10; i++) {
        double r = -6.0 + (rand() % 1701) / 100.0; // [-6; 11]
        push1(stack1, r);
        cout << r << " ";
    }
    cout << endl;

    double limit;
    cout << "Enter limit data: ";
    cin >> limit;

    Stack1* newStack1 = nullptr;

    while (!isEmpty1(stack1)) {
        double val = pop1(stack1);
        if (val >= limit) {
            push1(newStack1, val);
        }
    }

    double sum1 = 0;
    int count1 = 0;
    Stack1* temp1 = newStack1;
    cout << "New stack (elements >= " << limit << "): ";
    while (temp1) {
        cout << temp1->data << " ";
        sum1 += temp1->data;
        count1++;
        temp1 = temp1->next;
    }
    cout << endl;

    if (count1 > 0) cout << "Average: " << sum1 / count1 << endl;
    else cout << "New stack is empty." << endl;

    freeStack1(newStack1);


    //Task 2
    cout << "\n=== Task 2 ===" << endl;
    MusicStack* musicStack = nullptr;
    pushMusic(musicStack, {"audio cassette", "Song 1", "Artist A", 3.5, 1, 150.0});
    pushMusic(musicStack, {"laser disc", "Song 2", "Artist B", 4.0, 1, 300.0});
    pushMusic(musicStack, {"audio cassette", "Song 3", "Artist A", 5.2, 1, 120.0});
    pushMusic(musicStack, {"vinyl record", "Song 4", "Artist C", 6.0, 1, 500.0});

    string targetArtist = "Artist A";
    double totalDuration = 0.0;

    MusicStack* cassetteStack = nullptr;

    while (!isEmptyMusic(musicStack)) {
        MusicRecord rec = popMusic(musicStack);

        if (rec.artist == targetArtist) {
            totalDuration += rec.duration;
        }

        if (rec.medium == "audio cassette") {
            pushMusic(cassetteStack, rec);
        }
    }

    cout << "Total playing time for '" << targetArtist << "': " << totalDuration << " min." << endl;

    double cassettePriceSum = 0;
    int cassetteCount = 0;

    MusicStack* tempCassette = cassetteStack;
    while (tempCassette) {
        cassettePriceSum += tempCassette->data.price;
        cassetteCount++;
        tempCassette = tempCassette->next;
    }

    if (cassetteCount > 0)
        cout << "Average cost of audio cassettes in the new stack: " << cassettePriceSum / cassetteCount << " UAH." << endl;

    freeMusicStack(cassetteStack);


    //Task 3
    cout << "\n=== Task 3 ===" << endl;
    Queue3* q3head = nullptr; Queue3* q3tail = nullptr;
    cout << "Initial queue: ";
    for (int i = 0; i < 7; i++) {
        int val = rand() % 20 + 1; // positive datas [1; 20]
        enqueue3(q3head, q3tail, val);
        cout << val << " ";
    }
    cout << endl;

    Queue3* newQ3head = nullptr; Queue3* newQ3tail = nullptr;

    while (!isEmpty3(q3head)) {
        int val = dequeue3(q3head, q3tail);
        if (val % 2 == 0) {
            enqueue3(newQ3head, newQ3tail, val);
            enqueue3(newQ3head, newQ3tail, 100);
        }
    }

    double product3 = 1.0;
    int count3 = 0;
    cout << "New queue (evens + 100): ";

    while (!isEmpty3(newQ3head)) {
        int val = dequeue3(newQ3head, newQ3tail);
        cout << val << " ";
        product3 *= val;
        count3++;
    }
    cout << endl;

    if (count3 > 0) {
        cout << "Geometric: " << pow(product3, 1.0 / count3) << endl;
    } else {
        cout << "New queue is empty (no even datas found)." << endl;
    }


    //Task 4
    cout << "\n=== Task 4 ===" << endl;
    TeamQueue* mainQhead = nullptr; TeamQueue* mainQtail = nullptr;
    enqueueTeam(mainQhead, mainQtail, {"Falcons", "Kyiv", 15});
    enqueueTeam(mainQhead, mainQtail, {"Leopards", "Lviv", 22});
    enqueueTeam(mainQhead, mainQtail, {"Tigers", "Kyiv", 10});
    enqueueTeam(mainQhead, mainQtail, {"Lions", "Odesa", 18});
    enqueueTeam(mainQhead, mainQtail, {"Sharks", "Odesa", 25});

    int targetPoints;
    cout << "Enter target points to filter teams: ";
    cin >> targetPoints;

    TeamQueue* cityQhead = nullptr; TeamQueue* cityQtail = nullptr;
    TeamQueue* highQhead = nullptr; TeamQueue* highQtail = nullptr;
    TeamQueue* tempQhead = nullptr; TeamQueue* tempQtail = nullptr;
    Team leader = {"", "", -1};
    Team outsider = {"", "", 999999};

    while (!isEmptyTeam(mainQhead)) {
        Team t = dequeueTeam(mainQhead, mainQtail);

        if (t.points > leader.points) leader = t;
        if (t.points < outsider.points) outsider = t;

        if (!cityExists(cityQhead, t.city)) {
            enqueueTeam(cityQhead, cityQtail, t);
        }

        if (t.points > targetPoints) {
            enqueueTeam(highQhead, highQtail, t);
        }

        enqueueTeam(tempQhead, tempQtail, t);
    }

    mainQhead = tempQhead;
    mainQtail = tempQtail;

    cout << "Leader: " << leader.name << " (" << leader.points << " points)" << endl;
    cout << "Outsider: " << outsider.name << " (" << outsider.points << " points)" << endl;

    cout << "Teams from unique cities: ";
    TeamQueue* currCity = cityQhead;
    while (currCity) {
        cout << currCity->data.name << "[" << currCity->data.city << "] ";
        currCity = currCity->next;
    }
    cout << endl;

    cout << "Teams with more than " << targetPoints << " points: ";
    TeamQueue* currHigh = highQhead;
    while (currHigh) {
        cout << currHigh->data.name << " ";
        currHigh = currHigh->next;
    }
    cout << endl;

    freeTeamQueue(mainQhead, mainQtail);
    freeTeamQueue(cityQhead, cityQtail);
    freeTeamQueue(highQhead, highQtail);

    return 0;
}