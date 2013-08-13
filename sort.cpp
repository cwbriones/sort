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
void shuffle(T* items, size_t size){
    for (int i = size - 1; i > 0; i--){
        int j = rand() % i;

        //Swap
        T tmp = items[i];
        items[i] = items[j];
        items[j] = tmp;
    }
    return;
}

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

    return 0;
}
