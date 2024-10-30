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

    SortingTester t(bubble_sort_count);
    t.test_comparisons();
    std::cout << " " << t.random_moves[0].first << " " << t.random_moves[0].second;

    /*Timer t;
    

    std::cout << t.getDuration();*/
    
}
