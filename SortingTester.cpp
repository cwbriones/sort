#include "Sort.h"
#include "SortingTester.h"

//==============================================================================
// Utility Functions
//==============================================================================

unsigned int randint(int start, int end){
    int N = end - start;
    int MAX_VAL = RAND_MAX - N;

    int x;

    while ((x = rand()) < MAX_VAL);

    return x % N + start;
}

//==============================================================================
// SortingTestResult and SortingTestSummary
//==============================================================================

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

    std::cout << "Sort: " << sort_name_ << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    for (auto& tests : results_){
        int test_size = tests.first;

        std::cout << "Results for " << test_size << " tests." << std::endl;

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
        std::cout << "Total # of Tests: \t" << num_tests << std::endl;
        std::cout << "Time (ms): \t" << avg_time_ms << std::endl;
        std::cout << "Comparisons: \t" << avg_comparisons << std::endl;
        std::cout << "Swaps: \t" << avg_swaps << std::endl;
    }
}

//==============================================================================
// SortingTester
//==============================================================================

//Public Methods
//------------------------------------------------------------------------------


SortingTester::SortingTester(){}

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
    initialize_contents(size);

    for (auto& sort : sorters_){
        // Test each sort
        SortingTestSummary summary(sort->name());
        print_test_start();

        for (int i = 0; i < num_tests; i++){
            shuffle_contents();

            start_timer();
            (*sort)(data_, test_size);
            int time_ms = stop_timer();
            check_sorted();

            summary.add_result(size, time_ms, comparisons, swap_count);
            reset_test();
        }

        summaries_.push_back(summary);
    }

    show_results();
}

void SortingTester::initialize_contents(int size){
    if (data_){
        delete[] data_;
    }
    data_ = new int[size];
    for (int i = 0; i < size; i++){
        data_[i] = i;
    }
    test_size = size;
}

void SortingTester::clear_results(){
    summaries_.clear();
}

void SortingTester::show_results(){
    for (auto& summary : summaries_){
        summary.summarize();
    }
}

void SortingTester::swap(int& a, int& b){
    a ^= b;
    b ^= a;
    a ^= b;

    swap_count++;
}
int SortingTester::compare(int a, int b){
    if (a < b){
        return -1;
    } 
    else if (a == b) {
        return 0;
    }
    else {
        return 1;
    }
    comparisons++;
}

// Private Methods
//------------------------------------------------------------------------------

void SortingTester::shuffle_contents(){
    for (int i = test_size - 1; i > 0; i--){
        int j = randint(0, i-1);
        swap(data_[i], data_[j]);
    }
    swap_count = 0;
}
void SortingTester::print_test_start(){
    std::cout << cur_sort << ": starting sort of " 
        << test_size << " integers." << std::endl;
}
void SortingTester::print_check(){
    std::cout << cur_sort << ": Verifying that items are sorted.";
}

void SortingTester::check_sorted(){
    for (int i = 1; i < test_size; i++){
        if (data_[i] < data_[i-1]){
            // There is an error here
        }
    }
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
    int elapsed = get_ms_duration(std::chrono::high_resolution_clock::now()) -
        get_ms_duration(start);
    return elapsed;
}
void SortingTester::reset_test(){
    swap_count = 0;
    comparisons = 0;
}
