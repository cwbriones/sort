#include <iostream>
#include <cstdlib>
// #include <utility>
// #include <random>

/*
 * TODO:
 * Insertion Sort
 * Bubble Sort
 * Merge Sort
 * Quick Sort
 * Cocktail Shaker sort
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
void shuffle(T* items, size_t size){
    for (int i = size - 1; i > 0; i--){
        int j = rand() % i;
        swap(items[i], items[j]);
    }
    return;
}

// template <>
// void shuffle(int* items, size_t size){
//     for (int i = size - 1; i > 0; i--){
//         int j = rand() % i;
//         items[i] = items[i] ^ items[j];
//         items[j] = items[i] ^ items[j];
//         items[i] = items[i] ^ items[j];
//     }
//     return;
// }

int main(int argc, const char *argv[])
{
    const int size = 10;
    int nums[size];
    for (int i = 0; i < size; i++){
        nums[i] = i + 1;
    }
    shuffle(nums, size);
    for (auto x : nums){
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    bubble_sort(nums, size);
    for (auto x : nums){
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    return 0;
}
