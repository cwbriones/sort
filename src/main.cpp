#include "Sort.h"
#include "SortingTester.h"

#include <cstdlib>
#include <ctime>

//==============================================================================
// Main routine
//==============================================================================

int main(int argc, const char *argv[])
{
    SortingTester tester;
    srand(static_cast<int>(time(0)));

    // Let's add some sorts
    tester.add_sort(new BubbleSort());
    tester.add_sort(new CocktailSort());
    tester.add_sort(new MergeSort());
    tester.add_sort(new QuickSort());
    tester.add_sort(new InsertionSort());
    tester.add_sort(new HeapSort());
    tester.add_sort(new RadixSort());
    tester.set_data_range(1, 1000);

    // Let's do some tests
    tester.test_all(10000, 10);
    tester.show_results();
}
