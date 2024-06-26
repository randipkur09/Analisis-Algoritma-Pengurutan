#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

void bubbleSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < n1)
        arr[k++] = left[i++];

    while (j < n2)
        arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

template <typename Func>
void measureExecutionTime(Func func, vector<int>& arr, int n, const string& name) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n); 
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << name << " memerlukan waktu " << duration.count() << " microseconds" << endl;
}

template <typename Func>
void measureExecutionTime2(Func func, vector<int>& arr, int low, int high, const string& name) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, low, high); 
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << name << " memerlukan waktu " << duration.count() << " microseconds" << endl;
}

void randomDataGenerator(vector<int>& arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 10000);
    }
}

void sortedDataGenerator(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr.push_back(i);
    }
}

void reverseSortedDataGenerator(vector<int>& arr, int n) {
    for (int i = n - 1; i >= 0; i--) {
        arr.push_back(i);
    }
}

int main() {
    vector<int> arrSizes = {10, 50, 100, 500, 1000, 10000};

    for (int n : arrSizes) {
        vector<int> randomData, sortedData, reverseSortedData;

        randomDataGenerator(randomData, n);
        sortedDataGenerator(sortedData, n);
        reverseSortedDataGenerator(reverseSortedData, n);

        cout << "For n = " << n << ":" << endl;

        // Bubble Sort
        measureExecutionTime(bubbleSort, randomData, n, "Bubble Sort (Acak)");
        measureExecutionTime(bubbleSort, sortedData, n, "Bubble Sort (Terurut)");
        measureExecutionTime(bubbleSort, reverseSortedData, n, "Bubble Sort (Terurut Terbalik)");

        // Insertion Sort
        measureExecutionTime(insertionSort, randomData, n, "Insertion Sort (Acak)");
        measureExecutionTime(insertionSort, sortedData, n, "Insertion Sort (Terurut)");
        measureExecutionTime(insertionSort, reverseSortedData, n, "Insertion Sort (Terurut Terbalik)");

        // Selection Sort
        measureExecutionTime(selectionSort, randomData, n, "Selection Sort (Acak)");
        measureExecutionTime(selectionSort, sortedData, n, "Selection Sort (Terurut)");
        measureExecutionTime(selectionSort, reverseSortedData, n, "Selection Sort (Terurut Terbalik)");

        // Quick Sort
        measureExecutionTime2(quickSort, randomData, 0, n - 1, "Quick Sort (Acak)");
        measureExecutionTime2(quickSort, sortedData, 0, n - 1, "Quick Sort (Terurut)");
        measureExecutionTime2(quickSort, reverseSortedData, 0, n - 1, "Quick Sort (Terurut Terbalik)");

        // Merge Sort
        measureExecutionTime2(mergeSort, randomData, 0, n - 1, "Merge Sort (Acak)");
        measureExecutionTime2(mergeSort, sortedData, 0, n - 1, "Merge Sort (Terurut)");
        measureExecutionTime2(mergeSort, reverseSortedData, 0, n - 1, "Merge Sort (Terurut Terbalik)");

        cout << endl;
    }

    return 0;
}
