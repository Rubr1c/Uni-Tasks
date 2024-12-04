struct Student {
    long long id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    float gpa;
    Student* next;

    Student() : id(0), gpa(0.0), next(nullptr) {}
};