#include "main.h"


void RunTasks() {
	std::cout << "====Task 1: Anagrams===="
		<< "\n\nTest Strings: cat, tac -> Expected Output: 1"
		<< "\nSorting Method: "
		<< areAnagramBySort("cat", "tac")
		<< "\nFrequency Array Method: "
		<< areAnagramsByFrequency("cat", "tac")
		<< "\nTest Strings: cat, dog -> Expected Output: 0"
		<< "\nSorting Method: "
	    << areAnagramBySort("cat", "dog")
		<< "\nFrequency Array Method: "
		<< areAnagramsByFrequency("cat", "dog") << "\n";

	std::cout << "\n====Task 2: Coin Scale====\n"
			  << "\nTest 1: {1.0, 1.0, 2.0} -> Expected Output: Coin 3 is Heiver\n"
			  << coinScale(1.0, 1.0, 2.0) << "\n"
			  << "\nTest 2: {1.0, 2.0, 1.0}\n"
			  << coinScale(1.0, 2.0, 1.0) << "\n"
			  << "\nTest 3: {2.0, 1.0, 1.0}\n"
			  << coinScale(2.0, 1.0, 1.0) << "\n"
			  << "\nTest 4: {2.0, 2.0, 1.0}\n"
			  << coinScale(2.0, 2.0, 1.0) << "\n"
			  << "\nTest 5: {2.0, 1.0, 2.0}\n"
			  << coinScale(2.0, 1.0, 2.0) << "\n"
			  << "\nTest 3: {1.0, 2.0, 2.0}\n"
			  << coinScale(1.0, 2.0, 2.0) << "\n";

	std::cout << "\n====Task 3: Array Test====\n\n"
			  << startTest({ 
							heap_sort_count, 
							bubble_sort_count,
							selection_sort_count, 
							insertion_sort_count 
						   },
						   {
							"Heap Sort",
							"Bubble Sort",
							"Selection Sort",
							"Insertion Sort"
						   }
						  );

	std::cout << "\n====Task 4: Tower Of Hanoi====\n\n"
			  << "3 Disks: \n"
		      << TowerOfHanoi(3, 'A', 'B', 'C') << " <- Number of Moves \n";

	std::cout << "\n====Task 5: Sorting 2n Disks====\n\n"
			  << "Input: 5 \n"
		      << sort2nDisks(5) << " <- Number of Moves\n";


	TextWrapper::WrapText("Mary loves to sing and perform tapdancing", 10);
	std::cout << "\n====Task 6: TextWrapping====\n\n"
		      << "Test Case 1: \nText - Mary loves to sing and perform tapdancing \nLine Width - 10\n"
			  << TextWrapper::Build();
	TextWrapper::Clear();
	TextWrapper::WrapText("The quick brown fox jumps over the lazy dog", 8);
	std::cout << "\nTest Case 2: \nText - The quick brown fox jumps over the lazy dog \nLine Width - 8\n"
		      << TextWrapper::Build();
	TextWrapper::Clear();

	
	std::cout << "\n====Task 7: DFS Maze====\n\n"
		      << dfs({13, 0}, {1, 14}) << "\n";

	std::cout << "\n====Task 8: Threads====\n\n";
	readStudents();
}
