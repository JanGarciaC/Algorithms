#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

using namespace std;

////////////// CREATERANDOM IMPLEMENTATION //////////////
//
// Generates a vector of random values.
//
// This function initializes (or resets) a vector and fills
// it with a specified number (size) of randomly generated 
// elements within a given range [min, max].
//
// It supports both integral and floating-point types by
// selecting the appropriate random distribution.
//
// Time Complexity:
//   - O(N)
//
// Space Complexity:
//   - O(1) additional (modifies the vector in-place)
//
// Notes:
//   - Existing contents of the vector are cleared
//   - Uses Mersenne Twister (mt19937) for randomness
//
//////////////////////////////////////////////////////////
template <typename T>
void CreateRandom(vector<T>& list, size_t size, T min, T max)
{
    static random_device rd;
    static mt19937 gen(rd());

    list.clear();
    list.reserve(size);

    if constexpr (is_integral<T>::value) 
    {
        uniform_int_distribution<T> dist(min, max);
        for (size_t i = 0; i < size; ++i) 
        {
            list.push_back(dist(gen));
        }
    }
    else {
        uniform_real_distribution<T> dist(min, max);
        for (size_t i = 0; i < size; ++i) 
        {
            list.push_back(dist(gen));
        }
    }
}

////////////// RANDOMSHUFFLE IMPLEMENTATION //////////////
//
//              Random Shuffle Algorithm
//
// This function randomly permutes the elements of a vector
// using a uniform distribution.
//
// It relies on std::shuffle, which implements an efficient
// version of the Fisher–Yates shuffle algorithm.
//
// Time Complexity:
//   - O(N)
//
// Space Complexity:
//   - O(1)
//
// Notes:
//   - Produces a uniform random permutation
//   - Uses Mersenne Twister (mt19937) for randomness
//
//////////////////////////////////////////////////////////
template <typename T>
void RandomShuffle(vector<T>& list) 
{
    static random_device rd;
    static mt19937 gen(rd());

    shuffle(list.begin(), list.end(), gen);
}

////////////// CHECKIFSORTED IMPLEMENTATION //////////////
//
// Check If Sorted Function
//
// This function verifies whether a vector is sorted in
// ascending order.
//
// It iterates through the vector and compares each element
// with its successor. If any pair is found out of order,
// the function immediately returns false.
//
// Time Complexity:
//   - O(N)
//
// Space Complexity:
//   - O(1)
//
// Notes:
//   - Early exit improves performance in unsorted cases
//   - Assumes operator '>' is defined for type T
//
//////////////////////////////////////////////////////////
template <typename T>
bool CheckIfSorted(const vector<T>& list)
{
    for (int i = 0; i < list.size() - 1; i++)
        if (list[i] > list[i+1])
            return false;
	return true;
}

////////////// BUBBLESORT IMPLEMENTATION //////////////
//
//                Bubble Sort Algorithm
//
// This function sorts a vector using the Bubble Sort method.
// The algorithm repeatedly traverses the list, comparing
// adjacent elements and swapping them if they are in the
// wrong order.
//
// After each pass, the largest unsorted element "bubbles up"
// to its correct position at the end of the vector. This
// process is repeated until the entire vector is sorted.
//
// Time Complexity:
//   - Worst case: O(N^2)
//   - Average case: O(N^2)
//
// Space Complexity:
//   - O(1) (in-place sorting, no extra memory required)
//
///////////////////////////////////////////////////////
template <typename T>
void BubbleSort(vector<T>& list)
{
    if (CheckIfSorted(list))
        return;

	for (int i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < list.size() - i - 1; j++)
		{
			if (list[j] > list[j + 1])
			{
                swap(list[j], list[j + 1]);
			}
		}
	}
}


