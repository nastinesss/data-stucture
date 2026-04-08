#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int N = 6;

int main() {
    vector<vector<int>> matrix(N, vector<int>(N, 0));

    auto addEdge = [&](int u, int v, int weight) {
        matrix[u - 1][v - 1] = weight;
        matrix[v - 1][u - 1] = weight;
    };

    addEdge(1, 3, 2);
    addEdge(2, 3, 6);
    addEdge(3, 5, 8);
    addEdge(3, 6, 9);
    addEdge(4, 5, 4);
    addEdge(4, 6, 4);

    cout << "1. Adjacency matrix:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    bool isComplete = true;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j && matrix[i][j] == 0) {
                isComplete = false;
                break;
            }
        }
    }
    cout << "2. Is graf full: " << (isComplete ? "Yes" : "No") << "\n\n";

    cout << "3. Adjacency list:\n";
    vector<vector<pair<int, int>>> adjList(N);
    for (int i = 0; i < N; ++i) {
        cout << "Top " << i + 1 << ":";
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] > 0) {
                adjList[i].push_back({j, matrix[i][j]});
                cout << " -> [" << j + 1 << ", weight: " << matrix[i][j] << "]";
            }
        }
        cout << "\n";
    }
    cout << "\n";

    int totalWeight = 0;
    int edgeCount = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (matrix[i][j] > 0) {
                totalWeight += matrix[i][j];
                edgeCount++;
            }
        }
    }
    double avgPath = (double)totalWeight / edgeCount;
    cout << "4. Average lenght of way (edge): " << avgPath << "\n\n";

    cout << "5-6. Isolated points and their number:\n";
    vector<int> isolatedNodes;
    for (int i = 0; i < N; ++i) {
        if (adjList[i].size() == 1) {
            isolatedNodes.push_back(i + 1);
            cout << " - Point " << i + 1 << " isolated. Distance to the nearest ("
                 << adjList[i][0].first + 1 << "): " << adjList[i][0].second << "\n";
        }
    }
    cout << "Number of isolated points: " << isolatedNodes.size() << ". Their numbers: ";
    for (int node : isolatedNodes) cout << node << " ";
    cout << "\n\n";

    int maxDist = -1;
    int best_u = -1, best_v = -1, best_w = -1;
    int w1 = 0, w2 = 0;

    for (int v = 0; v < N; ++v) {
        for (size_t i = 0; i < adjList[v].size(); ++i) {
            for (size_t j = i + 1; j < adjList[v].size(); ++j) {
                int u = adjList[v][i].first;
                int weight_uv = adjList[v][i].second;
                int w = adjList[v][j].first;
                int weight_vw = adjList[v][j].second;

                if (weight_uv + weight_vw > maxDist) {
                    maxDist = weight_uv + weight_vw;
                    best_u = u;
                    best_v = v;
                    best_w = w;
                    w1 = weight_uv;
                    w2 = weight_vw;
                }
            }
        }
    }

    cout << "7. Route with the biggest total way between 3 cities:\n";
    if (best_u != -1) {
        cout << "(" << best_u + 1 << ") --- " << w1 << " --- (" << best_v + 1 << ") --- " << w2 << " --- (" << best_w + 1 << ")\n\n";
    }

    bool hasHamiltonian = false;
    vector<bool> visited(N, false);

    auto dfs = [&](auto& self, int curr, int count) -> void {
        visited[curr] = true;
        if (count == N) {
            hasHamiltonian = true;
        }
        if (!hasHamiltonian) {
            for (auto& edge : adjList[curr]) {
                if (!visited[edge.first]) {
                    self(self, edge.first, count + 1);
                }
            }
        }
        visited[curr] = false;
    };

    for (int i = 0; i < N; ++i) {
        dfs(dfs, i, 1);
        if (hasHamiltonian) break;
    }

    cout << "8. Is it possible to go around all localities, driving in only once?\n";
    if (hasHamiltonian) {
        cout << " - Yes.\n";
    } else {
        cout << " - No.\n";
    }

    return 0;
}