#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort(int* arr, int size, bool ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j = j + 1) {
            bool needSwap = false;
            if (ascending == true) {
                if (arr[j] > arr[j + 1]) needSwap = true;
            } else {
                if (arr[j] < arr[j + 1]) needSwap = true;
            }

            if (needSwap == true) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void task1() {
    cout << "\n=== TASK 1 ===" << endl;
    int n;
    cout << "Enter array size n: ";
    cin >> n;

    int* A = new int[n];
    int* evens = new int[n];
    int* odds = new int[n];
    int evensCount = 0;
    int oddsCount = 0;

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
        cout << A[i] << " ";
        if (A[i] % 2 == 0) {
            evens[evensCount] = A[i];
            evensCount++;
        } else {
            odds[oddsCount] = A[i];
            oddsCount++;
        }
    }
    cout << endl;

    clock_t startAsc = clock();
    bubbleSort(evens, evensCount, true);
    clock_t endAsc = clock();
    double timeAsc = (double)(endAsc - startAsc) / CLOCKS_PER_SEC;

    clock_t startDesc = clock();
    bubbleSort(odds, oddsCount, false);
    clock_t endDesc = clock();
    double timeDesc = (double)(endDesc - startDesc) / CLOCKS_PER_SEC;

    int index = 0;
    for (int i = 0; i < evensCount; i++) {
        A[index] = evens[i];
        index++;
    }
    for (int i = 0; i < oddsCount; i++) {
        A[index] = odds[i];
        index++;
    }

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
	cout << A[i] << " ";
    cout << endl;

    cout << "Time for ascending sort (evens): " << fixed << setprecision(6) << timeAsc << " sec" << endl;
    cout << "Time for descending sort (odds): " << fixed << setprecision(6) << timeDesc << " sec" << endl;

    delete[] A; delete[] evens; delete[] odds;
}
void removeAndAddZeros(int* arr, int size, int X){
    int writeIndex = 0;
    int zerosCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > X) {
            arr[writeIndex] = arr[i];
            writeIndex++;
        } else {
            zerosCount++;
        }
    }
    
    for (int i = 0; i < zerosCount; i++) {
        arr[writeIndex] = 0;
        writeIndex++;
    }
}

void task2() {
    cout << "\n=== TASK 2 ===" << endl;
    int n, X;
    cout << "Enter array size n: "; cin >> n;
    cout << "Enter value X: "; cin >> X;
    
    int* A = new int[n];
    int count = 0;
    
    while (count < n) {
        int r = rand() % 100;
        bool unique = true;
        for (int i = 0; i < count; i++) {
            if (A[i] == r) unique = false;
        }
        if (unique == true) {
            A[count] = r;
            count++;
        }
    }

    cout << "Generated array: ";
    for (int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;

    removeAndAddZeros(A, n, X);

    cout << "Array after removing elements <= " << X << ":" << endl;
    for (int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
    
    delete[] A;
}

void printMatrix5x5(int mat[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << setw(4) << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void task3() {
    cout << "\n=== TASK 3 ===" << endl;
    int mat[5][5];
    int maxVal = -1;
    int maxR = 0;
    int maxC = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mat[i][j] = rand() % 100;
            if (mat[i][j] > maxVal) {
                maxVal = mat[i][j]; maxR = i; maxC = j;
            }
        }
    }
    
    cout << "Initial matrix 5x5 (Max element is " << maxVal << " at [" << maxR << "][" << maxC << "]):" << endl; 
    printMatrix5x5(mat);

    for (int j = 0; j < 5; j++) {
        int temp = mat[0][j];
        mat[0][j] = mat[maxR][j];
        mat[maxR][j] = temp;
    }
    cout << "Iteration 1 (After row swap):" << endl; 
    printMatrix5x5(mat);

    for (int i = 0; i < 5; i++) {
        int temp = mat[i][0];
        mat[i][0] = mat[i][maxC];
        mat[i][maxC] = temp;
    }
    cout << "Iteration 2 (After column swap):" << endl; 
    printMatrix5x5(mat);

}

void task4() {
    cout << "\n=== TASK 4 ===" << endl;
    int n; 
    cout << "Enter square matrix size n: "; 
    cin >> n;
    
    int rows = n;
    int cols = n;

    int** mat = new int*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            mat[i][j] = rand() % 100;
        }
    }

    cout << "Initial matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
		cout << setw(4) << mat[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = i; j < cols - 1; j++) {
            mat[i][j] = mat[i][j + 1];
        }
    }
    cols = cols - 1; 

    int maxVal = -1;
    int maxRowIndex = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] > maxVal) { 
                maxVal = mat[i][j]; 
                maxRowIndex = i; 
            }
        }
    }

    cout << "\nAfter removing diagonal. Max element is " << maxVal << " in row " << maxRowIndex << "." << endl;

    delete[] mat[maxRowIndex]; 
    for (int i = maxRowIndex; i < rows - 1; i++) {
        mat[i] = mat[i + 1];
    }
    rows = rows - 1; 

    cout << "Final matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << setw(4) << mat[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < rows; i) delete[] mat[i];
    delete[] mat;
}

int main() {
    srand(time(0));

    task1();
    task2();
    task3();
    task4();

    return 0;
}