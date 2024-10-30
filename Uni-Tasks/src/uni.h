#pragma once

#include <iostream>
#include <vector>
#include "CoinScale.h"
#include "Sorting/Timer.h"
#include "Sorting/Excel.h"
#include "Sorting/SortingTester.h"

int TowerOfHanoi(int n, char source, char auxiliary, char destination);

bool areAnagramByMap(const std::string& word1, const std::string& word2);

std::pair<int, long long> insertion_sort_count(int arr[], int size);
std::pair<int, long long> selection_sort_count(int arr[], int size);
std::pair<int, long long> bubble_sort_count(int arr[], int size);






