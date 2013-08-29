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

    tester.add_sort(new BubbleSort());
    tester.test_all(1000, 10);
}
