#include "course.h"
#include "student.h"

#include <iostream>
#include <algorithm>

Course::Course() : course_name("Unknown"), course_code("000") {}

Course::Course(const std::string& name, const std::string& code)
    : course_name(name), course_code(code) {
}

void Course::display() const {
    std::cout << "Course Name: " << course_name << std::endl;
    std::cout << "Course Code: " << course_code << std::endl;
    std::cout << "Enrolled Students: " << students.size() << std::endl;
}

std::string Course::code() const {
    return course_code;
}

std::string Course::name() const {
    return course_name;
}

void Course::add_student(Student& student) {
    if (students.size() >= COURSE_SIZE) {
        throw std::string("Error: Course " + course_code + " is full. Cannot enroll " + student.name() + ".");
    }
    students.push_back(&student);
}

void Course::display_students() const {
    std::cout << "Students enrolled in " << course_code << " - " << course_name << ":" << std::endl;
    std::for_each(students.begin(), students.end(), [](const Student* s) {
        std::cout << "  - " << s->name() << std::endl;
        });
}

Course::~Course() {
    std::cout << "Course object has been destroyed." << std::endl;
}