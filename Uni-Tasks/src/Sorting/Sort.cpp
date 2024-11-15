#include <iostream>
#include "Timer.h"


std::pair<int, long long> insertion_sort_count(int arr[], int size) {
	int count = 0;
	Timer t;
	for (int i = 1; i < size; i++) {
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			count++;
			arr[j + 1] = arr[j];
			j--;
			count++;
		}
		arr[j + 1] = key;
	}
	t.Stop();
	return { count, t.getDuration() };
}

std::pair<int, long long> selection_sort_count(int arr[], int size) {
	int count = 0;
	Timer t;
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				count++;
				min = j;
			}
		}
		std::swap(arr[i], arr[min]);
	}
	t.Stop();
	return { count, t.getDuration() };
}

std::pair<int, long long> bubble_sort_count(int arr[], int size) {
	int count = 0;
	Timer t;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				count++;
				std::swap(arr[j], arr[j + 1]);
				count++;
			}
		}
	}
	t.Stop();
	return { count, t.getDuration() };
}