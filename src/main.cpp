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
    tester.add_sort(new RadixSort());
    tester.add_sort(new HeapSort());
    
    // Generate uniformly distributed integers in
    // the interval [1, 1000] as our test data
    tester.set_data_range(1, 1000);

    // Let's do some tests
    // Each algorithm will sort sets of 10 000 integers 10 times
    tester.test_all(10000, 10);
    tester.show_results();
}