////////////// QUICKSORT IMPLEMENTATION //////////////
//
//                Quick Sort Algorithm
//
// This function sorts a vector using the Quick Sort method
//
// The algorithm works by selecting a pivot element (in this
// case, randomly chosen), and partitioning the vector into
// two subarrays:
//   - Elements smaller than or equal to the pivot
//   - Elements greater than the pivot
//
// The process is then recursively applied to the subarrays
// until the entire vector is sorted.
//
// The use of a random pivot helps reduce the probability
// of encountering the worst-case scenario.
//
// Time Complexity:
//   - Worst case: O(N^2)
//   - Average case: O(N log N)
//
// Space Complexity:
//   - Worst case: O(N)
//   - Average case: O(log N) 
//
// Notes:
//   - In-place sorting (no additional data structures used)
//
///////////////////////////////////////////////////////
template <typename T>
void QuickSortRec(vector<T>& list, int low, int high)
{
    if (low < high)
    {
        int randomIndex = low + rand() % (high - low + 1);
        swap(list[randomIndex], list[high]);

        T pivot = list[high];
        int i = low;

        for (int j = low; j < high; j++)
        {
            if (list[j] <= pivot)
            {
                swap(list[i], list[j]);
                i++;
            }
        }
        swap(list[i], list[high]);
        QuickSortRec(list, low, i - 1);
        QuickSortRec(list, i + 1, high);
    }
}

template <typename T>
void QuickSort(vector<T>& list)
{
    if (CheckIfSorted(list))
        return;

	QuickSortRec(list, 0, list.size() - 1);
}

////////////// BOGOSORT IMPLEMENTATION //////////////
//
//                Bogo Sort Algorithm
//
// This is a highly inefficient but funny sorting algorithm. 
// It repeatedly shuffles the vector until it becomes sorted.
//
// Time Complexity:
//   - O(N!)
//
// Space Complexity:
//   - O(1) (in-place shuffling)
//
// Notes:
//   - Not suitable for large vectors
//   - Uses RandomShuffle function for shuffling
//
///////////////////////////////////////////////////////
template <typename T>
void BogoSort(vector<T>& list)
{
    while (!CheckIfSorted(list))
    {
        RandomShuffle(list);
    }
}

////////////// INSERTIONSORT IMPLEMENTATION //////////////
//
//                Insertion Sort Algorithm
//
// This function sorts a vector using the Insertion Sort method.
// It builds the sorted array one element at a time by
// repeatedly taking the next unsorted element and inserting
// it into the correct position.
//
// Time Complexity:
//   - Worst case: O(N^2)
//   - Best case (already sorted): O(N)
//
// Space Complexity:
//   - O(1) (in-place)
// 
///////////////////////////////////////////////////////
template <typename T>
void InsertionSort(vector<T>& list)
{
    for (int i = 1; i < list.size(); i++)
    {
        T key = list[i];
        int j = i - 1;

        while (j >= 0 && list[j] > key)
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

////////////// MERGESORT IMPLEMENTATION //////////////
//
//                Merge Sort Algorithm
//
// This function sorts a vector using the Merge Sort method.
// It recursively divides the vector into halves, sorts each
// half, and then merges them into a single sorted array.
//
// Time Complexity:
//   - Worst case: O(N log N)
//   - Average case: O(N log N)
//
// Space Complexity:
//   - O(N) additional space for merging
//
// Notes:
//   - Stable sort
//
///////////////////////////////////////////////////////
template <typename T>
void Merge(vector<T>& list, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = list[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = list[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            list[k++] = L[i++];
        else
            list[k++] = R[j++];
    }

    while (i < n1)
        list[k++] = L[i++];
    while (j < n2)
        list[k++] = R[j++];
}

template <typename T>
void MergeSortRec(vector<T>& list, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        MergeSortRec(list, left, mid);
        MergeSortRec(list, mid + 1, right);
        Merge(list, left, mid, right);
    }
}

template <typename T>
void MergeSort(vector<T>& list)
{
    if (CheckIfSorted(list))
        return;

    MergeSortRec(list, 0, list.size() - 1);
}

////////////// BINARYSEARCH IMPLEMENTATION //////////////
//
//               Binary Search Algorithm
//
// Searches a vector looking for specified element. Returns
// element index or -1 if element not found.
//
// Time Complexity:
//   - O(log N)
//
// Space Complexity:
//   - O(1)
//
// Notes:
//   - Only works on sorted vectors
//
////////////////////////////////////////////////////////
template <typename T>
int binarySearch(vector<T>& list, T element)
{
    int min = 0, max = list.size() - 1;
    int i = (max + min) / 2;

    while (list[i] != element)
    {
        if (element < list[i])
            max = i;
        else
            min = i;

        i = (max + min) / 2;

        if (min == max || i == min || i == max)
            return -1;
    }

    return i;
}