#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Position {
    double A;
    double B;
    int count;
};

void solveTask1() {
    vector<Position> positions = {
        {1, 1, 7},   // Sanitarka
        {6, 5, 10},  // Medsestra
        {8, 5, 10},  // Likar
        {9, 5, 1},   // Zav. aptekoyu
        {2, 1, 3},   // Zav. viddilennyam
        {12, 5, 1},  // Golovny likar
        {13, 5, 1},  // Zav. gosp.
        {3, 1, 1}    // Zav. likarneyu
    };

    double targetBudget = 680000.0;
    double bestBaseSalary = 0;
    double minDiff = targetBudget;
    double bestTotalSalary = 0;

    double totalCoeffSum = 0;
    for (const auto& pos : positions) {
        totalCoeffSum += (pos.A / pos.B) * pos.count;
    }

    double theoreticalBase = targetBudget / totalCoeffSum;
    int startBase = static_cast<int>(theoreticalBase) - 500;
    int endBase = static_cast<int>(theoreticalBase) + 500;

    for (int base = startBase; base <= endBase; ++base) {
        if (base <= 0) continue;
        
        double currentTotal = 0;
        for (const auto& pos : positions) {
            double coeff = pos.A / pos.B;
            currentTotal += floor(base * coeff) * pos.count;
        }

        if (currentTotal <= targetBudget) {
            double diff = targetBudget - currentTotal;
            if (diff < minDiff) {
                minDiff = diff;
                bestBaseSalary = base;
                bestTotalSalary = currentTotal;
            }
        }
    }

    cout << "Task 1 Results:" << endl;
    cout << "Optimal Base Salary (Sanitarka): " << bestBaseSalary << " UAH" << endl;
    cout << "Calculated Budget: " << bestTotalSalary << " UAH" << endl;
    cout << "Remaining Budget: " << minDiff << " UAH" << endl;
    cout << "-----------------------------------" << endl;
}

void northwestCorner(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost) {
    int numSupply = supply.size();
    int numDemand = demand.size();
    vector<vector<int>> allocation(numSupply, vector<int>(numDemand, 0));
    
    int i = 0, j = 0;
    while (i < numSupply && j < numDemand) {
        int quantity = min(supply[i], demand[j]);
        allocation[i][j] = quantity;
        supply[i] -= quantity;
        demand[j] -= quantity;
        
        if (supply[i] == 0) i++;
        else j++;
    }

    int totalCost = 0;
    cout << "Northwest Corner Method Plan:" << endl;
    for (int r = 0; r < numSupply; ++r) {
        for (int c = 0; c < numDemand; ++c) {
            cout << setw(5) << allocation[r][c] << " ";
            totalCost += allocation[r][c] * cost[r][c];
        }
        cout << endl;
    }
    cout << "Total Cost: " << totalCost << endl;
}

void minimumCostMethod(vector<int> supply, vector<int> demand, const vector<vector<int>>& cost) {
    int numSupply = supply.size();
    int numDemand = demand.size();
    vector<vector<int>> allocation(numSupply, vector<int>(numDemand, 0));
    
    while (true) {
        int minCost = 10000000;
        int minRow = -1, minCol = -1;
        
        for (int r = 0; r < numSupply; ++r) {
            if (supply[r] == 0) continue;
            for (int c = 0; c < numDemand; ++c) {
                if (demand[c] == 0) continue;
                if (cost[r][c] < minCost) {
                    minCost = cost[r][c];
                    minRow = r;
                    minCol = c;
                }
            }
        }
        
        if (minRow == -1 || minCol == -1) break;
        
        int quantity = min(supply[minRow], demand[minCol]);
        allocation[minRow][minCol] = quantity;
        supply[minRow] -= quantity;
        demand[minCol] -= quantity;
    }

    int totalCost = 0;
    cout << "Minimum Cost Method Plan:" << endl;
    for (int r = 0; r < numSupply; ++r) {
        for (int c = 0; c < numDemand; ++c) {
            cout << setw(5) << allocation[r][c] << " ";
            totalCost += allocation[r][c] * cost[r][c];
        }
        cout << endl;
    }
    cout << "Total Cost: " << totalCost << endl;
}

void solveTask2() {
    vector<int> supply = {1500, 1900, 1600};
    vector<int> demand = {1800, 1200, 2000};
    vector<vector<int>> cost = {
        {8, 7, 2},
        {1, 4, 3},
        {5, 1, 6}
    };

    cout << "Task 2 Results:" << endl;
    northwestCorner(supply, demand, cost);
    cout << "-----------------------------------" << endl;
    minimumCostMethod(supply, demand, cost);
}

int main() {
    solveTask1();
    solveTask2();
    return 0;
}