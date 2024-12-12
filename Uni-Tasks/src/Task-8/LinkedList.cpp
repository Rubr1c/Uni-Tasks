#include "linkedlist.h"

void LinkedList::insert(const Student& student) {
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

void LinkedList::print() const {
    Node* temp = head.get();
    while (temp) {
        const Student& s = temp->student;
        std::cout << "ID: " << s.id <<
            ", Name: " << s.firstName << " " << s.middleName << " " << s.lastName <<
            ", GPA: " << s.gpa << std::endl;
        temp = temp->next.get();
    }
}