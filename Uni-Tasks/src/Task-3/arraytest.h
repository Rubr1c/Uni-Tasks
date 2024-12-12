#pragma once
#include <iostream>
#include <vector>


std::string startTest(const std::vector<std::pair<int, double>(*)(int*, int)> sortingAlgorithms,
	const std::vector<std::string>& algorithmNames);

std::pair<int, double> insertion_sort_count(int arr[], int size);
std::pair<int, double> selection_sort_count(int arr[], int size);
std::pair<int, double> bubble_sort_count(int arr[], int size);
std::pair<int, double> heap_sort_count(int arr[], int size);

