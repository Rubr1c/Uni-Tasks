#include <iostream>
#include <vector>
#include "SortingTester.h"
#include "Excel.h"
#include <sstream>
#include <format>
#include "JSONBuilder.h"

std::string startTest(std::vector<std::pair<int, double>(*)(int*, int)> sortingAlgorithms,
    std::vector<std::string>& algorithmNames) {
    JSONBuilder::clear();
    ExcelWriter<4> e(2);

    e.addRow({ "Sorting Algorithm", "Array Used", "Number of Comparisons" });
    e.switchSheet(2);
    e.addRow({ "Sorting Algorithm", "Array Used", "Time Taken" });
    e.switchSheet(1);

    JSONBuilder::startObject(true); 

    for (int i = 0; i < sortingAlgorithms.size(); i++) {
        SortingTester tester(sortingAlgorithms[i]);
        tester.test_comparisons();

        JSONBuilder::startArray(algorithmNames[i]);

        for (auto& entry : tester.random_moves) {
            std::string arr = tester.array_to_string<SortingTester::RANDOM_ARRAY>(entry.first);
            JSONBuilder::startObject(true);
            JSONBuilder::addKeyValue("array", arr);
            JSONBuilder::addKeyValue("moves", entry.second.first);
            JSONBuilder::addKeyValue("microseconds", entry.second.second);
            JSONBuilder::endObject();

            e.addRow({ algorithmNames[i], arr, static_cast<double>(entry.second.first) });
            e.switchSheet(2);
            e.addRow({ algorithmNames[i], arr, entry.second.second });
            e.switchSheet(1);
        }

        e.addChart({ algorithmNames[i], "Random Arrays" });
        e.switchSheet(2);
        e.addChart({ algorithmNames[i], "Random Arrays" });
        e.switchSheet(1);

        for (auto& entry : tester.sorted_moves) {
            std::string arr = tester.array_to_string<SortingTester::SORTED_ARRAY>(entry.first);
            JSONBuilder::startObject(true);
            JSONBuilder::addKeyValue("array", arr);
            JSONBuilder::addKeyValue("moves", entry.second.first);
            JSONBuilder::addKeyValue("microseconds", entry.second.second);
            JSONBuilder::endObject();

            e.addRow({ algorithmNames[i], arr, static_cast<double>(entry.second.first) });
            e.switchSheet(2);
            e.addRow({ algorithmNames[i], arr, entry.second.second });
            e.switchSheet(1);
        }

        e.addChart({ algorithmNames[i], "Sorted Arrays" });
        e.switchSheet(2);
        e.addChart({ algorithmNames[i], "Sorted Arrays" });
        e.switchSheet(1);

        for (auto& entry : tester.inverse_sorted_moves) {
            std::string arr = tester.array_to_string<SortingTester::INVERSE_SORTED_ARRAY>(entry.first);
            JSONBuilder::startObject(true);
            JSONBuilder::addKeyValue("array", arr);
            JSONBuilder::addKeyValue("moves", entry.second.first);
            JSONBuilder::addKeyValue("microseconds", entry.second.second);
            JSONBuilder::endObject();

            e.addRow({ algorithmNames[i], arr, static_cast<double>(entry.second.first) });
            e.switchSheet(2);
            e.addRow({ algorithmNames[i], arr, entry.second.second });
            e.switchSheet(1);
        }

        e.addChart({ algorithmNames[i], "Inverse Sorted Arrays" });
        e.switchSheet(2);
        e.addChart({ algorithmNames[i], "Inverse Sorted Arrays" });
        e.switchSheet(1);

        JSONBuilder::endArray();
    }

    JSONBuilder::endObject();
    return JSONBuilder::build();
}