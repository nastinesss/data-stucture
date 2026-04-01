#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

bool CheckKrat(int n)
{
    return (n > 0 && n % 4 == 0);
}

void PrintArray(double* arr, int n)
{
    for (int i = 0; i < n; i++) {
        cout << setw(6) << fixed << setprecision(2) << arr[i] << " ";
    }
    cout << endl;
}

void FillArray(double* arr, int n)
{
    for (int i = 0; i < n; i++)
	{
        arr[i] = (rand() % 601) / 100.0 - 1.5;
    }
}

double** CreateMatrix(double* arr, int n, int& rows, int& cols)
{
    rows = n / 4;
    cols = 4;

    double** mat = new double*[rows];
    int k = 0;
    for (int i = 0; i < rows; i++) {
        mat[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            mat[i][j] = arr[k++];
        }
    }
    return mat;
}

void BubbleSort(double* arr, int size, bool ascending)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (ascending) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            } else {
                if (arr[j] < arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

double FindMax(double* arr, int size) {
    double maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void DeleteMatrix(double** mat, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

int main() {
    srand(time(0));
    
    int test_values[] = {20, 100, 1000};
    int num_tests = 3;

    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cerr << "Error creating file!" << endl;
        return 1;
    }

    fout << "|-------|-------|-------------|-------------|" << endl;
    fout << "|   №  |   n   |  Time, sec. | Space, byte |" << endl;
    fout << "|-------|-------|-------------|-------------|" << endl;

    cout << "Starting tests..." << endl;

    for (int t = 0; t < num_tests; t++) {
        int n = test_values[t];
        
        if (!CheckKrat(n)) {
            cerr << "Warning: n = " << n << " is invalid!" << endl;
            continue; 
        }

        double* B = new double[n];
        FillArray(B, n);

        int rows, cols;
        double** A = CreateMatrix(B, n, rows, cols);
        
        clock_t start = clock();

        for (int i = 0; i < rows; i++) {
            BubbleSort(A[i], cols, (i % 2 == 0));
        }

        double* colTemp = new double[rows];
        double* maxValues = new double[cols];
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                colTemp[i] = A[i][j];
            }
            maxValues[j] = FindMax(colTemp, rows);
        }
        
        clock_t end = clock();
        
        if (n == 20) {
            cout << "\n--- Processed Matrix (n=20) ---" << endl;
            for(int r=0; r<rows; r++){
                PrintArray(A[r], cols);
            }
        for (int j = 0; j < cols; j++) 
            cout << "Max of Column " << j << ": " << maxValues[j] << endl;
    }

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        long space_used = sizeof(double) * n; 

        fout << "| " << setw(5) << (t + 1) << " | " 
             << setw(5) << n << " | " 
             << setw(11) << fixed << setprecision(3) << time_spent << " | " 
             << setw(11) << space_used << " |" << endl;
        fout << "|-------|-------|-------------|-------------|" << endl;

        delete[] maxValues;
        delete[] colTemp;
        DeleteMatrix(A, rows);
        delete[] B;
    }

    fout.close();
    cout << "Done! Results saved to output.txt" << endl;

    return 0;
}