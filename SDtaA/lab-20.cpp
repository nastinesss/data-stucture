#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int id;
    int start;
    int end;
};

bool compareActivities(const Activity& a, const Activity& b) {
    return a.end < b.end;
}

void solveTask1() {
    double s = 1.0;
    double m = 16 * s;
    double f = 8 * s;
    double l = 8 * s;
    
    cout << "Task 1 Results:" <<endl;
    cout << "Meat: " << m << " kg" <<endl;
    cout << "Flour: " << f << " kg" <<endl;
    cout << "Milk: " << l << " kg" <<endl;
    cout << "Sugar: " << s << " kg" <<endl;
    cout << "Total Mass: " << (m + f + l + s) << " kg" <<endl;
    cout << "Total Volume: " << (m * 1.0 + f * 1.5 + l * 2.0 + s * 1.0) << " dm3" << endl;
    cout << "Total Calories: " << (m * 1500 + f * 5000 + l * 5000 + s * 4000) << " kcal" <<endl;
    cout << "-----------------------------------" <<endl;
}

void solveTask2() {
    int n;
    if (!(cin >> n)) return;
    
    vector<Activity> activities(n);
    for (int i = 0; i < n; ++i) {
        activities[i].id = i + 1;
        cin >> activities[i].start >> activities[i].end;
    }
    
    sort(activities.begin(), activities.end(), compareActivities);
    
    vector<Activity> selected;
    if (n > 0) {
        selected.push_back(activities[0]);
        int last_end_time = activities[0].end;
        
        for (int i = 1; i < n; ++i) {
            if (activities[i].start >= last_end_time) {
                selected.push_back(activities[i]);
                last_end_time = activities[i].end;
            }
        }
    }
    
    cout << "Task 2 Results:" <<endl;
    cout << "Maximum number of activities: " << selected.size() <<endl;
    cout << "Selected activities (Index, Start, End):" <<endl;
    for (const auto& act : selected) {

        cout << "Index: " << act.id << " (" << act.start << ", " << act.end << ")" <<endl;
    }
}

int main() {
    solveTask1();
    solveTask2();
    return 0;
}