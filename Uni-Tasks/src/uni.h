#pragma once

#include "iostream"
#include "Sorting/Timer.h"
#include "Sorting/Excel.h"
#include "Sorting/SortingTester.h"
#include "./ParellelProgamming/Student.h"
#include <mutex>

int TowerOfHanoi(int n, char source, char auxiliary, char destination);
std::string coinScale(float c1, float c2, float c3);
bool areAnagramBySort(std::string word1, std::string word2);
bool areAnagramByMap(const std::string& word1, const std::string& word2);
bool areAnagramsBySum(const std::string& word1, const std::string& word2);

int sort2nDisks(int n);

std::pair<int, double> insertion_sort_count(int arr[], int size);
std::pair<int, double> selection_sort_count(int arr[], int size);
std::pair<int, double> bubble_sort_count(int arr[], int size);
std::pair<int, double> heap_sort_count(int arr[], int size);

std::string startTest(std::vector<std::pair<int, double>(*)(int*, int)> sortingAlgorithms,
	std::vector<std::string>& algorithmNames);

void dfs(std::pair<int, int> start, std::pair<int, int> goal);

void wrapText(const std::string& text);

