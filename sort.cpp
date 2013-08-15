#include <iostream>
#include <cstdlib>
// #include <utility>
// #include <random>

/*
 * TODO:
 * Selection Sort
 * Heap Sort
 * Shell Sort
 * Radix Sort
 * Insertion Sort
 * ( and Library Sort )
 */

/*
 * Function randint:
 * Generates a uniformly distributed integer
 * between the values and b inclusive
 */
int randint(int a, int b){
    int N = b - a + 1;
    int r;
    do {
        r = rand();
    } while (r >= RAND_MAX - N && r >= N);
    return a + (r % N);
}

template <class T>
void swap(T& a, T& b){
    if (a == b){
        return;
    }
    T tmp = a;
    a = b;
    b = tmp;
}

template <> // void swap(int& a, int& b){ //     a = a ^ b;
void swap(int& a, int& b){
    if (a == b){
        // otherwise will turn both entries into 0s
        return;
    }
    a ^= b;
    b ^= a;
    a ^= b;
}

template <class T>
void shuffle(T* items, size_t size){
    for (int i = size - 1; i > 0; i--){
        int j = rand() % i;
        swap(items[i], items[j]);
    }
    return;
}

template <class T>
size_t partition(T* items, size_t lo, size_t hi){
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

template <class T>
void quick_sort(T* items, int lo, int hi){
    if (hi <= lo){
        // Arrays of length <= 1 are sorted
        return;
    }
    // Partition the array
    int j = partition(items, lo, hi);
    // Recursively sort subarrays
    quick_sort(items, lo, j-1);
    quick_sort(items, j+1, hi);
}

template <class T>
void quick_sort(T* items, size_t size){
    quick_sort(items, 0, size - 1);
}

template <class T>
void merge(T* items, int left, int right, T* scratch){
    if (right == left + 1){
        return;
    }
    int i = 0;
    int len = right - left;
    int mid = len/2;

    merge(items, left, left + mid, scratch);
    merge(items, left + mid, right, scratch);

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

template <class T>
void merge_sort(T* items, size_t size){
    T* scratch = new T[size];
    merge(items, 0, size, scratch);
    delete scratch;

    return;
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
bool is_sorted(T* items, size_t size){
    for (int i = 0; i < size - 1; i++){
        if (items[i] > items[i + 1]){
            return false;
        }
    }
    return true;
}

int main(int argc, const char *argv[])
{
    const int size = 50;
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
