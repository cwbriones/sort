#include <iostream>
#include <cstdlib>
#include <cassert>
#include <chrono>
#include <ctime>
// #include <utility>
// #include <random>

/*
 * TODO:
 * Selection Sort
 * Shell Sort
 * Radix Sort
 * ( and Library Sort )
 */

//==============================================================================
// Utility Functions
//==============================================================================

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

void shuffle(int* items, size_t size){
    for (int i = size - 1; i > 0; i--){
        int j = rand() % i;
        swap(items[i], items[j]);
    }
    return;
}

void TEST_print_check();

bool assert_sorted(int* items, size_t size){
    TEST_print_check();
    for (int i = 0; i < size - 1; i++){
        assert(items[i] <= items[i+1]);
    }
    return true;
}

template <class Iterator>
void print_iterable(Iterator start, Iterator end){
    for (Iterator iter = start; iter != end; ++iter){
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

//==============================================================================
// Quicksort
//==============================================================================

size_t partition(int* items, size_t lo, size_t hi){
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

void quick_sort(int* items, int lo, int hi){
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

void quick_sort(int* items, size_t size){
    quick_sort(items, 0, size - 1);
}

//==============================================================================
// Mergesort
//==============================================================================

void merge(int* items, int left, int right, int* scratch){
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

void merge_sort(int* items, size_t size){
    int* scratch = new int[size];
    merge(items, 0, size, scratch);
    delete scratch;

    return;
}

//==============================================================================
// Bubble-Sort and Similar
//==============================================================================


void bubble_sort(int* items, size_t size){
    for (int i = size; i > 1; i--){
        for (int j = 1; j < i; j++){
            if (items[j] < items[j-1]){
                swap(items[j], items[j-1]);
            }
        }
    }
}

void cocktail_sort(int* items, size_t size){
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

void insertion_sort(int* items, size_t size){
    for (int i = 0; i < size; i++){
        int tmp = items[i];

        int j = i;
        while (--j >= 0 && items[j] > tmp){
            items[j + 1] = items[j];
        }
        items[j + 1] = tmp;
    }
}


//==============================================================================
// Tests
//==============================================================================

using std::chrono::high_resolution_clock;

void TEST_sort_sorted(const int size){
    int nums[size];

    for (int i = 0; i < size; i++){
        nums[i] = size + 1;
    }
    insertion_sort(nums, size);
    assert_sorted(nums, size);

    merge_sort(nums, size);
    assert_sorted(nums, size);

    quick_sort(nums, size);
    assert_sorted(nums, size);

    bubble_sort(nums, size);
    assert_sorted(nums, size);

    cocktail_sort(nums, size);
    assert_sorted(nums, size);
}

void TEST_print_start(const char* sort, int size){
    std::cout << "Beginning " << sort << "sort with " << size << " items." << std::endl;
}

void TEST_print_check(){
    std::cout << "Verifying that items are sorted." << std::endl;
}

void TEST_print_log(const char* sort, int time, int size){
    std::cout << sort << "sort: Sorted " << size << " items in " 
              << time << " ms" << std::endl << std::endl;
}

int get_ms_duration(const high_resolution_clock::time_point& time){
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            time.time_since_epoch()
            ).count();
}

void TEST_sort_specified_size(const int size){
    int nums[size];

    for (int i = 0; i < size; i++){
        nums[i] = i + 1;
    }
    shuffle(nums, size);

    // TEST_print_start("Bubble", size);
    high_resolution_clock::time_point start = high_resolution_clock::now();
    // bubble_sort(nums, size);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    // assert_sorted(nums, size);
    int time = get_ms_duration(end) - get_ms_duration(start);
    // TEST_print_log("Bubble", time, size);

    // shuffle(nums, size);

    // TEST_print_start("Cocktail", size);
    // start = high_resolution_clock::now();
    // cocktail_sort(nums, size);
    // end = high_resolution_clock::now();
    // assert_sorted(nums, size);
    // time = get_ms_duration(end) - get_ms_duration(start);
    // TEST_print_log("Cocktail", time, size);

    shuffle(nums, size);

    TEST_print_start("Insertion", size);
    start = high_resolution_clock::now();
    insertion_sort(nums, size);
    end = high_resolution_clock::now();
    assert_sorted(nums, size);
    time = get_ms_duration(end) - get_ms_duration(start);
    TEST_print_log("Insertion", time, size);

    shuffle(nums, size);

    TEST_print_start("Merge", size);
    start = high_resolution_clock::now();
    merge_sort(nums, size);
    end = high_resolution_clock::now();
    assert_sorted(nums, size);
    time = get_ms_duration(end) - get_ms_duration(start);
    TEST_print_log("Merge", time, size);

    shuffle(nums, size);

    TEST_print_start("Quick", size);
    start = high_resolution_clock::now();
    quick_sort(nums, size);
    end = high_resolution_clock::now();
    assert_sorted(nums, size);
    time = get_ms_duration(end) - get_ms_duration(start);
    TEST_print_log("Quick", time, size);
}

//==============================================================================
// Main routine
//==============================================================================


int main(int argc, const char *argv[])
{
    TEST_sort_specified_size(1000000);
}
