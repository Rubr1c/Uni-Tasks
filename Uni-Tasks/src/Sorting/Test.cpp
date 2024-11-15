#include <iostream>
#include <vector>
#include "SortingTester.h"
#include "Excel.h"
#include <sstream>
#include <format>

std::string startTest(std::vector<std::pair<int, long long>(*)(int*, int)> sortingAlgorithms,
			   std::vector<std::string>& algorithmNames) {
	std::stringstream output;

    ExcelWriter<4> e(2);
    output << "{\n";
    e.addRow({ "Sorting Algorithm", "Array Used", "Number of Comparisons" });
    e.switchSheet(2);
    e.addRow({ "Sorting Algorithm", "Array Used", "Time Taken" });
    e.switchSheet(1);
	for (int i = 0; i < sortingAlgorithms.size(); i++) {
		SortingTester tester(sortingAlgorithms[i]);
		tester.test_comparisons();
		
		output << "  \"" << algorithmNames[i] << "\": [\n";
        bool first = true;
        for (auto& entry : tester.random_moves) {
            if (!first) output << ",\n";
            first = false;

            std::string arr = tester.array_to_string<SortingTester::RANDOM_ARRAY>(entry.first);

            output << "    {\n";
            output << "      \"array\": "
                << arr << ",\n";
            output << "      \"moves\": " << entry.second.first << ",\n";
            output << "      \"microseconds\": " << entry.second.second << "\n";
            output << "    }";

            e.addRow({ algorithmNames[i],
                     arr,
                     entry.second.first,
                     });

            e.switchSheet(2);
            e.addRow({ algorithmNames[i],
                     arr,
                     std::format("{:.2f}", entry.second.second) + " microseconds" });

            e.switchSheet(1);

        }

        first = true;
        for (auto& entry : tester.sorted_moves) {
            if (!first) output << ",\n";
            first = false;

            std::string arr = tester.array_to_string<SortingTester::SORTED_ARRAY>(entry.first);

            output << "    {\n";
            output << "      \"array\": "
                << arr << ",\n";
            output << "      \"moves\": " << entry.second.first << ",\n";
            output << "      \"microseconds\": " << entry.second.second << "\n";
            output << "    }";

            e.addRow({ algorithmNames[i],
                     arr,
                     entry.second.first,
                });

            e.switchSheet(2);
            e.addRow({ algorithmNames[i],
                     arr,
                     std::format("{:.2f}", entry.second.second) + " microseconds" });

            e.switchSheet(1);

        }
        first = true;
        for (auto& entry : tester.inverse_sorted_moves) {
            if (!first) output << ",\n";
            first = false;

            std::string arr = tester.array_to_string<SortingTester::INVERSE_SORTED_ARRAY>(entry.first);

            output << "    {\n";
            output << "      \"array\": "
                << arr << ",\n";
            output << "      \"moves\": " << entry.second.first << ",\n";
            output << "      \"microseconds\": " << entry.second.second << "\n";
            output << "    }";

            e.addRow({ algorithmNames[i],
                     arr,
                     entry.second.first,
                });

            e.switchSheet(2);
            e.addRow({ algorithmNames[i],
                     arr,
                     std::format("{:.2f}", entry.second.second) + " microseconds" });

            e.switchSheet(1);

        }
        output << "\n  ]\n";
        e.addChart();
	}
    output << "}";
	return output.str();
}