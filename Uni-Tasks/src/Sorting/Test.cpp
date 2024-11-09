#include <iostream>
#include <vector>
#include "SortingTester.h"
#include <sstream>

std::string startTest(std::vector<std::pair<int, long long>(*)(int*, int)> sortingAlgorithms,
			   std::vector<std::string>& algorithmNames) {
	std::stringstream output;
    output << "{\n";
	for (int i = 0; i < sortingAlgorithms.size(); i++) {
		SortingTester tester(sortingAlgorithms[i]);
		tester.test_comparisons();
		
		output << "  \"" << algorithmNames[i] << ": [\n";
        bool first = true;
        for (auto& entry : tester.random_moves) {
            if (!first) output << ",\n";
            first = false;

            output << "    {\n";
            output << "      \"array\": "
                << tester.array_to_string<SortingTester::RANDOM_ARRAY>(entry.first) << ",\n";
            output << "      \"moves\": " << entry.second.first << ",\n";
            output << "      \"microseconds\": " << entry.second.second << "\n";
            output << "    }";
        }
        output << "\n  ]\n";
	}
    output << "}";
	return output.str();
}