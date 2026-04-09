#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

friend class Program;

class Student;

const int COURSE_SIZE = 6;

class Course {
private:
    std::string course_name;
    std::string course_code;
    std::vector<Student*> students;

public:
    Course();
    Course(const std::string& name, const std::string& code);

    void display() const;
    std::string code() const;
    std::string name() const;

    void add_student(Student& student);
    void display_students() const;

    ~Course();
};

#endif