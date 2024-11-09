#include "uni.h" 
#include "Sorting/Timer.h"


int e() {
    return 1;
}


int main() {
    /*std::vector<std::string> cols = { "Algorithm",
                                      "Array Tested",
                                      "Number of Moves",
                                      "Time Taken" };

    ExcelWriter e(cols);
   */

    /*SortingTester t(bubble_sort_count);
    t.test_comparisons();
    std::cout << " " << t.random_moves[0].first << " " << t.random_moves[0].second;*/


    std::vector<std::pair<int, long long>(*)(int*, int)> x = { bubble_sort_count, insertion_sort_count };
    std::vector<std::string> names = { "Bubble Sort", "Insertion Sort" };

    std::string out = startTest(x, names);
    std::cout << out;

    /*Timer t;
    * 
    

    std::cout << t.getDuration();*/
    
}
