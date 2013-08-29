#include "Sort.h"
#include "SortingTester.h"

//==============================================================================
// Sort
//==============================================================================

Sort::Sort() {}

Sort::Sort(std::string name) : name_(name) {}

void Sort::set_tester(SortingTester* tester) { tester_ = tester; }

std::string Sort::name() { return name_; }

void Sort::swap(int& a, int& b){
    if (tester_){
        tester_->increment_swaps();
    }
    if (a == b){
        return;
    }
    a ^= b;
    b ^= a;
    a ^= b;
}

int Sort::compare(int a, int b){
    if (tester_){
        tester_->increment_comparisons();
    }
    if (a > b){
        return 1;
    }
    else if (a < b){
        return -1;
    }
    return 0;
}

//==============================================================================
// Quicksort
//==============================================================================

QuickSort::QuickSort() : Sort("QuickSort") {}

size_t QuickSort::partition(int* items, size_t lo, size_t hi){
    int i = lo;
    int j = hi + 1;

    // Randomly choose a partition element
    int pivot = randint(lo, hi);
    // Move the pivot to the front
    swap(items[pivot], items[lo]);
    while (true){
        // Increase first pointer until elem greater than pivot
        // and second pointer until elem less than pivot
        while (items[++i] < items[lo] && i != hi);
        while (items[lo] < items[--j] && j != lo);
        if (i >= j){
            break;
        }
        // Swap the smaller item with the larger item
        swap(items[i], items[j]);
    }
    // Move the pivot back
    swap(items[lo], items[j]);
    return j;
}

void QuickSort::_quick_sort(int* items, int lo, int hi){
    if (hi <= lo){
        // Arrays of length <= 1 are sorted
        return;
    }
    // Partition the array
    int j = partition(items, lo, hi);
    // Recursively sort subarrays
    _quick_sort(items, lo, j-1);
    _quick_sort(items, j+1, hi);
}

void QuickSort::operator()(int* items, size_t size){
    _quick_sort(items, 0, size - 1);
}

//==============================================================================
// Mergesort
//==============================================================================

MergeSort::MergeSort() : Sort("MergeSort") {}

void MergeSort::_merge(int* items, int left, int right, int* scratch){
    if (right == left + 1){
        return;
    }
    int i = 0;
    int len = right - left;
    int mid = len/2;

    MergeSort::_merge(items, left, left + mid, scratch);
    MergeSort::_merge(items, left + mid, right, scratch);

    int il = left;
    int ir = left + mid;

    for (int i = 0; i < len; i++){
        if (il < left + mid && (ir == right || items[il] < items[ir])){
            scratch[i] = items[il];
            il++;
        } else {
            scratch[i] = items[ir];
            ir++;
        }
    }

    // Copy back
    for(i = left; i < right; i++){
        items[i] = scratch[i - left];
    }
}

void MergeSort::operator()(int* items, size_t size){
    int* scratch = new int[size];
    _merge(items, 0, size, scratch);
    delete scratch;

    return;
}

//==============================================================================
// Bubble-Sort and Similar
//==============================================================================

#include "SortingTester.h"

BubbleSort::BubbleSort() : Sort("BubbleSort") {}

void BubbleSort::operator()(int* items, size_t size){
    for (int i = size; i > 1; i--){
        for (int j = 1; j < i; j++){
            if (compare(items[j], items[j-1]) < 0){
                swap(items[j], items[j-1]);
            }
        }
    }
}

CocktailSort::CocktailSort() : Sort("CocktailSort") {}

void CocktailSort::operator()(int* items, size_t size){
    int left = 0;
    int right = size - 2;

    while (left < right){
        // Go up the list
        for (int i = left; i <= right; i++){
            if (items[i] > items[i + 1]){
                swap(items[i], items[i + 1]);
            }
        }
        left++;
        // Go down the list
        for (int i = right; i >= left; i--){
            if (items[i-1] > items[i]){
                swap(items[i-1], items[i]);
            }
        }
        right--;
    }
}

//==============================================================================
// Various other sorts
//==============================================================================

InsertionSort::InsertionSort() : Sort("InsertionSort") {}

void InsertionSort::operator()(int* items, size_t size){
    for (int i = 0; i < size; i++){
        int tmp = items[i];

        int j = i;
        while (--j >= 0 && items[j] > tmp){
            items[j + 1] = items[j];
        }
        items[j + 1] = tmp;
    }
}
