#pragma once
#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <future>
#include <memory>
#include <iterator>
#include <unordered_map>

#ifdef __unix__  
#include <pthread.h>
#endif

class ParallelReader {
private:
    std::string m_FilePath;
    LinkedList studentList;
    int m_ThreadNum;
    bool useHardwareConcurrency;
    std::unordered_map<std::thread::id, std::atomic<int>> threadWork;

public:
    ParallelReader(const std::string& filePath, bool useHardware = false, int threadNum = 1)
        : m_FilePath(filePath), m_ThreadNum(threadNum), useHardwareConcurrency(useHardware) {
        }

    void readFile();
};