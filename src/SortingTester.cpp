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

//==============================================================================
// Utility Functions
//==============================================================================

unsigned int randint(int start, int end){
    // Remove modulo bias by finding the maximum value
    // and discarding those above it

    int N = end - start;
    int MAX_VAL = RAND_MAX - ((RAND_MAX % N) + 1);

    int x;
    while ((x = rand()) > MAX_VAL);

    return x % N + start;
}

//==============================================================================
// SortingTestResult and SortingTestSummary
//==============================================================================

#include <iomanip>

SortingTestSummary::SortingTestSummary(std::string sort_name) :
    sort_name_(sort_name) {}

void SortingTestSummary::add_result(int test_size, int time, int comparisons, int swaps){
    SortingTestResult result;

    result.comparisons = comparisons;
    result.swaps = swaps;
    result.time_ms = time;

    results_[test_size].push_back(result);
}

void SortingTestSummary::clear(){
    results_.clear();
}

void SortingTestSummary::summarize(){

    std::map<int, double> average_comparisons;
    std::map<int, double> average_times;
    std::map<int, double> average_swaps;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Performance Summary. Sort: " << sort_name_ << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    for (auto& tests : results_){
        int test_size = tests.first;

        SortingTestResult total;

        total.time_ms = 0;
        total.comparisons = 0;
        total.swaps = 0;

        int num_tests = tests.second.size();

        for (auto& result : tests.second){
            // These are all results of a single size
            // Do work here
            total.time_ms += result.time_ms;
            total.comparisons += result.comparisons;
            total.swaps += result.swaps;
        }

        float avg_time_ms = static_cast<float>(total.time_ms)/num_tests;
        float avg_comparisons = static_cast<float>(total.comparisons)/num_tests;
        float avg_swaps = static_cast<float>(total.swaps)/num_tests;

        std::cout << "Statistics for sorting N = " << test_size << " items." << std::endl;

        std::cout << "Total # of Tests: " << 
            std::setw(10) << std::right << num_tests << std::endl;
        std::cout << "Average Time (ms): " << 
            std::setw(10) << std::right << avg_time_ms << std::endl;
        std::cout << "Average # of Comparisons: " <<
            std::setw(10) << std::right << avg_comparisons << std::endl;
        std::cout << "Average # of Swaps: " << 
            std::setw(10) << std::right << avg_swaps << std::endl;
    }
}

//==============================================================================
// SortingTester
//==============================================================================

//Public Methods
//------------------------------------------------------------------------------


SortingTester::SortingTester(){
    range_start = 0;
    range_end = 0;
}

SortingTester::~SortingTester(){
    if (data_){
        delete[] data_;
    }
    while (!sorters_.empty()){
        delete sorters_.back();
        sorters_.pop_back();
    }
}

void SortingTester::add_sort(Sort* sort){
    sorters_.push_back(sort);
    sorters_.back()->set_tester(this);
}

void SortingTester::test_all(int size, int num_tests, bool partial_sort){
    std::cout << "Initializing contents.\n" << std::endl;
    initialize_contents(size);

    if (!data_){
        std::cout << "ERROR: Data uninitialized." << std::endl;
        std::cout << "Stopping tests." << std::endl;
        return;
    }

    std::cout << "Beginning Tests." << std::endl;
    for (auto& sort : sorters_){
        // Test each sort
        cur_sort = sort->name();

        std::cout << "Testing " << cur_sort << std::endl;

        SortingTestSummary summary(cur_sort);

        for (int i = 0; i < num_tests; i++){
            shuffle_contents();
            start_timer();
            sort->operator()(data_, size);
            int time_ms = stop_timer();

            if (!check_sorted()){
                std::cout << "ERROR: TEST FAILED!" << std::endl;
            }

            summary.add_result(size, time_ms, comparisons, swap_count);
            reset_test();
        }

        summaries_.push_back(summary);
    }
}

void SortingTester::set_data_range(int a, int b){
    if (b < a){
        int tmp = b;
        b = a;
        a = tmp;
    }

    range_start = a;
    range_end = b;
}

void SortingTester::initialize_contents(int size){
    if (data_){
        delete[] data_;
    }
    data_ = new int[size];

    if (range_start == range_end && range_end == 0){
        for (int i = 0; i < size; i++){
            data_[i] = i + 1;
        }
    } else {
        for (int i = 0; i < size; i++){
            data_[i] = randint(range_start, range_end);
        }
    }

    test_size = size;
}

void SortingTester::clear_results(){
    summaries_.clear();
}

void SortingTester::show_results(){
    std::cout << "\n\nTest Summaries" << std::endl;

    for (auto& summary : summaries_){
        summary.summarize();
    }
}

// Private Methods
//------------------------------------------------------------------------------

void SortingTester::shuffle_contents(){
    for (int i = 0; i < test_size - 1; i++){
        int j = randint(i, test_size - 1);

        int tmp = data_[i];
        data_[i] = data_[j];
        data_[j] = tmp;
    }
    swap_count = 0;
}

void SortingTester::print_check(){
    std::cout << cur_sort << ": Verifying that items are sorted." << std::endl;
}

bool SortingTester::check_sorted(){
    for (int i = 1; i < test_size; i++){
        if (data_[i] < data_[i-1]){
            // There is an error here
            return false;
        }
    }
    return true;
}

int SortingTester::get_ms_duration(const std::chrono::high_resolution_clock::time_point& time){
    return 
        std::chrono::duration_cast<std::chrono::milliseconds>(
                time.time_since_epoch()
            ).count();
}

void SortingTester::start_timer(){
    start = std::chrono::high_resolution_clock::now();
}

int SortingTester::stop_timer(){
    std::chrono::high_resolution_clock::time_point now = 
        std::chrono::high_resolution_clock::now();
    int elapsed = get_ms_duration(now) - get_ms_duration(start);

    return elapsed;
}
void SortingTester::reset_test(){
    swap_count = 0;
    comparisons = 0;
}
