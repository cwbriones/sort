#include <iostream>
#include <cstdlib>
// #include <utility>
// #include <random>

/*
 * TODO:
 * Insertion Sort
 * Merge Sort
 * Quick Sort
 */
template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

template <>
void swap(int& a, int& b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

template <class T>
void bubble_sort(T* items, size_t size){
    for (int i = size; i > 1; i--){
        for (int j = 1; j < i; j++){
            if (items[j] < items[j-1]){
                swap(items[j], items[j-1]);
            }
        }
    }
}

template <class T>
void cocktail_sort(T* items, size_t size){
    int left = 0;
    int right = size - 2;

    bool swapped = true;
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

template <class T>
void shuffle(T* items, size_t size){
    for (int i = size - 1; i > 0; i--){
        int j = rand() % i;
        swap(items[i], items[j]);
    }
    return;
}

int main(int argc, const char *argv[])
{
    const int size = 100;
    int nums[size];
    for (int i = 0; i < size; i++){
        nums[i] = i + 1;
    }
    shuffle(nums, size);
    cocktail_sort(nums, size);
    for (auto x : nums){
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    return 0;
}
