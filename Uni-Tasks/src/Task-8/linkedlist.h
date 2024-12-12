#pragma once
#include "student.h"
#include <memory>
#include <mutex>
#include <iostream>

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

    void insert(const Student& student);
    void print() const;
};
