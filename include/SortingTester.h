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

#ifndef SORTING_TESTER_H_
#define SORTING_TESTER_H_

#include "Sort.h"
#include "Base.h"

#include <map>
#include <chrono>

template <class Iterator>
void print_iterable(Iterator start, Iterator end){
    for (Iterator i = start; i != end; ++i){
        std::cout << *i << ' ';
    }
    std::cout << std::endl;
}


unsigned int randint(int start, int end);

struct SortingTestResult {
    int time_ms;
    int comparisons;
    int swaps;
};

class SortingTestSummary {
public:
    SortingTestSummary(std::string sort_name);
    void summarize();
    void clear();
    void add_result(int test_size, int time, int comparisons, int swaps);
private:
    std::string sort_name_;
    std::map<int, std::vector<SortingTestResult> > results_;
};

class SortingTester {
    public:
        SortingTester();
        ~SortingTester();
        void add_sort(Sort* sort);
        void test_all(int size, int num_tests, bool partial_sort = false);

        void increment_swaps(){ ++swap_count; }
        void increment_comparisons(){ ++comparisons; }
        void clear_results();
        void show_results();

        void set_data_range(int a, int b);
    private:
        int range_start, range_end;
        void initialize_contents(int size);

        void shuffle_contents();
        void print_test_start();
        void print_check();
        bool check_sorted();
        int get_ms_duration(const std::chrono::high_resolution_clock::time_point& time);
        void start_timer();
        int stop_timer();
        void reset_test();

        int swap_count = 0;
        int comparisons = 0;
        std::chrono::high_resolution_clock::time_point start;

        std::vector<Sort*> sorters_;
        std::vector<SortingTestSummary> summaries_;

        int* data_ = nullptr;
        int test_size = 0;

        std::string cur_sort = "UNDEFINED";
};

#endif /* SORTING_TESTER_H_ */
