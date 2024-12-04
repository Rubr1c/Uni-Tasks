#include "SortingTester.h"


SortingTester::SortingTester(std::pair<int, double> (*sorting_algorithm)(int*, int)) :
    sortingAlgorithm(sorting_algorithm) {
    for (int i = 0; i < random_vectors.size(); i++) {
        int* rand_arr = new int[random_vectors[i].size()];
        int* sorted_arr = new int[sorted_vectors[i].size()];
        int* inv_sorted_arr = new int[inverse_sorted_vectors[i].size()];
        copy(random_vectors[i].begin(), random_vectors[i].end(), rand_arr);
        copy(sorted_vectors[i].begin(), sorted_vectors[i].end(), sorted_arr);
        copy(inverse_sorted_vectors[i].begin(), inverse_sorted_vectors[i].end(), inv_sorted_arr);
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
    for (int i = 0; i < random_vectors.size(); i++) {
        random_moves[i] = 
            sortingAlgorithm(randomArrays[i], random_vectors[i].size());

        sorted_moves[i] = 
            sortingAlgorithm(sortedArrays[i], sorted_vectors[i].size());

        inverse_sorted_moves[i] = 
            sortingAlgorithm(inverseSortedArrays[i], inverse_sorted_vectors[i].size());
    }
}

