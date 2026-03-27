///////////////////////////////////////////////////////////
//
//                 TEST PROGRAM
//
// This program demonstrates the usage of several algorithms
// and functions defined in different header files.
//
// Available Functions (sorting.h):
//   - CreateRandom
//   - RandomShuffle
//   - CheckIfSorted
//   - BubbleSort
//   - QuickSort
//	 - InsertionSort
//	 - MergeSort
//	 - BogoSort
//
// Each function is documented in detail in its corresponding
// header file.
//
// Note:
//   - This project is a work in progress.
//   - Additional functions and modules will be added in the future.
//
///////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>

#include "sorting.h"

int main()
{
	vector<int> llista;

	CreateRandom(llista, 1000000, 0, 1000000);

	cout << "Sorted? : " << CheckIfSorted(llista) << endl;
	cout << "Sorting with QuickSort..." << endl;

	auto start = chrono::high_resolution_clock::now();
	QuickSort(llista);
	auto end = chrono::high_resolution_clock::now();

	cout << "Sorted? : " << CheckIfSorted(llista) << endl;

	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

	cout << "Time elapsed: " << duration << endl;
}