#include "parallelreader.h"

#define INPUT 0

void readStudents() {

#if INPUT
    std::string filename;
    int threadCount;

    std::cin >> filename >> threadCount;

    filename = "../../../src/Task-8/" + filename;

    char useHardwareChoice;
    std::cout << "Would you like to use hardware concurrency for thread count? (y/n): ";
    std::cin >> useHardwareChoice;

    bool useHardware = (useHardwareChoice == 'y' || useHardwareChoice == 'Y');

    ParallelReader p(filename, useHardware, threadCount);
    p.readFile();
#else
    ParallelReader p("../../../src/Task-8/students.txt", false, 4);
    p.readFile();
#endif
    
}
