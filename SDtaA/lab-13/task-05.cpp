#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

int main() {
    int N, M, K;
    cout << "Enter number of elements to insert (N): "; cin >> N;
    cout << "Enter number of elements to delete (M): "; cin >> M;
    cout << "Enter number of elements to search (K): "; cin >> K;

    map<int, int> treeMap;
    unordered_map<int, int> hashMap;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, N * 2);

    vector<int> keysToInsert(N);
    vector<int> keysToDelete(M);
    vector<int> keysToSearch(K);

    for(int i=0; i<N; ++i) keysToInsert[i] = distrib(gen);
    for(int i=0; i<M; ++i) keysToDelete[i] = keysToInsert[i % N];
    for(int i=0; i<K; ++i) keysToSearch[i] = distrib(gen);


    cout << "\n--- Тестування map ---\n";
    
    auto start = high_resolution_clock::now();
    for (int key : keysToInsert) treeMap[key] = key;
    auto stop = high_resolution_clock::now();
    cout << "Insert: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int key : keysToDelete) treeMap.erase(key);
    stop = high_resolution_clock::now();
    cout << "Delete: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    start = high_resolution_clock::now();
    int foundMap = 0;
    for (int key : keysToSearch) {
        if (treeMap.find(key) != treeMap.end()) foundMap++;
    }
    stop = high_resolution_clock::now();
    cout << "Search: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";


    cout << "\n--- Тестування unordered_map ---\n";
    
    start = high_resolution_clock::now();
    for (int key : keysToInsert) hashMap[key] = key;
    stop = high_resolution_clock::now();
    cout << "Insert: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    start = high_resolution_clock::now();
    for (int key : keysToDelete) hashMap.erase(key);
    stop = high_resolution_clock::now();
    cout << "Delete: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    start = high_resolution_clock::now();
    int foundUMap = 0;
    for (int key : keysToSearch) {
        if (hashMap.find(key) != hashMap.end()) foundUMap++;
    }
    stop = high_resolution_clock::now();
    cout << "Search: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";

    return 0;
}