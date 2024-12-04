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

#ifdef __unix__  // POSIX systems (Linux/macOS)
#include <pthread.h>
#endif

struct Student {
    long long id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    float gpa;
};

class LinkedList {
private:
    struct Node {
        Student student;
        std::unique_ptr<Node> next;

        Node(const Student& student) : student(student), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    std::mutex mtx;

public:
    LinkedList() : head(nullptr) {}

    void insert(const Student& student) {
        std::lock_guard<std::mutex> lock(mtx);

        Node* newNode = new Node(student);
        if (!head) {
            head = std::unique_ptr<Node>(newNode);
        }
        else {
            Node* temp = head.get();
            while (temp->next) {
                temp = temp->next.get();
            }
            temp->next.reset(newNode);
        }
    }

    void print() const {
        Node* temp = head.get();
        while (temp) {
            const Student& s = temp->student;
            std::cout << "ID: " << s.id <<
                ", Name: " << s.firstName << " " << s.middleName << " " << s.lastName <<
                ", GPA: " << s.gpa << std::endl;
            temp = temp->next.get();
        }
    }
};

class ParallelReader {
private:
    std::string m_FilePath;
    LinkedList studentList;
    int m_ThreadNum;
    bool useHardwareConcurrency;

public:
    ParallelReader(const std::string& filePath, bool useHardware = false, int threadNum = 1)
        : m_FilePath(filePath), m_ThreadNum(threadNum), useHardwareConcurrency(useHardware) {}

    void readFile() {
        std::ifstream file(m_FilePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        // Read the entire file into memory
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        size_t count = lines.size();
        if (useHardwareConcurrency) {
            m_ThreadNum = std::max(1, static_cast<int>(std::thread::hardware_concurrency()));
        }

        if (m_ThreadNum > count) {
            std::cout << "[WARN]: Number of threads exceeds number of lines in the file. Reducing thread count to " << count << "." << std::endl;
            m_ThreadNum = count;
        }

        // Adjust chunk size
        int spread = count / m_ThreadNum;
        int remainder = count % m_ThreadNum;

        std::vector<std::future<void>> futures;

        // Use std::async to launch parallel parsing (Windows) or pthread (Linux/macOS)
        for (int i = 0; i < m_ThreadNum; i++) {
            int startLine = i * spread + std::min(i, remainder);
            int endLine = startLine + spread + (i < remainder ? 1 : 0);

#ifdef __unix__  // POSIX systems (Linux/macOS)
            // Create a pthread for each chunk of lines
            pthread_t thread;
            pthread_create(&thread, nullptr, [](void* arg) -> void* {
                auto params = static_cast<std::tuple<int, int, std::vector<std::string>&, LinkedList&>*>(arg);
                int startLine = std::get<0>(*params);
                int endLine = std::get<1>(*params);
                auto& lines = std::get<2>(*params);
                LinkedList& studentList = std::get<3>(*params);

                for (int currentLine = startLine; currentLine < endLine; ++currentLine) {
                    const std::string& line = lines[currentLine];
                    std::stringstream ss(line);
                    std::string idStr, firstName, middleName, lastName, gpaStr;

                    // Parsing order: id, firstName, middleName, lastName, gpa
                    std::getline(ss, idStr, ',');
                    std::getline(ss, firstName, ',');
                    std::getline(ss, middleName, ',');
                    std::getline(ss, lastName, ',');
                    std::getline(ss, gpaStr);

                    try {
                        long long id = std::stoll(idStr);
                        float gpa = std::stof(gpaStr);

                        studentList.insert({ id, firstName, middleName, lastName, gpa });
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error parsing line: " << line << std::endl;
                    }
                }

                return nullptr;
                }, new std::tuple<int, int, std::vector<std::string>&, LinkedList&>(startLine, endLine, std::ref(lines), std::ref(studentList)));

            pthread_join(thread, nullptr);  // Wait for thread to finish
#else
            // Use std::async for Windows or other systems with C++ threads support
            futures.push_back(std::async(std::launch::async, [this, startLine, endLine, &lines]() {
                for (int currentLine = startLine; currentLine < endLine; ++currentLine) {
                    const std::string& line = lines[currentLine];
                    std::stringstream ss(line);
                    std::string idStr, firstName, middleName, lastName, gpaStr;

                    // Parsing order: id, firstName, middleName, lastName, gpa
                    std::getline(ss, idStr, ',');
                    std::getline(ss, firstName, ',');
                    std::getline(ss, middleName, ',');
                    std::getline(ss, lastName, ',');
                    std::getline(ss, gpaStr);

                    try {
                        long long id = std::stoll(idStr);
                        float gpa = std::stof(gpaStr);

                        studentList.insert({ id, firstName, middleName, lastName, gpa });
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error parsing line: " << line << std::endl;
                    }
                }
                }));
#endif
        }

        // Wait for all threads to complete
        for (auto& future : futures) {
            future.get();
        }

        studentList.print();
    }
};

int main() {
    std::string filename;
    int threadCount;

    std::cin >> filename >> threadCount;

    filename = "../../../src/ParellelProgamming/" + filename;

    char useHardwareChoice;
    std::cout << "Would you like to use hardware concurrency for thread count? (y/n): ";
    std::cin >> useHardwareChoice;

    bool useHardware = (useHardwareChoice == 'y' || useHardwareChoice == 'Y');

    ParallelReader p(filename, useHardware, threadCount);
    p.readFile();

    return 0;
}
