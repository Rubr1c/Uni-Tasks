#include "parallelreader.h"


void ParallelReader::readFile() {
    std::ifstream file(m_FilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

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

    int spread = count / m_ThreadNum;
    int remainder = count % m_ThreadNum;

    std::vector<std::future<void>> futures;
    std::cout << "Reading file\n";
#ifdef __unix__  
    
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

    pthread_join(thread, nullptr);  
#else
    for (int i = 0; i < m_ThreadNum; i++) {
        int startLine = i * spread + std::min(i, remainder);
        int endLine = startLine + spread + (i < remainder ? 1 : 0);

        futures.push_back(std::async(std::launch::async, [this, startLine, endLine, &lines, i]() {
            for (int currentLine = startLine; currentLine < endLine; ++currentLine) {
                const std::string& line = lines[currentLine];
                std::stringstream ss(line);
                std::string idStr, firstName, middleName, lastName, gpaStr;

                std::getline(ss, idStr, ',');
                std::getline(ss, firstName, ',');
                std::getline(ss, middleName, ',');
                std::getline(ss, lastName, ',');
                std::getline(ss, gpaStr);

                try {
                    long long id = std::stoll(idStr);
                    float gpa = std::stof(gpaStr);


                    studentList.insert({ id, firstName, middleName, lastName, gpa });
                    
                    threadWork[std::this_thread::get_id()]++;
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing line: " << line << std::endl;
                }
            }

            }));
    }
#endif
    for (auto& future : futures) {
        future.get();
    }

    for (const auto& pair : threadWork) {
        std::cout << "Thread: " << pair.first << ": " << pair.second << " Students\n";
    }
}