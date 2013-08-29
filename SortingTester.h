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
    private:
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
