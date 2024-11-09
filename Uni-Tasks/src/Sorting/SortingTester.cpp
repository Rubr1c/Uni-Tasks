#include "SortingTester.h"


SortingTester::SortingTester(std::pair<int, long long> (*sorting_algorithm)(int*, int)) : sortingAlgorithm(sorting_algorithm) {
    for (int i = 0; i < random_arrays.size(); i++) {
        int* rand_arr = new int[random_arrays[i].size()];
        int* sorted_arr = new int[sorted_arrays[i].size()];
        int* inv_sorted_arr = new int[inverse_sorted_arrays[i].size()];
        copy(random_arrays[i].begin(), random_arrays[i].end(), rand_arr);
        copy(sorted_arrays[i].begin(), sorted_arrays[i].end(), sorted_arr);
        copy(inverse_sorted_arrays[i].begin(), inverse_sorted_arrays[i].end(), inv_sorted_arr);
        randomArrays[i] = rand_arr;
        sortedArrays[i] = sorted_arr;
        inverseSortedArrays[i] = inv_sorted_arr;
    }
}

SortingTester::~SortingTester() {
    for (int i = 0; i < 30; i++) {
        delete[] randomArrays[i];
        delete[] sortedArrays[i];
        delete[] inverseSortedArrays[i];
    }
    delete[] randomArrays;
    delete[] sortedArrays;
    delete[] inverseSortedArrays;
}


void SortingTester::test_comparisons() {
    for (int i = 0; i < random_arrays.size(); i++) {
        random_moves[i] = 
            sortingAlgorithm(randomArrays[i], random_arrays[i].size());

        sorted_moves[i] = 
            sortingAlgorithm(sortedArrays[i], sorted_arrays[i].size());

        inverse_sorted_moves[i] = 
            sortingAlgorithm(inverseSortedArrays[i], inverse_sorted_arrays[i].size());
    }
}

