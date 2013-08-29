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

#endif /* SORT_H_ */
