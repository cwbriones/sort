/*
 * Copyright (C) 2013 Christian Briones
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
        while (compare(items[++i], items[lo]) < 0 && i != hi);
        while (compare(items[lo], items[--j]) < 0 && j != lo);
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
        // Base case
        return;
    }
    int i = 0;
    int len = right - left;
    int mid = len/2;

    // Recurse
    _merge(items, left, left + mid, scratch);
    _merge(items, left + mid, right, scratch);

    int il = left;
    int ir = left + mid;

    // Each half is now sorted. We merge.
    for (int i = 0; i < len; i++){
        if (il < left + mid && (ir == right || (compare(items[il], items[ir]) < 0))){
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
    // Only a single array allocation is necessary
    int* scratch = new int[size];
    _merge(items, 0, size, scratch);
    delete scratch;

    return;
}

//==============================================================================
// Bubble sort
//==============================================================================

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

//==============================================================================
// Cocktail sort
//==============================================================================

CocktailSort::CocktailSort() : Sort("CocktailSort") {}

void CocktailSort::operator()(int* items, size_t size){
    int left = 0;
    int right = size - 2;

    while (left < right){
        // Go up the list
        for (int i = left; i <= right; i++){
            if (compare(items[i], items[i + 1]) > 0){
                swap(items[i], items[i + 1]);
            }
        }
        left++;
        // Go down the list
        for (int i = right; i >= left; i--){
            if (compare(items[i-1], items[i]) > 0 ){
                swap(items[i-1], items[i]);
            }
        }
        right--;
    }
}

//==============================================================================
// Insertion sort
//==============================================================================

InsertionSort::InsertionSort() : Sort("InsertionSort") {}

void InsertionSort::operator()(int* items, size_t size){
    for (int i = 0; i < size; i++){
        int tmp = items[i];

        int j = i;
        while (--j >= 0 && compare(items[j], tmp) > 0){
            items[j + 1] = items[j];
            // Essentially we are swapping each element above
            // the inserted position up one space
            if (tester_){
                tester_->increment_swaps();
            }
        }
        items[j + 1] = tmp;
    }
}

//==============================================================================
// Heapsort
//==============================================================================

HeapSort::HeapSort() : Sort("HeapSort") {}

void HeapSort::operator()(int* items, size_t size){

    // Create the heap
    MinHeap<int> heap(items, size);

    // Pop off the heap and populate the array
    int i = 0;
    while (!heap.is_empty()){
        items[i++] = heap.pop_min();
    }
}

//==============================================================================
// Radix Sort
//==============================================================================

#include <vector>
#include <list>

RadixSort::RadixSort() : Sort("RadixSort") {}

void RadixSort::operator()(int * items, size_t size){
    if (size <= 1){
        return;
    }
    // Base of the modulo operation
    int m = 10;
    int n = 1;

    std::vector< std::list<int> > buckets(10);

    // Find the largest item
    int max = items[0];
    for (int i = 1; i < size; i++){
        if (items[i] > max){
            max = items[i];
        }
    }

    while (n < max){
        // Move into respective list
        for (int i = 0; i < size; i++){
            int j = (items[i] % m) / n;
            buckets[j].push_back(items[i]);
        }
        // Pop off and copy back into array
        int k = 0;
        for (int i = 0; i < 10; i++){
            while (!buckets[i].empty()){
                int top = buckets[i].front();
                buckets[i].pop_front();

                items[k++] = top;
            }
        }
        // Iterate
        m *= 10;
        n *= 10;
    }
}
