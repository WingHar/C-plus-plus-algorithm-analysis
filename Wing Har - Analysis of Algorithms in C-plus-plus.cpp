/*

Wing Har - CSC382 - Lab 4

*/

// Chrono for time
#include <chrono>
// Input output
#include <iostream>
// Vector arrays instead of static
#include<vector>
// Manipulate output to make it look good
#include <iomanip>

using namespace std;
// Need namespace standard chrono for chrono library - time.
// Could substitute for ctime.
using namespace std::chrono;

/* 

******* MERGE SORT ********
Reference: https://www.geeksforgeeks.org/merge-sort/

*/

/*
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create two temporary arrays
    int LARR[n1], RARR[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        LARR[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        RARR[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {
        if (LARR[i] <= RARR[j])
        {
            arr[k] = LARR[i];
            i++;
        }
        else
        {
            arr[k] = RARR[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = LARR[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = RARR[j];
        j++;
        k++;
    }
}

*/

/*

******* INSERTION SORT ********
Reference: https://www.geeksforgeeks.org/insertion-sort/

*/

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

    // Move value to space before.
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/*

// Call Merge Sort to check if the arrays are merged or not.
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

*/

/*

******* HEAP SORT ********
Reference: https://www.geeksforgeeks.org/heap-sort/

*/

// Heapify the array

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // Defining two child as left = 2*i + 1
    int r = 2 * i + 2; // and right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree and create
        heapify(arr, n, largest);
    }
}

// Heap Sort

void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Print the arrays
void printArray(int Array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << Array[i] << " ";
}

int main()
{
    // INPUT LENGTH
    int n[] = { 1000,10000,25000,50000,150000,250000 };
    cout << "Input Length\tHeap Sort (Seconds) \tInsertion Sort (Seconds) \tMerge Sort (Seconds) \tBest Time\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    // Set the time to 0
    srand(time(0));

    for (int i = 0; i < 6; i++)
    {
        int nn = n[i];
        int hp = new int[nn];
        int ins = new int[nn];
        int mrg = new int[nn];

        for (int i = 0; i < nn; i++)
        {
            // While the array is still going, generate random values into it.
            int t = rand();
            // Copy the random values into all 3 arrays at the same spots.
            hp[i] = ins[i] = mrg[i] = t;
        }

        // CHRONO
        // Reference: https://en.cppreference.com/w/cpp/chrono
        // High resolution clock - shortest tick period to get max accuracy
        // Start clock with auto start and now().
        // End clock with auto end and now().
        auto start = high_resolution_clock::now();
        heapSort(hp, nn);
        auto stop = high_resolution_clock::now();
        auto hd = duration_cast<microseconds>(stop - start);
        start = high_resolution_clock::now();
        insertionSort(ins, nn);
        stop = high_resolution_clock::now();
        auto id = duration_cast<microseconds>(stop - start);
        start = high_resolution_clock::now();
        stop = high_resolution_clock::now();
        auto md = duration_cast<microseconds>(stop - start);
        double t1 = hd.count() / (double)1000000; //heapsort time taken
        double t2 = id.count() / (double)1000000; //insertion sort time taken
        double t3 = md.count() / (double)1000000; //merge sort time taken
        string bestTime;

        /*
        
        Check for which is the best time for each iteration.
        
        */

        // t1 = Heap
        // t2 = Insertion
        // t3 = Merge
        if (t1 < t2 && t1 < t3)
        {
            // Return heap as the best time
            bestTime = "Heap";
        }
        else if (t2 < t3 && t2 < t1)
        {
            // Return insertion sort as the best time
            bestTime = "Insertion";
        }
        else
        {
            // Return merge sort as the best time
            bestTime = "Merge";
        }
        cout << fixed << setprecision(2) << nn << " \t\t " << t1 << "\t\t" << t2 << "\t\t" << t3 << "\t\t" << bestTime << endl;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}