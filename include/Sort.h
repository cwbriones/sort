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

#ifndef SORT_H_
#define SORT_H_

#include "Heap.h"
#include <string>

class SortingTester;

/*
 * TODO:
 * Selection Sort
 * Shell Sort
 * Radix Sort
 * ( and Library Sort )
 */

//==============================================================================
// Sort
//==============================================================================

class Sort {
public:
    Sort();
    Sort(std::string name);
    virtual void operator()(int* items, size_t size) = 0;

    std::string name();
    void set_tester(SortingTester* tester);
protected:
    void swap(int& a, int &b);
    int compare(int a, int b);
    SortingTester* tester_ = nullptr;
    std::string name_;
};

class QuickSort : public Sort {
public:
    QuickSort();
    virtual void operator()(int* items, size_t size);
private:
    void _quick_sort(int* items, int lo, int hi);
    size_t partition(int* items, size_t lo, size_t hi);
};

//==============================================================================
// Various Sorts
//==============================================================================

class MergeSort : public Sort {
public:
    MergeSort();
    virtual void operator()(int* items, size_t size);
private:
    void _merge(int* items, int left, int right, int* scratch);
};

class InsertionSort : public Sort {
public:
    InsertionSort();
    virtual void operator()(int* items, size_t size);
};

class BubbleSort : public Sort {
public:
    BubbleSort();
    virtual void operator()(int* items, size_t size);
};

class CocktailSort : public Sort {
public:
    CocktailSort();
    virtual void operator()(int* items, size_t size);
};

class HeapSort : public Sort {
public:
    HeapSort();
    virtual void operator()(int* items, size_t size);
};

class RadixSort : public Sort {
public:
    RadixSort();
    virtual void operator()(int* items, size_t size);
};

#endif /* SORT_H_ */
