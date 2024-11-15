#include <iostream>
#include <utility>
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
		}
		if (j >= 0) count++; 
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
			count++; 
			if (arr[j] < arr[min]) {
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
			count++; 
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
	t.Stop();
	return { count, t.getDuration() };
}

void heapify(int arr[], int n, int i, int& count) {
	int largest = i;    
	int left = 2 * i + 1;    
	int right = 2 * i + 2;   

	if (left < n) {
		count++; 
		if (arr[left] > arr[largest]) {
			largest = left;
		}
	}

	if (right < n) {
		count++; 
		if (arr[right] > arr[largest]) {
			largest = right;
		}
	}

	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		heapify(arr, n, largest, count); 
	}
}

std::pair<int, long long> heap_sort_count(int arr[], int size) {
	int count = 0;
	Timer t;

	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(arr, size, i, count);
	}

	for (int i = size - 1; i > 0; i--) {
		std::swap(arr[0], arr[i]);

		heapify(arr, i, 0, count);
	}

	t.Stop();
	return { count, t.getDuration() };
}